/**
 * Section 5.3.8.3. Communication of a receiver state. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.ReceiverPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 27;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 4;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** ID of the entitythat is the source of the communication */
   this.entityId = new dis.EntityID(); 

   /** particular radio within an entity */
  this.radioId = 0;

   /** encoding scheme used, and enumeration */
  this.receiverState = 0;

   /** padding */
  this.padding1 = 0;

   /** received power */
  this.receivedPoser = 0;

   /** ID of transmitter */
   this.transmitterEntityId = new dis.EntityID(); 

   /** ID of transmitting radio */
  this.transmitterRadioId = 0;

} // end of class
