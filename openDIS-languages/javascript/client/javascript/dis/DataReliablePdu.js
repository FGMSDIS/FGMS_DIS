/**
 * Section 5.3.12.10: issued in response to a data query R or set dataR pdu. Needs manual intervention      to fix padding on variable datums. UNFINSIHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.DataReliablePdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 60;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 10;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** Object originatig the request */
   this.originatingEntityID = new dis.EntityID(); 

   /** Object with which this point object is associated */
   this.receivingEntityID = new dis.EntityID(); 

   /** Request ID */
  this.requestID = 0;

   /** level of reliability service used for this transaction */
  this.requiredReliabilityService = 0;

   /** padding */
  this.pad1 = 0;

   /** padding */
  this.pad2 = 0;

   /** Fixed datum record count */
  this.numberOfFixedDatumRecords = 0;

   /** variable datum record count */
  this.numberOfVariableDatumRecords = 0;

   /** Fixed datum records */
    fixedDatumRecords = new Array();
 
   /** Variable datum records */
    variableDatumRecords = new Array();
 
} // end of class
