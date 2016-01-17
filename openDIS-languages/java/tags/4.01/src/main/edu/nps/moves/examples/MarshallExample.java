package edu.nps.moves.examples;

import edu.nps.moves.dis.*;

import java.io.*;
import javax.xml.bind.*;

/**
 * Example of using JAXB to marshal and unmarshal to XML. Uses
 * Jaxb 2.1.x.
 * 
 * @author DMcG
 * @version $Id:$
 */
public class MarshallExample {

    /**
     * Shows two ways to marshal and unmarshal XML. The first way to marshal
     * involves calling a method in a class marked as an XmlRootElement in
     * the generated code. The second (preferred) way involves simply calling
     * the required marshal/unmarshal code external to the XmlRootElement
     * class.
     * @param args
     */
    public static void main(String args[]) {

        PduContainer container = new PduContainer(); // XmlRootElement marked class

        // A few PDUs to marshal
        EntityStatePdu espdu = new EntityStatePdu();
        FirePdu firePdu = new FirePdu();
        DetonationPdu detonationPdu = new DetonationPdu();
        FirePdu bang = new FirePdu();

        // Add them to the XmlRootElement container
        container.getPdus().add(espdu);
        container.getPdus().add(firePdu);
        container.getPdus().add(detonationPdu);
        container.getPdus().add(bang);
        
        for(int idx = 0; idx < 500; idx++)
        {
            EntityStatePdu pdu = new EntityStatePdu();
            
            Vector3Double loc = pdu.getEntityLocation();
            loc.setX(Math.random());
            loc.setY(Math.random());
            loc.setZ(Math.random());
            
            Vector3Float vel = pdu.getEntityLinearVelocity();
            vel.setX((float)Math.random());
            vel.setY((float)Math.random());
            vel.setZ((float)Math.random());
            
            EntityID eid = pdu.getEntityID();
            eid.setSite((short)(Math.random() * 1000));
            eid.setApplication((short)(Math.random() * 1000));
            eid.setEntity((short)(Math.random() * 1000));
            
            container.getPdus().add(pdu);
        }

        // And marshall it to this file
        
        //container.marshallToXml("somePdus.xml");

        // An alternative way to marshall
        try {
            JAXBContext context = JAXBContext.newInstance("edu.nps.moves.dis"); 
            Marshaller marshaller = context.createMarshaller();
            marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
            marshaller.marshal(container, new FileOutputStream("somePdus.xml"));
            

            // Just to prove nothing funny is going on, read the XML file back in
            Unmarshaller unmarshaller = context.createUnmarshaller();
            PduContainer unmarshalledObject = (PduContainer) unmarshaller.unmarshal(new FileInputStream("somePdus.xml"));
            System.out.println("got " + unmarshalledObject.getNumberOfPdus() + " back");
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println(e);

        }
    }
}
