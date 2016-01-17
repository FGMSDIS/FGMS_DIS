/**
 * Section 5.3.7.5. SEES PDU, supplemental emissions entity state information. COMPLETE
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.SeesPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 30;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 6;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** Originating entity ID */
   this.orginatingEntityID = new dis.EntityID(); 

   /** IR Signature representation index */
  this.infraredSignatureRepresentationIndex = 0;

   /** acoustic Signature representation index */
  this.acousticSignatureRepresentationIndex = 0;

   /** radar cross section representation index */
  this.radarCrossSectionSignatureRepresentationIndex = 0;

   /** how many propulsion systems */
  this.numberOfPropulsionSystems = 0;

   /** how many vectoring nozzle systems */
  this.numberOfVectoringNozzleSystems = 0;

   /** variable length list of propulsion system data */
    propulsionSystemData = new Array();
 
   /** variable length list of vectoring system data */
    vectoringSystemData = new Array();
 
} // end of class
