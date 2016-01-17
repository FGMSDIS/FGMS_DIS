package edu.nps.moves.dismobile;

import java.util.*;
import java.io.*;
import edu.nps.moves.disenum.*;
import edu.nps.moves.disutil.*;


/**
 * Section 5.2.18. Fixed Datum Record
 *
 * Copyright (c) 2008-2010, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
public class FixedDatum extends Object implements Serializable
{
   /** ID of the fixed datum */
   protected long  fixedDatumID;

   /** Value for the fixed datum */
   protected long  fixedDatumValue;


/** Constructor */
 public FixedDatum()
 {
 }

public int getMarshalledSize()
{
   int marshalSize = 0; 

   marshalSize = marshalSize + 4;  // fixedDatumID
   marshalSize = marshalSize + 4;  // fixedDatumValue

   return marshalSize;
}


public void setFixedDatumID(long pFixedDatumID)
{ fixedDatumID = pFixedDatumID;
}

public long getFixedDatumID()
{ return fixedDatumID; 
}

public void setFixedDatumValue(long pFixedDatumValue)
{ fixedDatumValue = pFixedDatumValue;
}

public long getFixedDatumValue()
{ return fixedDatumValue; 
}


public void marshal(DataOutputStream dos)
{
    try 
    {
       dos.writeInt( (int)fixedDatumID);
       dos.writeInt( (int)fixedDatumValue);
    } // end try 
    catch(Exception e)
    { 
      System.out.println(e);}
    } // end of marshal method

public void unmarshal(DataInputStream dis)
{
    try 
    {
       fixedDatumID = dis.readInt();
       fixedDatumValue = dis.readInt();
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
       buff.putInt( (int)fixedDatumID);
       buff.putInt( (int)fixedDatumValue);
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
       fixedDatumID = buff.getInt();
       fixedDatumValue = buff.getInt();
 } // end of unmarshal method 


 /**
  * The equals method doesn't always work--mostly it works only on classes that consist only of primitives. Be careful.
  */
 public boolean equals(FixedDatum rhs)
 {
     boolean ivarsEqual = true;

    if(rhs.getClass() != this.getClass())
        return false;

     if( ! (fixedDatumID == rhs.fixedDatumID)) ivarsEqual = false;
     if( ! (fixedDatumValue == rhs.fixedDatumValue)) ivarsEqual = false;

    return ivarsEqual;
 }
} // end of class
