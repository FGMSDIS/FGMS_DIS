/**
 * Section 5.3.3.1. Represents the postion and state of one entity in the world. This is identical in function to entity state pdu, but generates less garbage to collect in the Java world. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.FastEntityStatePdu = function()
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

   /** The site ID */
  this.site = 0;

   /** The application ID */
  this.application = 0;

   /** the entity ID */
  this.entity = 0;

   /** what force this entity is affiliated with, eg red, blue, neutral, etc */
  this.forceId = 0;

   /** How many articulation parameters are in the variable length list */
  this.numberOfArticulationParameters = 0;

   /** Kind of entity */
  this.entityKind = 0;

   /** Domain of entity (air, surface, subsurface, space, etc) */
  this.domain = 0;

   /** country to which the design of the entity is attributed */
  this.country = 0;

   /** category of entity */
  this.category = 0;

   /** subcategory of entity */
  this.subcategory = 0;

   /** specific info based on subcategory field. Name changed from specific because that is a reserved word in SQL. */
  this.specif = 0;

  this.extra = 0;

   /** Kind of entity */
  this.altEntityKind = 0;

   /** Domain of entity (air, surface, subsurface, space, etc) */
  this.altDomain = 0;

   /** country to which the design of the entity is attributed */
  this.altCountry = 0;

   /** category of entity */
  this.altCategory = 0;

   /** subcategory of entity */
  this.altSubcategory = 0;

   /** specific info based on subcategory field */
  this.altSpecific = 0;

  this.altExtra = 0;

   /** X velo */
  this.xVelocity = 0;

   /** y Value */
  this.yVelocity = 0;

   /** Z value */
  this.zVelocity = 0;

   /** X value */
  this.xLocation = 0;

   /** y Value */
  this.yLocation = 0;

   /** Z value */
  this.zLocation = 0;

  this.psi = 0;

  this.theta = 0;

  this.phi = 0;

   /** a series of bit flags that are used to help draw the entity, such as smoking, on fire, etc. */
  this.entityAppearance = 0;

   /** enumeration of what dead reckoning algorighm to use */
  this.deadReckoningAlgorithm = 0;

   /** other parameters to use in the dead reckoning algorithm */
   /** X value */
  this.xAcceleration = 0;

   /** y Value */
  this.yAcceleration = 0;

   /** Z value */
  this.zAcceleration = 0;

   /** X value */
  this.xAngularVelocity = 0;

   /** y Value */
  this.yAngularVelocity = 0;

   /** Z value */
  this.zAngularVelocity = 0;

   /** characters that can be used for debugging, or to draw unique strings on the side of entities in the world */
   /** a series of bit flags */
  this.capabilities = 0;

   /** variable length list of articulation parameters */
    articulationParameters = new Array();
 
} // end of class
