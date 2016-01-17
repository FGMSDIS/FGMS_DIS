/**
 * Section 5.3.5.2. Information about a request for supplies. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.ResupplyOfferPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 6;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 3;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** Entity that is receiving service */
   this.receivingEntityID = new dis.EntityID(); 

   /** Entity that is supplying */
   this.supplyingEntityID = new dis.EntityID(); 

   /** how many supplies are being offered */
  this.numberOfSupplyTypes = 0;

   /** padding */
  this.padding1 = 0;

   /** padding */
  this.padding2 = 0;

    supplies = new Array();
 
} // end of class
