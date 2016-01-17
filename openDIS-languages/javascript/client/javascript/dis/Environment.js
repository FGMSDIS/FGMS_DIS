/**
 * Section 5.2.40. Information about a geometry, a state associated with a geometry, a bounding volume, or an associated entity ID. NOTE: this class requires hand coding.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.Environment = function()
{
   /** Record type */
  this.environmentType = 0;

   /** length, in bits */
  this.length = 0;

   /** Identify the sequentially numbered record index */
  this.recordIndex = 0;

   /** padding */
  this.padding1 = 0;

   /** Geometry or state record */
  this.geometry = 0;

   /** padding to bring the total size up to a 64 bit boundry */
  this.padding2 = 0;

} // end of class
