// Copyright (c) 1995-2009 held by the author(s).  All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
//  are met:
// 
//  * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * Neither the names of the Naval Postgraduate School (NPS)
//  Modeling Virtual Environments and Simulation (MOVES) Institute
// (http://www.nps.edu and http://www.MovesInstitute.org)
// nor the names of its contributors may be used to endorse or
//  promote products derived from this software without specific
// prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Xml.Serialization;
using DISnet.DataStreamUtilities;

namespace DIS1998net
{

/**
 * 5.2.3: location of the radiating portion of the antenna, specified in world coordinates and         entity coordinates.
 *
 * Copyright (c) 2008, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 * Modified for use with C#:
 * Peter Smith (Naval Air Warfare Center - Training Systems Division)
 */
[Serializable]
[XmlRoot]
[XmlInclude(typeof(Vector3Double))]
[XmlInclude(typeof(Vector3Float))]
public class AntennaLocation : Object
{
   /** Location of the radiating portion of the antenna in world    coordinates */
   protected Vector3Double  _antennaLocation = new Vector3Double(); 

   /** Location of the radiating portion of the antenna     in entity coordinates */
   protected Vector3Float  _relativeAntennaLocation = new Vector3Float(); 


/** Constructor */
   ///<summary>
   ///5.2.3: location of the radiating portion of the antenna, specified in world coordinates and         entity coordinates.
   ///</summary>
 public AntennaLocation()
 {
 }

public int getMarshalledSize()
{
   int marshalSize = 0; 

   marshalSize = marshalSize + _antennaLocation.getMarshalledSize();  // _antennaLocation
   marshalSize = marshalSize + _relativeAntennaLocation.getMarshalledSize();  // _relativeAntennaLocation

   return marshalSize;
}


   ///<summary>
   ///Location of the radiating portion of the antenna in world    coordinates
   ///</summary>
public void setAntennaLocation(Vector3Double pAntennaLocation)
{ _antennaLocation = pAntennaLocation;
}

   ///<summary>
   ///Location of the radiating portion of the antenna in world    coordinates
   ///</summary>
public Vector3Double getAntennaLocation()
{ return _antennaLocation; 
}

   ///<summary>
   ///Location of the radiating portion of the antenna in world    coordinates
   ///</summary>
[XmlElement(Type= typeof(Vector3Double), ElementName="antennaLocation")]
public Vector3Double AntennaLocation_
{
     get
{
          return _antennaLocation;
}
     set
{
          _antennaLocation = value;
}
}

   ///<summary>
   ///Location of the radiating portion of the antenna     in entity coordinates
   ///</summary>
public void setRelativeAntennaLocation(Vector3Float pRelativeAntennaLocation)
{ _relativeAntennaLocation = pRelativeAntennaLocation;
}

   ///<summary>
   ///Location of the radiating portion of the antenna     in entity coordinates
   ///</summary>
public Vector3Float getRelativeAntennaLocation()
{ return _relativeAntennaLocation; 
}

   ///<summary>
   ///Location of the radiating portion of the antenna     in entity coordinates
   ///</summary>
[XmlElement(Type= typeof(Vector3Float), ElementName="relativeAntennaLocation")]
public Vector3Float RelativeAntennaLocation
{
     get
{
          return _relativeAntennaLocation;
}
     set
{
          _relativeAntennaLocation = value;
}
}


///<summary>
///Marshal the data to the DataOutputStream.  Note: Length needs to be set before calling this method
///</summary>
public void marshal(DataOutputStream dos)
{
    try 
    {
       _antennaLocation.marshal(dos);
       _relativeAntennaLocation.marshal(dos);
    } // end try 
    catch(Exception e)
    { 
      Trace.WriteLine(e);
      Trace.Flush();
    }
} // end of marshal method

public void unmarshal(DataInputStream dis)
{
    try 
    {
       _antennaLocation.unmarshal(dis);
       _relativeAntennaLocation.unmarshal(dis);
    } // end try 
   catch(Exception e)
    { 
      Trace.WriteLine(e); 
      Trace.Flush();
    }
 } // end of unmarshal method 


   ///<summary>
   ///This allows for a quick display of PDU data.  The current format is unacceptable and only used for debugging.
   ///This will be modified in the future to provide a better display.  Usage: 
   ///pdu.GetType().InvokeMember("reflection", System.Reflection.BindingFlags.InvokeMethod, null, pdu, new object[] { sb });
   ///where pdu is an object representing a single pdu and sb is a StringBuilder.
   ///Note: The supplied Utilities folder contains a method called 'DecodePDU' in the PDUProcessor Class that provides this functionality
   ///</summary>
public void reflection(StringBuilder sb)
{
    sb.Append("<AntennaLocation>"  + System.Environment.NewLine);
    try 
    {
    sb.Append("<antennaLocation>"  + System.Environment.NewLine);
       _antennaLocation.reflection(sb);
    sb.Append("</antennaLocation>"  + System.Environment.NewLine);
    sb.Append("<relativeAntennaLocation>"  + System.Environment.NewLine);
       _relativeAntennaLocation.reflection(sb);
    sb.Append("</relativeAntennaLocation>"  + System.Environment.NewLine);
    sb.Append("</AntennaLocation>"  + System.Environment.NewLine);
    } // end try 
    catch(Exception e)
    { 
      Trace.WriteLine(e);
      Trace.Flush();
}
    } // end of marshal method

        public static bool operator !=(AntennaLocation a, AntennaLocation b)
        {
                return !(a == b);
        }

        public static bool operator ==(AntennaLocation a, AntennaLocation b)
        {
                if (System.Object.ReferenceEquals(a, b))
                {
                      return true;
                }

                if (((object)a == null) || ((object)b == null))
                {
                     return false;
                }

                     return a.equals(b);
        }


 /**
  * The equals method doesn't always work--mostly on on classes that consist only of primitives. Be careful.
  */
 public bool equals(AntennaLocation rhs)
 {
     bool ivarsEqual = true;

    if(rhs.GetType() != this.GetType())
        return false;

     if( ! (_antennaLocation.Equals( rhs._antennaLocation) )) ivarsEqual = false;
     if( ! (_relativeAntennaLocation.Equals( rhs._relativeAntennaLocation) )) ivarsEqual = false;

    return ivarsEqual;
 }
} // end of class
} // end of namespace
