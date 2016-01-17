/**
 * 5.2.58. Used in IFF ATC PDU
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.SystemID = function()
{
   /** System Type */
  this.systemType = 0;

   /** System name, an enumeration */
  this.systemName = 0;

   /** System mode */
  this.systemMode = 0;

   /** Change Options */
  this.changeOptions = 0;

} // end of class
