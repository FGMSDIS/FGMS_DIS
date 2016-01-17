/**
 * 5.2.48: Linear segment parameters
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.LinearSegmentParameter = function()
{
   /** number of segments */
  this.segmentNumber = 0;

   /** segment appearance */
   this.segmentAppearance = new dis.SixByteChunk(); 

   /** location */
   this.location = new dis.Vector3Double(); 

   /** orientation */
   this.orientation = new dis.Orientation(); 

   /** segmentLength */
  this.segmentLength = 0;

   /** segmentWidth */
  this.segmentWidth = 0;

   /** segmentHeight */
  this.segmentHeight = 0;

   /** segment Depth */
  this.segmentDepth = 0;

   /** segment Depth */
  this.pad1 = 0;

} // end of class
