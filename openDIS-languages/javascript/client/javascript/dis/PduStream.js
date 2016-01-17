/**
 * Non-DIS class, used on SQL databases
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.PduStream = function()
{
   /** Longish description of this PDU stream */
   /** short description of this PDU stream */
   /** Start time of recording, in Unix time */
  this.startTime = 0;

   /** stop time of recording, in Unix time */
  this.stopTime = 0;

} // end of class
