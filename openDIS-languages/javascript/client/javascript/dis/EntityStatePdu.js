/**
 * Section 5.3.3.1. Represents the postion and state of one entity in the world. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.EntityStatePdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 1;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 1;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** Unique ID for an entity that is tied to this state information */
   this.entityID = new dis.EntityID(); 

   /** What force this entity is affiliated with, eg red, blue, neutral, etc */
  this.forceId = 0;

   /** How many articulation parameters are in the variable length list */
  this.numberOfArticulationParameters = 0;

   /** Describes the type of entity in the world */
   this.entityType = new dis.EntityType(); 

   this.alternativeEntityType = new dis.EntityType(); 

   /** Describes the speed of the entity in the world */
   this.entityLinearVelocity = new dis.Vector3Float(); 

   /** describes the location of the entity in the world */
   this.entityLocation = new dis.Vector3Double(); 

   /** describes the orientation of the entity, in euler angles */
   this.entityOrientation = new dis.Orientation(); 

   /** a series of bit flags that are used to help draw the entity, such as smoking, on fire, etc. */
  this.entityAppearance = 0;

   /** parameters used for dead reckoning */
   this.deadReckoningParameters = new dis.DeadReckoningParameter(); 

   /** characters that can be used for debugging, or to draw unique strings on the side of entities in the world */
   this.marking = new dis.Marking(); 

   /** a series of bit flags */
  this.capabilities = 0;

   /** variable length list of articulation parameters */
    articulationParameters = new Array();
 
} // end of class
