/**
 * Used in UA PDU
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.AcousticBeamData = function()
{
   /** beam data length */
  this.beamDataLength = 0;

   /** beamIDNumber */
  this.beamIDNumber = 0;

   /** padding */
  this.pad2 = 0;

   /** fundamental data parameters */
   this.fundamentalDataParameters = new dis.AcousticBeamFundamentalParameter(); 

} // end of class
