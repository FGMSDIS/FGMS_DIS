/**
 * Section 5.3.9.2 Information about a particular group of entities grouped together for the purposes of netowrk bandwidth         reduction or aggregation. Needs manual cleanup. The GED size requires a database lookup. UNFINISHED
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.IsGroupOfPdu = function()
{
   /** The version of the protocol. 5=DIS-1995, 6=DIS-1998. */
  this.protocolVersion = 6;

   /** Exercise ID */
  this.exerciseID = 0;

   /** Type of pdu, unique for each PDU class */
  this.pduType = 34;

   /** value that refers to the protocol family, eg SimulationManagement, et */
  this.protocolFamily = 7;

   /** Timestamp value */
  this.timestamp = 0;

   /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word */
  this.pduLength = 0;

   /** zero-filled array of padding */
  this.padding = 0;

   /** ID of aggregated entities */
   this.groupEntityID = new dis.EntityID(); 

   /** type of entities constituting the group */
  this.groupedEntityCategory = 0;

   /** Number of individual entities constituting the group */
  this.numberOfGroupedEntities = 0;

   /** padding */
  this.pad2 = 0;

   /** latitude */
  this.latitude = 0;

   /** longitude */
  this.longitude = 0;

   /** GED records about each individual entity in the group. ^^^this is wrong--need a database lookup to find the actual size of the list elements */
    groupedEntityDescriptions = new Array();
 
} // end of class
