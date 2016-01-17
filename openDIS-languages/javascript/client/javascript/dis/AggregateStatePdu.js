/**
 * Section 5.3.9.1 informationa bout aggregating entities anc communicating information about the aggregated entities.        requires manual intervention to fix the padding between entityID lists and silent aggregate sysem lists--this padding        is dependent on how many entityIDs there are, and needs to be on a 32 bit word boundary. UNFINISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.AggregateStatePdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 33;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 7;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** ID of aggregated entities */
   this.aggregateID = new dis.EntityID(); 

   /** force ID */
  this.forceID = 0;

   /** state of aggregate */
  this.aggregateState = 0;

   /** entity type of the aggregated entities */
   this.aggregateType = new dis.EntityType(); 

   /** formation of aggregated entities */
  this.formation = 0;

   /** marking for aggregate; first char is charset type, rest is char data */
   this.aggregateMarking = new dis.AggregateMarking(); 

   /** dimensions of bounding box for the aggregated entities, origin at the center of mass */
   this.dimensions = new dis.Vector3Float(); 

   /** orientation of the bounding box */
   this.orientation = new dis.Orientation(); 

   /** center of mass of the aggregation */
   this.centerOfMass = new dis.Vector3Double(); 

   /** velocity of aggregation */
   this.velocity = new dis.Vector3Float(); 

   /** number of aggregates */
  this.numberOfDisAggregates = 0;

   /** number of entities */
  this.numberOfDisEntities = 0;

   /** number of silent aggregate types */
  this.numberOfSilentAggregateTypes = 0;

   /** number of silent entity types */
  this.numberOfSilentEntityTypes = 0;

   /** aggregates  list */
    aggregateIDList = new Array();
 
   /** entity ID list */
    entityIDList = new Array();
 
   /** ^^^padding to put the start of the next list on a 32 bit boundary. This needs to be fixed */
  this.pad2 = 0;

   /** silent entity types */
    silentAggregateSystemList = new Array();
 
   /** silent entity types */
    silentEntitySystemList = new Array();
 
   /** number of variable datum records */
  this.numberOfVariableDatumRecords = 0;

   /** variableDatums */
    variableDatumList = new Array();
 
} // end of class
