#import "Network.h"

#include <sys/types.h>  // sockets
#include <sys/socket.h> // sockets
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>     // close
#include <arpa/inet.h>  // inet_addr


@implementation Network

/**
 * Designated initializer. Open a socket on a port and join the
 * multicast group. We do a join on the multicast group because
 * we may be listening for packets, and even in a local network
 * environment IGMP snooping may be turned on, which prevents
 * us from hearing multicast packets sent from another switch port.
 *
 * This will return nil if the socket is unable to be opened or for
 * any other fatal error.
 */
-(id)initOnPort:(int)pPort joinGroup:(NSString*)pMulticastGroup
{
    self = [super init];
    if(self)
    {
        socketFd = -1;
        struct sockaddr_in multicastAddress;
        unsigned char ttl = 2;               // For setting mutlicast TTL
        int resuePortFlag = 1;               // for so_reuse
        struct ip_mreq multicastJoinRequest; // Request for IGMP joing
        
        multicastDestination = pMulticastGroup;
        [multicastDestination retain];
        port = pPort;
        
        // Open up a socket, which is treated as a file descriptor
        socketFd = socket(PF_INET,       // Internet socket (as opposed to a unix or xerox soceket)
                          SOCK_DGRAM,    // Of type UDP (as opposed to TCP in SOCK_STREAM)
                          IPPROTO_UDP);  // user datagram protocol
        
        // Should fail only if things are really, really hosed
        if(socketFd <  0)
        {
            return nil;
        }
        
        // Set up a join on the socket for the multicast group
        // Zero out the multicast address structure so we don't have anything random
        // allocated in the space
        memset(&multicastAddress, 0, sizeof(multicastAddress));
       
        // This is used to tell the network stack what interface and format to listen on
        multicastAddress.sin_family = AF_INET;
        multicastAddress.sin_addr.s_addr = htonl(INADDR_ANY); // listen on all interfaces
        multicastAddress.sin_port = htons(port);
        
        // Set the TTL on outgoing multicast packets. The TTL in multicast is used
        // to limit the extent to which the packet is distributed in the network.
        // In a campus environment we want it to live for at least a couple hops.
        if( (setsockopt(socketFd, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&ttl, sizeof(ttl))) < 0)
        {
            return nil; // Could not set the sockopt for ttl, bail
        }
            
        // Set the sock_addr_reuse option, which allows multiple processes to receive
        // packets from the same socket. This needs to be done BEFORE any bind operation.
        // SOL_SOCKET specifies an operation at the socket layer
        if( (setsockopt(socketFd, SOL_SOCKET, SO_REUSEPORT, (void*)&resuePortFlag, sizeof(resuePortFlag))) < 0)
        {
            return nil; // Could not set the sockopt for tt, bail
        }
        
        // Do a bind. This is neccessary to receive packets. bind causes the stack to start
        // passing packets to the app. Uses the multicastAddress variable filled out above.
        if( (bind(socketFd, (struct sockaddr*)&multicastAddress, sizeof(multicastAddress))) <  0)
        {
            return nil; // failed bind, bail
        }
        
        // Do an IGMP join operation; this informs the router or switch that there is a host
        // on this port that is interested in the given multicast address.
        memset(&multicastJoinRequest, 0, sizeof(multicastJoinRequest));
        multicastJoinRequest.imr_multiaddr.s_addr = inet_addr([pMulticastGroup cStringUsingEncoding:NSASCIIStringEncoding]);
        multicastJoinRequest.imr_interface.s_addr = htonl(INADDR_ANY);
        
        // Send the join request via a set sock opt
        if( (setsockopt(socketFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&multicastJoinRequest, sizeof(multicastJoinRequest))) < 0)
        {
            return nil; // Can't join group; bail
        }
    }

    return self;
}

/**
 * Sets a callback method that will be invoked when a packet arrives.
 */
-(void)setCallbackObject:(id)receiver andMethod:(SEL)method;
{
    callbackObject = receiver;
    callbackMethod = method;
}

-(void)sendData:(void*)data withLength:(int)dataLength
{
    struct sockaddr_in destination;
    
    // Set up the destination address
    memset(&destination, 0, sizeof(destination));
    destination.sin_family = AF_INET;
    destination.sin_addr.s_addr = inet_addr([multicastDestination cStringUsingEncoding:NSASCIIStringEncoding]);
    destination.sin_port = port;
    
   // NSLog(@"preparing to send packet");
    
    int bytesSent = sendto(socketFd,             // Socket file descriptor
                            data,                // ptr to data to send
                            dataLength,          // How many bytes
                             0,                  // flags for sending (all zero)
                            (struct sockaddr*) &destination,        // destination address (set to multicast address)
                           sizeof(destination)); // size of destination address
    
    if(bytesSent != dataLength)
    {
        NSLog(@"Unable to send multicast packet");
    }
    else
    {
       // NSLog(@"Sent multicast packet");
    }
}

/**
 * Reads (blocking) a packet from the network, and returns the data in an NSData
 * object.
 */
-(NSData*)receiveData
{
    char               buffer[1520];
    int                bytesReceivedCount = 0;
    struct sockaddr_in fromAddress;
    unsigned int       fromAddressLength = 0;
    NSData             *payload;
    
    //NSLog(@"entering receive data method");
    
    memset(&fromAddress, 0, sizeof(fromAddress));
    fromAddressLength = sizeof(fromAddress);
    
    memset(buffer, 0, sizeof(buffer)); // zero out receive buffer
    
    // blocking receive
    bytesReceivedCount = recvfrom(socketFd,       // file descriptor
                                  buffer,         // buffer we read into
                                  1519,           // max number of bytes to read
                                  0,              // flags
                                  (struct sockaddr*)&fromAddress,   // IP address of sender
                                  &fromAddressLength);              // length of from address
    if((bytesReceivedCount) < 0 || (bytesReceivedCount > 1519))
    {
        NSLog(@"Error receiving packet");
    }
    else
    {
       // NSLog(@"Received data");
        // Copies data into NSData, so it doesn't go away when the method exits
       payload = [NSData dataWithBytes:buffer length:bytesReceivedCount]; 
    }
    
    return payload;
}

/**
 * Note the use of autorelase pool. Normally the autorelease pool is provided in the
 * main event loop. In a thread we're outside the main event loop, so we need to
 * provide our own autorelease pool, and periodically drain it. This is the case
 * even if we don't have any leaks at the level visible to us; we may call objects
 * in foundation that call retain/release, and those internal implementations need
 * an autorelease pool present.
 */
-(void)startThreadWithObject:(id)obj
{
    //char *buf = "Hello";
    
    while(YES)
    {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

        NSData *receivedData;
        
        receivedData = [self receiveData]; // blocking call
        
        // On the main event thread, notify that we have data. This causes the update to occur
        // in the main event thread, where it should be safe to modify the UI elements. Generally
        // speaking, you don't want to have two threads accessing UI elements at the same
        // time.
        [callbackObject performSelectorOnMainThread:callbackMethod withObject:receivedData waitUntilDone:NO];
        
        
        //[self sendData:(void*)buf withLength:5];
        
        [pool release];
    }
}

@end
