package edu.nps.moves.dis;

import java.util.*;
import java.io.*;
import edu.nps.moves.disenum.*;
import edu.nps.moves.disutil.*;

// Jaxb and Hibernate annotations generally won't work on mobile devices. XML serialization uses jaxb, and
// javax.persistence uses the JPA JSR, aka hibernate. See the Hibernate site for details.
// To generate Java code without these, and without the annotations scattered through the
// see the XMLPG java code generator, and set the boolean useHibernateAnnotations and useJaxbAnnotions 
// to false, and then regenerate the code

import javax.xml.bind.*;            // Used for JAXB XML serialization
import javax.xml.bind.annotation.*; // Used for XML serialization annotations (the @ stuff)
import javax.persistence.*;         // Used for JPA/Hibernate SQL persistence

/**
 * Section 5.2.32. Variable Datum Record
 *
 * Copyright (c) 2008-2010, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
@Entity  // Hibernate
@Inheritance(strategy=InheritanceType.JOINED)  // Hibernate
public class VariableDatum extends Object implements Serializable
{
   /** Primary key for hibernate, not part of the DIS standard */
   private long pk_VariableDatum;

   /** ID of the variable datum */
   protected long  variableDatumID;

   /** length of the variable datums */
   protected long  variableDatumLength;

   /** variable length list of 64-bit datums */
   protected List< EightByteChunk> variableDatums = new ArrayList<EightByteChunk>(); 

/** Constructor */
 public VariableDatum()
 {
 }

@Transient  // Marked as transient to prevent hibernate from thinking this is a persistent property
public int getMarshalledSize()
{
   int marshalSize = 0; 

   marshalSize = marshalSize + 4;  // variableDatumID
   marshalSize = marshalSize + 4;  // variableDatumLength
   for(int idx=0; idx < variableDatums.size(); idx++)
   {
        EightByteChunk listElement = variableDatums.get(idx);
        marshalSize = marshalSize + listElement.getMarshalledSize();
   }

   return marshalSize;
}


/** Primary key for hibernate, not part of the DIS standard */
@Id
@GeneratedValue(strategy=GenerationType.AUTO)
public long getPk_VariableDatum()
{
   return pk_VariableDatum;
}

/** Hibernate primary key, not part of the DIS standard */
public void setPk_VariableDatum(long pKeyName)
{
   this.pk_VariableDatum = pKeyName;
}

public void setVariableDatumID(long pVariableDatumID)
{ variableDatumID = pVariableDatumID;
}

@XmlAttribute // Jaxb
@Basic       // Hibernate
public long getVariableDatumID()
{ return variableDatumID; 
}

@XmlAttribute
@Basic
public long getVariableDatumLength()
{ return (long)variableDatums.size() * 64; // patch to fix units; bits rather than bytes
}

/** Note that setting this value will not change the marshalled value. The list whose length this describes is used for that purpose.
 * The getvariableDatumLength method will also be based on the actual list length rather than this value. 
 * The method is simply here for java bean completeness.
 */
public void setVariableDatumLength(long pVariableDatumLength)
{ variableDatumLength = pVariableDatumLength;
}

public void setVariableDatums(List<EightByteChunk> pVariableDatums)
{ variableDatums = pVariableDatums;
}

@XmlElementWrapper(name="variableDatumsList" ) //  Jaxb
@OneToMany    // Hibernate
public List<EightByteChunk> getVariableDatums()
{ return variableDatums; }


public void marshal(DataOutputStream dos)
{
    try 
    {
       dos.writeInt( (int)variableDatumID);
       dos.writeInt( (int)variableDatums.size() * 64 ); // post-processing patch to fix units; bits rather than bytes

       for(int idx = 0; idx < variableDatums.size(); idx++)
       {
            EightByteChunk aEightByteChunk = variableDatums.get(idx);
            aEightByteChunk.marshal(dos);
       } // end of list marshalling

    } // end try 
    catch(Exception e)
    { 
      System.out.println(e);}
    } // end of marshal method

public void unmarshal(DataInputStream dis)
{
    try 
    {
       variableDatumID = dis.readInt();
       variableDatumLength = dis.readInt();
        int over = variableDatumLength % 64 > 0 ? 1 : 0; // post-processing patch to fix units problem
        variableDatumLength = (variableDatumLength / 64) + over;
        
       for(int idx = 0; idx < variableDatumLength; idx++)
       {
           EightByteChunk anX = new EightByteChunk();
           anX.unmarshal(dis);
           variableDatums.add(anX);
       }

    } // end try 
   catch(Exception e)
    { 
      System.out.println(e); 
    }
 } // end of unmarshal method 


/**
 * Packs a Pdu into the ByteBuffer.
 * @throws java.nio.BufferOverflowException if buff is too small
 * @throws java.nio.ReadOnlyBufferException if buff is read only
 * @see java.nio.ByteBuffer
 * @param buff The ByteBuffer at the position to begin writing
 * @since ??
 */
public void marshal(java.nio.ByteBuffer buff)
{
       buff.putInt( (int)variableDatumID);
       buff.putInt( (int)variableDatums.size() * 64 ); // post-processing patch to fix units; bits rather than bytes

       for(int idx = 0; idx < variableDatums.size(); idx++)
       {
            EightByteChunk aEightByteChunk = (EightByteChunk)variableDatums.get(idx);
            aEightByteChunk.marshal(buff);
       } // end of list marshalling

    } // end of marshal method

/**
 * Unpacks a Pdu from the underlying data.
 * @throws java.nio.BufferUnderflowException if buff is too small
 * @see java.nio.ByteBuffer
 * @param buff The ByteBuffer at the position to begin reading
 * @since ??
 */
public void unmarshal(java.nio.ByteBuffer buff)
{
       variableDatumID = buff.getInt();
       variableDatumLength = buff.getInt();
       int over = variableDatumLength % 64 > 0 ? 1 : 0; // post-processing patch to fix units problem
       variableDatumLength = (variableDatumLength / 64) + over;
       for(int idx = 0; idx < variableDatumLength; idx++)
       {
            EightByteChunk anX = new EightByteChunk();
            anX.unmarshal(buff);
            variableDatums.add(anX);
       }

 } // end of unmarshal method 


 /**
  * The equals method doesn't always work--mostly it works only on classes that consist only of primitives. Be careful.
  */
 public boolean equals(VariableDatum rhs)
 {
     boolean ivarsEqual = true;

    if(rhs.getClass() != this.getClass())
        return false;

     if( ! (variableDatumID == rhs.variableDatumID)) ivarsEqual = false;
     if( ! (variableDatumLength == rhs.variableDatumLength)) ivarsEqual = false;

     for(int idx = 0; idx < variableDatums.size(); idx++)
     {
        if( ! ( variableDatums.get(idx).equals(rhs.variableDatums.get(idx)))) ivarsEqual = false;
     }


    return ivarsEqual;
 }
} // end of class
