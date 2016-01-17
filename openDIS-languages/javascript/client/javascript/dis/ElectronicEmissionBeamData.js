/**
 * Description of one electronic emission beam
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.ElectronicEmissionBeamData = function()
{
   /** This field shall specify the length of this beams data in 32 bit words */
  this.beamDataLength = 0;

   /** This field shall specify a unique emitter database number assigned to differentiate between otherwise similar or identical emitter beams within an emitter system. */
  this.beamIDNumber = 0;

   /** This field shall specify a Beam Parameter Index number that shall be used by receiving entities in conjunction with the Emitter Name field to provide a pointer to the stored database parameters required to regenerate the beam.  */
  this.beamParameterIndex = 0;

   /** Fundamental parameter data such as frequency range, beam sweep, etc. */
   this.fundamentalParameterData = new dis.FundamentalParameterData(); 

   /** beam function of a particular beam */
  this.beamFunction = 0;

   /** Number of track/jam targets */
  this.numberOfTrackJamTargets = 0;

   /** wheher or not the receiving simulation apps can assume all the targets in the scan pattern are being tracked/jammed */
  this.highDensityTrackJam = 0;

   /** padding */
  this.pad4 = 0;

   /** identify jamming techniques used */
  this.jammingModeSequence = 0;

   /** variable length list of track/jam targets */
    trackJamTargets = new Array();
 
} // end of class
