/**
 * Sectioin 5.3.4.1. Information about someone firing something. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.FirePdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 2;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 2;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** ID of the entity that shot */
   this.firingEntityID = new dis.EntityID(); 

   /** ID of the entity that is being shot at */
   this.targetEntityID = new dis.EntityID(); 

   /** ID of the munition that is being shot */
   this.munitionID = new dis.EntityID(); 

   /** ID of event */
   this.eventID = new dis.EventID(); 

  this.fireMissionIndex = 0;

   /** location of the firing event */
   this.locationInWorldCoordinates = new dis.Vector3Double(); 

   /** Describes munitions used in the firing event */
   this.burstDescriptor = new dis.BurstDescriptor(); 

   /** Velocity of the ammunition */
   this.velocity = new dis.Vector3Float(); 

   /** range to the target. Note the word range is a SQL reserved word. */
  this.rangeToTarget = 0;

} // end of class
