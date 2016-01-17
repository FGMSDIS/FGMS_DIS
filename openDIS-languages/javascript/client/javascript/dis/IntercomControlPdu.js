/**
 * Section 5.3.8.5. Detailed inofrmation about the state of an intercom device and the actions it is requestion         of another intercom device, or the response to a requested action. Required manual intervention to fix the intercom parameters,        which can be of varialbe length. UNFINSISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.IntercomControlPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 32;

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

   /** control type */
  this.controlType = 0;

   /** control type */
  this.communicationsChannelType = 0;

   /** Source entity ID */
   this.sourceEntityID = new dis.EntityID(); 

   /** The specific intercom device being simulated within an entity. */
  this.sourceCommunicationsDeviceID = 0;

   /** Line number to which the intercom control refers */
  this.sourceLineID = 0;

   /** priority of this message relative to transmissons from other intercom devices */
  this.transmitPriority = 0;

   /** current transmit state of the line */
  this.transmitLineState = 0;

   /** detailed type requested. */
  this.command = 0;

   /** eid of the entity that has created this intercom channel. */
   this.masterEntityID = new dis.EntityID(); 

   /** specific intercom device that has created this intercom channel */
  this.masterCommunicationsDeviceID = 0;

   /** number of intercom parameters */
  this.intercomParametersLength = 0;

   /** ^^^This is wrong--the length of the data field is variable. Using a long for now. */
    intercomParameters = new Array();
 
} // end of class
