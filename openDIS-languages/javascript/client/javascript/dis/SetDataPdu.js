/**
 * Section 5.3.6.9. Change state information with the data contained in this. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.SetDataPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 19;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 5;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** Entity that is sending message */
   this.originatingEntityID = new dis.EntityID(); 

   /** Entity that is intended to receive message */
   this.receivingEntityID = new dis.EntityID(); 

   /** ID of request */
  this.requestID = 0;

   /** padding */
  this.padding1 = 0;

   /** Number of fixed datum records */
  this.numberOfFixedDatumRecords = 0;

   /** Number of variable datum records */
  this.numberOfVariableDatumRecords = 0;

   /** variable length list of fixed datums */
    fixedDatums = new Array();
 
   /** variable length list of variable length datums */
    variableDatums = new Array();
 
} // end of class
