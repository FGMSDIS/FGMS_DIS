/**
 * Section 5.3.7.2. Handles designating operations. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.DesignatorPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 24;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 6;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** ID of the entity designating */
   this.designatingEntityID = new dis.EntityID(); 

   /** This field shall specify a unique emitter database number assigned to  differentiate between otherwise similar or identical emitter beams within an emitter system. */
  this.codeName = 0;

   /** ID of the entity being designated */
   this.designatedEntityID = new dis.EntityID(); 

   /** This field shall identify the designator code being used by the designating entity  */
  this.designatorCode = 0;

   /** This field shall identify the designator output power in watts */
  this.designatorPower = 0;

   /** This field shall identify the designator wavelength in units of microns */
  this.designatorWavelength = 0;

   /** designtor spot wrt the designated entity */
   this.designatorSpotWrtDesignated = new dis.Vector3Float(); 

   /** designtor spot wrt the designated entity */
   this.designatorSpotLocation = new dis.Vector3Double(); 

   /** Dead reckoning algorithm */
  this.deadReckoningAlgorithm = 0;

   /** padding */
  this.padding1 = 0;

   /** padding */
  this.padding2 = 0;

   /** linear accelleration of entity */
   this.entityLinearAcceleration = new dis.Vector3Float(); 

} // end of class
