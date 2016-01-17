/**
 * Section 5.3.10.1 Abstract superclass for PDUs relating to minefields. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.MinefieldStatePdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 37;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 8;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** Minefield ID */
   this.minefieldID = new dis.EntityID(); 

   /** Minefield sequence */
  this.minefieldSequence = 0;

   /** force ID */
  this.forceID = 0;

   /** Number of permieter points */
  this.numberOfPerimeterPoints = 0;

   /** type of minefield */
   this.minefieldType = new dis.EntityType(); 

   /** how many mine types */
  this.numberOfMineTypes = 0;

   /** location of minefield in world coords */
   this.minefieldLocation = new dis.Vector3Double(); 

   /** orientation of minefield */
   this.minefieldOrientation = new dis.Orientation(); 

   /** appearance bitflags */
  this.appearance = 0;

   /** protocolMode */
  this.protocolMode = 0;

   /** perimeter points for the minefield */
    perimeterPoints = new Array();
 
   /** Type of mines */
    mineType = new Array();
 
} // end of class
