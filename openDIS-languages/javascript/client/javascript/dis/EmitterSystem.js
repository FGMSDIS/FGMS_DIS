/**
 * Section 5.2.11. This field shall specify information about a particular emitter system
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.EmitterSystem = function()
{
   /** Name of the emitter, 16 bit enumeration */
  this.emitterName = 0;

   /** function of the emitter, 8 bit enumeration */
  this.function = 0;

   /** emitter ID, 8 bit enumeration */
  this.emitterIdNumber = 0;

} // end of class
