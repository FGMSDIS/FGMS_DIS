/**
 * Section 5.2.7. Specifies the type of muntion fired, the type of warhead, the         type of fuse, the number of rounds fired, and the rate at which the roudns are fired in         rounds per minute.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.BurstDescriptor = function()
{
   /** What munition was used in the burst */
   this.munition = new dis.EntityType(); 

   /** type of warhead */
  this.warhead = 0;

   /** type of fuse used */
  this.fuse = 0;

   /** how many of the munition were fired */
  this.quantity = 0;

   /** rate at which the munition was fired */
  this.rate = 0;

} // end of class
