/**
 * Encapsulates a multicast UDP socket, for sending and receiving UDP packets on multicast.
 *
 * Opens up a UDP port and joins a multicast group. The user can specify an object and method
 * that will be called when a packet arrives. <p>
 *
 * This is intended to be run in a separate thread; the read from the socket is blocking.<p>
 *
 * @author DMcG
 */

//#import <UIKit/UIKit.h>


@interface Network : NSObject 
{
    /** file descriptor for the network socket */
    int      socketFd;
    
    /** The multicast port we listen on and send to */
    NSString *multicastDestination;
    
    /** The UDP port we listen on and send to */
    int      port;
    
    /** Object we notify when we receive a packet */
    id       callbackObject;
    
    /** Method we call on the object above when we receive a packet */
    SEL      callbackMethod;

}


-(id)initOnPort:(int)port joinGroup:(NSString*)pMulticastGroup;

-(void)setCallbackObject:(id)receiver andMethod:(SEL)method;

-(void)sendData:(void*)data withLength:(int)dataLength;

/** NOTE: this is a blocking call, and will wait until a packet arrives. You should
 * probably call this from inside a thread.
 */
-(NSData*)receiveData;

-(void)startThreadWithObject:(id)obj;

@end
