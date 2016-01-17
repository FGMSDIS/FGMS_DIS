package edu.nps.moves.examples;

import java.io.*;
import java.net.*;
import java.util.*;

import edu.nps.moves.dis.*;
import edu.nps.moves.disutil.DisTime;

/**
 * Creates and sends ESPDUs in IEEE binary format. 
 *
 * @author DMcG
 */
public class EspduSender 
{
    public enum Mode{UNICAST, MULTICAST};

    /** multicast group we send on */
    public static final String MULTICAST_GROUP="239.1.2.3";
   
    /** Port we send on */
    public static final int    PORT = 62040;
    
public static void main(String args[])
{
    EntityStatePdu espdu = new EntityStatePdu();
    MulticastSocket socket = null;
    InetAddress     address = null;
    Mode mode = Mode.MULTICAST;
    
    // Check for system properties passed into the VM via the -Dattr=value
    // method
    Properties systemProperties = System.getProperties();
    String multicastGroup = systemProperties.getProperty("multicastGroup");
    String unicastDestination = systemProperties.getProperty("unicastDestination");
    String port = systemProperties.getProperty("port");
    int portInt = PORT;
    DisTime disTime = DisTime.getInstance();

    try
    {
        if(port != null)
            portInt = Integer.parseInt(port);

        if(unicastDestination != null)
            mode = Mode.UNICAST;
          else
            mode = Mode.MULTICAST;

         if(mode == mode.UNICAST)
         {
             address = InetAddress.getByName(unicastDestination);
             socket = new MulticastSocket(portInt);
         }

         if(mode == mode.MULTICAST)
         {
            if(multicastGroup == null)
                multicastGroup = MULTICAST_GROUP;
            address = InetAddress.getByName(multicastGroup);
            socket = new MulticastSocket(portInt);
            socket.joinGroup(address);
         }

    }
    catch(Exception e)
    {
        System.out.println(e);
        System.exit(-1);
    }
    
    espdu.setExerciseID((short)0);
    
    // The EID is the unique identifier for objects in the world. This 
    // EID should match up with the ID for the object specified in the 
    // VMRL/x3d world.
    EntityID eid = espdu.getEntityID();
    eid.setSite(0);
    eid.setApplication(1); // 1
    eid.setEntity(2); // 2

    try
    {
        
        while(true)
        {
            for(int idx = 0; idx < 100; idx++)
            {
                // The timestamp should be monotonically increasing. Many implementations
                // discard packets that have earlier timestamps (assumption is that it
                // arrived out of order) or non-increasing timestamp (dupe packet).
                // The time should be slaved to clock time, so we can determine the time
                // between packets, but this is the minimum for testing.
                long timestamp = espdu.getTimestamp();
                timestamp++;
                espdu.setTimestamp(timestamp);

                // An alterative approach: actually follow the standard.
                //int ts = disTime.getDisAbsoluteTimestamp();
                //espdu.setTimestamp(ts);
                
                // Modify the x-axis position of the object
                // 36.595517, -121.877939
                Vector3Double location = espdu.getEntityLocation();
                location.setX(36.595517);
                location.setY(-121.877939 + (double)((double)idx / 1000.0));
                
                // Do some rotation to make sure that works
                Orientation orientation = espdu.getEntityOrientation();
                float psi = orientation.getPsi();
                psi = psi + idx;
                orientation.setPsi(psi);
                orientation.setTheta((float)(orientation.getTheta() + idx /2.0));
                
                // Marshal out the object to a byte array, then send a datagram
                // packet with that data in it.
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                DataOutputStream dos = new DataOutputStream(baos);
                espdu.marshal(dos);
                byte[] data = baos.toByteArray();
               
                DatagramPacket packet = new DatagramPacket(data, data.length, address, PORT);
                
                socket.send(packet);
                Thread.sleep(1000);
                
                System.out.print("Moving espdu EID=[" + eid.getSite() + "," + eid.getApplication() + "," + eid.getEntity() + "]");
                System.out.println(" Location=[" + location.getX() + "," + location.getY() + "," + location.getZ() + "]");
                                   
            }
        }
    }
    catch(Exception e)
    {
        System.out.println(e);
    }
        
}

}
