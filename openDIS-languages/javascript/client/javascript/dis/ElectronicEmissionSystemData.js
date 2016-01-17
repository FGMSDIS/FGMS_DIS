/**
 * Data about one electronic system
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.ElectronicEmissionSystemData = function()
{
   /** This field shall specify the length of this emitter system�s data (including beam data and its track/jam information) in 32-bit words. The length shall include the System Data Length field.  */
  this.systemDataLength = 0;

   /** This field shall specify the number of beams being described in the current PDU for the system being described.  */
  this.numberOfBeams = 0;

   /** padding. */
  this.emissionsPadding2 = 0;

   /** This field shall specify information about a particular emitter system */
   this.emitterSystem = new dis.EmitterSystem(); 

   /** Location with respect to the entity */
   this.location = new dis.Vector3Float(); 

   /** variable length list of beam data records */
    beamDataRecords = new Array();
 
} // end of class
