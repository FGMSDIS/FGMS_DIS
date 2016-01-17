/**
 * Section 5.3.10.3 Information about individual mines within a minefield. This is very, very wrong. UNFINISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.MinefieldDataPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 39;

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

   /** ID of entity making request */
   this.requestingEntityID = new dis.EntityID(); 

   /** Minefield sequence number */
  this.minefieldSequenceNumbeer = 0;

   /** request ID */
  this.requestID = 0;

   /** pdu sequence number */
  this.pduSequenceNumber = 0;

   /** number of pdus in response */
  this.numberOfPdus = 0;

   /** how many mines are in this PDU */
  this.numberOfMinesInThisPdu = 0;

   /** how many sensor type are in this PDU */
  this.numberOfSensorTypes = 0;

   /** padding */
  this.pad2 = 0;

   /** 32 boolean fields */
  this.dataFilter = 0;

   /** Mine type */
   this.mineType = new dis.EntityType(); 

   /** Sensor types, each 16 bits long */
    sensorTypes = new Array();
 
   /** Padding to get things 32-bit aligned. ^^^this is wrong--dyanmically sized padding needed */
  this.pad3 = 0;

   /** Mine locations */
    mineLocation = new Array();
 
} // end of class
