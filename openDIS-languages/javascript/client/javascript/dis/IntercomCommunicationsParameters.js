/**
 * 5.2.46.  Intercom communcations parameters
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.IntercomCommunicationsParameters = function()
{
   /** Type of intercom parameters record */
  this.recordType = 0;

   /** length of record */
  this.recordLength = 0;

   /** Jerks. Looks like the committee is forcing a lookup of the record type parameter to find out how long the field is. This is a placeholder. */
  this.recordSpecificField = 0;

} // end of class
