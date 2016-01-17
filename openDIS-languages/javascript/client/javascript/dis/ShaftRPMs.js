/**
 * Shaft RPMs, used in underwater acoustic clacluations.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.ShaftRPMs = function()
{
   /** Current shaft RPMs */
  this.currentShaftRPMs = 0;

   /** ordered shaft rpms */
  this.orderedShaftRPMs = 0;

   /** rate of change of shaft RPMs */
  this.shaftRPMRateOfChange = 0;

} // end of class
