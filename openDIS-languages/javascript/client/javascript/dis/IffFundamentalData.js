/**
 * 5.2.42. Basic operational data ofr IFF ATC NAVAIDS
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.IffFundamentalData = function()
{
   /** system status */
  this.systemStatus = 0;

   /** Alternate parameter 4 */
  this.alternateParameter4 = 0;

   /** eight boolean fields */
  this.informationLayers = 0;

   /** enumeration */
  this.modifier = 0;

   /** parameter, enumeration */
  this.parameter1 = 0;

   /** parameter, enumeration */
  this.parameter2 = 0;

   /** parameter, enumeration */
  this.parameter3 = 0;

   /** parameter, enumeration */
  this.parameter4 = 0;

   /** parameter, enumeration */
  this.parameter5 = 0;

   /** parameter, enumeration */
  this.parameter6 = 0;

} // end of class
