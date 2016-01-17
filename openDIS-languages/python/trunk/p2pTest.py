import socket 
import struct 
import warnings
import random
import time
from espduCreator import *
try:
    import thread as _thread
except ImportError:
    import dummy_thread as _thread

# @author: Shawn Pollock
# @author: Tommy Getty
# @author: John Weaver

# @title: P2P network DIS demonstration
# @date: 17SEP2010

# @description: This progam will create an entity with and use espduCreator to create a DIS compliant
#  entity state PDU.  This PDU will be updated every program cycle using a simple DR algorithm. The 
#  ESPDU is multicast to the network every 2 seconds.  Additionally this program monitors the network 
#  for other ESPDUs and displays the pertinent info translated from them.

# Prevent deprecated function warnings
def fxn():
    warnings.warn("deprecated", DeprecationWarning)
with warnings.catch_warnings():
    warnings.simplefilter("ignore")
    fxn()
    
    # Setup multicast socket and set socket options.
    MCAST_GRP = '239.1.2.3' 
    MCAST_PORT = 62040 
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) 
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) 
    sock.bind(('', MCAST_PORT)) 
    mreq = struct.pack("4sl", socket.inet_aton(MCAST_GRP), socket.INADDR_ANY) 
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq) 
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2) 
    
    # Create a new ESPDU to represent my entity in the simulation
    myESPDU = ESPDU(0)
    
    # Setup an ID number for my entity
    myESPDU.ID = random.randint(1,1000)
    
    # Setup initial position and velocity
    myESPDU.x = random.random() * 200 - 100
    myESPDU.y = random.random() * 200 - 100
    myESPDU.z = random.random() * 200 - 100
    myESPDU.vX = random.random() * 0.2 - 0.1
    myESPDU.vY = random.random() * 0.2 - 0.1
    myESPDU.vZ = random.random() * 0.2 - 0.1
     
    # Time since last position update 
    timelast = time.time()
    
    # Time when next multicast is due (hearbeat)
    timeover = time.time()
    
    while True: # Loop forever
        # Is it time for next update?
        if time.time() > timeover:
            # pack the ESPDU into the binary format
            myESPDU.marshall()
            # send the ESPDU to the multicast
            sock.sendto( myESPDU.espdu, (MCAST_GRP, MCAST_PORT))
            # set time for next update
            timeover = time.time() + 2.0
            # receive ESPDU
            input = sock.recv(1024)
            # translate the ESPDU
            inESPDU = ESPDU(input)
            # print the relevant ESPDU information
            inESPDU.printESPDU()
            print " "
        # update position based on velocity and elapsed time
        dt = time.time() - timelast
        myESPDU.x += dt * myESPDU.vX
        myESPDU.y += dt * myESPDU.vY
        myESPDU.z += dt * myESPDU.vZ
        
      