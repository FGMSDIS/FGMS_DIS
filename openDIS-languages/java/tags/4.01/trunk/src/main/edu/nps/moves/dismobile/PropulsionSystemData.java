package edu.nps.moves.dismobile;

import java.util.*;
import java.io.*;
import edu.nps.moves.disenum.*;
import edu.nps.moves.disutil.*;


/**
 * Data about a propulsion system
 *
 * Copyright (c) 2008-2010, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
public class PropulsionSystemData extends Object implements Serializable
{
   /** powerSetting */
   protected float  powerSetting;

   /** engine RPMs */
   protected float  engineRpm;


/** Constructor */
 public PropulsionSystemData()
 {
 }

public int getMarshalledSize()
{
   int marshalSize = 0; 

   marshalSize = marshalSize + 4;  // powerSetting
   marshalSize = marshalSize + 4;  // engineRpm

   return marshalSize;
}


public void setPowerSetting(float pPowerSetting)
{ powerSetting = pPowerSetting;
}

public float getPowerSetting()
{ return powerSetting; 
}

public void setEngineRpm(float pEngineRpm)
{ engineRpm = pEngineRpm;
}

public float getEngineRpm()
{ return engineRpm; 
}


public void marshal(DataOutputStream dos)
{
    try 
    {
       dos.writeFloat( (float)powerSetting);
       dos.writeFloat( (float)engineRpm);
    } // end try 
    catch(Exception e)
    { 
      System.out.println(e);}
    } // end of marshal method

public void unmarshal(DataInputStream dis)
{
    try 
    {
       powerSetting = dis.readFloat();
       engineRpm = dis.readFloat();
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
       buff.putFloat( (float)powerSetting);
       buff.putFloat( (float)engineRpm);
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
       powerSetting = buff.getFloat();
       engineRpm = buff.getFloat();
 } // end of unmarshal method 


 /**
  * The equals method doesn't always work--mostly it works only on classes that consist only of primitives. Be careful.
  */
 public boolean equals(PropulsionSystemData rhs)
 {
     boolean ivarsEqual = true;

    if(rhs.getClass() != this.getClass())
        return false;

     if( ! (powerSetting == rhs.powerSetting)) ivarsEqual = false;
     if( ! (engineRpm == rhs.engineRpm)) ivarsEqual = false;

    return ivarsEqual;
 }
} // end of class
