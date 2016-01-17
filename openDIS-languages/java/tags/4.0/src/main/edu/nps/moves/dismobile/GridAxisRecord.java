package edu.nps.moves.dismobile;

import java.util.*;
import java.io.*;
import edu.nps.moves.disenum.*;
import edu.nps.moves.disutil.*;


/**
 * 5.2.44: Grid data record, a common abstract superclass for several subtypes 
 *
 * Copyright (c) 2008-2010, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
public class GridAxisRecord extends Object implements Serializable
{
   /** type of environmental sample */
   protected int  sampleType;

   /** value that describes data representation */
   protected int  dataRepresentation;


/** Constructor */
 public GridAxisRecord()
 {
 }

public int getMarshalledSize()
{
   int marshalSize = 0; 

   marshalSize = marshalSize + 2;  // sampleType
   marshalSize = marshalSize + 2;  // dataRepresentation

   return marshalSize;
}


public void setSampleType(int pSampleType)
{ sampleType = pSampleType;
}

public int getSampleType()
{ return sampleType; 
}

public void setDataRepresentation(int pDataRepresentation)
{ dataRepresentation = pDataRepresentation;
}

public int getDataRepresentation()
{ return dataRepresentation; 
}


public void marshal(DataOutputStream dos)
{
    try 
    {
       dos.writeShort( (short)sampleType);
       dos.writeShort( (short)dataRepresentation);
    } // end try 
    catch(Exception e)
    { 
      System.out.println(e);}
    } // end of marshal method

public void unmarshal(DataInputStream dis)
{
    try 
    {
       sampleType = (int)dis.readUnsignedShort();
       dataRepresentation = (int)dis.readUnsignedShort();
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
       buff.putShort( (short)sampleType);
       buff.putShort( (short)dataRepresentation);
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
       sampleType = (int)(buff.getShort() & 0xFFFF);
       dataRepresentation = (int)(buff.getShort() & 0xFFFF);
 } // end of unmarshal method 


 /**
  * The equals method doesn't always work--mostly it works only on classes that consist only of primitives. Be careful.
  */
 public boolean equals(GridAxisRecord rhs)
 {
     boolean ivarsEqual = true;

    if(rhs.getClass() != this.getClass())
        return false;

     if( ! (sampleType == rhs.sampleType)) ivarsEqual = false;
     if( ! (dataRepresentation == rhs.dataRepresentation)) ivarsEqual = false;

    return ivarsEqual;
 }
} // end of class
