/**
 * Section 5.3.10.2 Query a minefield for information about individual mines. Requires manual clean up to get the padding right. UNFINISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.MinefieldQueryPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 38;

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

   /** EID of entity making the request */
   this.requestingEntityID = new dis.EntityID(); 

   /** request ID */
  this.requestID = 0;

   /** Number of perimeter points for the minefield */
  this.numberOfPerimeterPoints = 0;

   /** Padding */
  this.pad2 = 0;

   /** Number of sensor types */
  this.numberOfSensorTypes = 0;

   /** data filter, 32 boolean fields */
  this.dataFilter = 0;

   /** Entity type of mine being requested */
   this.requestedMineType = new dis.EntityType(); 

   /** perimeter points of request */
    requestedPerimeterPoints = new Array();
 
   /** Sensor types, each 16 bits long */
    sensorTypes = new Array();
 
} // end of class
