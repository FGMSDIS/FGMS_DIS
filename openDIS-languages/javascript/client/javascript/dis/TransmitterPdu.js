/**
 * Section 5.3.8.1. Detailed information about a radio transmitter. This PDU requires manually         written code to complete, since the modulation parameters are of variable length. UNFINISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.TransmitterPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 25;

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

   /** linear accelleration of entity */
   this.radioEntityType = new dis.RadioEntityType(); 

   /** transmit state */
  this.transmitState = 0;

   /** input source */
  this.inputSource = 0;

   /** padding */
  this.padding1 = 0;

   /** Location of antenna */
   this.antennaLocation = new dis.Vector3Double(); 

   /** relative location of antenna */
   this.relativeAntennaLocation = new dis.Vector3Float(); 

   /** antenna pattern type */
  this.antennaPatternType = 0;

   /** atenna pattern length */
  this.antennaPatternCount = 0;

   /** frequency */
  this.frequency = 0;

   /** transmit frequency Bandwidth */
  this.transmitFrequencyBandwidth = 0;

   /** transmission power */
  this.power = 0;

   /** modulation */
   this.modulationType = new dis.ModulationType(); 

   /** crypto system enumeration */
  this.cryptoSystem = 0;

   /** crypto system key identifer */
  this.cryptoKeyId = 0;

   /** how many modulation parameters we have */
  this.modulationParameterCount = 0;

   /** padding2 */
  this.padding2 = 0;

   /** padding3 */
  this.padding3 = 0;

   /** variable length list of modulation parameters */
    modulationParametersList = new Array();
 
   /** variable length list of antenna pattern records */
    antennaPatternList = new Array();
 
} // end of class
