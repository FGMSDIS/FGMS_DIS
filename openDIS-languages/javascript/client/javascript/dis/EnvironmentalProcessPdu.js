/**
 * Section 5.3.11.1: Information about environmental effects and processes. This requires manual cleanup. the environmental        record is variable, as is the padding. UNFINISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.EnvironmentalProcessPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 41;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 9;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** Environmental process ID */
   this.environementalProcessID = new dis.EntityID(); 

   /** Environment type */
   this.environmentType = new dis.EntityType(); 

   /** model type */
  this.modelType = 0;

   /** Environment status */
  this.environmentStatus = 0;

   /** number of environment records  */
  this.numberOfEnvironmentRecords = 0;

   /** PDU sequence number for the environmentla process if pdu sequencing required */
  this.sequenceNumber = 0;

   /** environemt records */
    environmentRecords = new Array();
 
} // end of class
