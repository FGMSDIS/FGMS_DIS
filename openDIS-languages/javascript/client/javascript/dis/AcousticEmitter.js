/**
 * Section 5.2.35. information about a specific UA emmtter
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.AcousticEmitter = function()
{
   /** the system for a particular UA emitter, and an enumeration */
  this.acousticName = 0;

   /** The function of the acoustic system */
  this.function = 0;

   /** The UA emitter identification number relative to a specific system */
  this.acousticIdNumber = 0;

} // end of class
