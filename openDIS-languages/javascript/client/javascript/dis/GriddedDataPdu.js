/**
 * Section 5.3.11.2: Information about globat, spatially varying enviornmental effects. This requires manual cleanup; the grid axis        records are variable sized. UNFINISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.GriddedDataPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 42;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 9;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** environmental simulation application ID */
   this.environmentalSimulationApplicationID = new dis.EntityID(); 

   /** unique identifier for each piece of enviornmental data */
  this.fieldNumber = 0;

   /** sequence number for the total set of PDUS used to transmit the data */
  this.pduNumber = 0;

   /** Total number of PDUS used to transmit the data */
  this.pduTotal = 0;

   /** coordinate system of the grid */
  this.coordinateSystem = 0;

   /** number of grid axes for the environmental data */
  this.numberOfGridAxes = 0;

   /** are domain grid axes identidal to those of the priveious domain update? */
  this.constantGrid = 0;

   /** type of environment */
   this.environmentType = new dis.EntityType(); 

   /** orientation of the data grid */
   this.orientation = new dis.Orientation(); 

   /** valid time of the enviormental data sample, 64 bit unsigned int */
  this.sampleTime = 0;

   /** total number of all data values for all pdus for an environmental sample */
  this.totalValues = 0;

   /** total number of data values at each grid point. */
  this.vectorDimension = 0;

   /** padding */
  this.padding1 = 0;

   /** padding */
  this.padding2 = 0;

   /** Grid data ^^^This is wrong */
    gridDataList = new Array();
 
} // end of class
