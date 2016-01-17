/**
 * Section 5.3.10.4 proivde the means to request a retransmit of a minefield data pdu. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.MinefieldResponseNackPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 40;

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

   /** entity ID making the request */
   this.requestingEntityID = new dis.EntityID(); 

   /** request ID */
  this.requestID = 0;

   /** how many pdus were missing */
  this.numberOfMissingPdus = 0;

   /** PDU sequence numbers that were missing */
    missingPduSequenceNumbers = new Array();
 
} // end of class
