/**
 * Section 5.2.38. Identifies the type of aggregate including kind of entity, domain (surface, subsurface, air, etc) country, category, etc.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.AggregateType = function()
{
   /** Kind of entity */
  this.aggregateKind = 0;

   /** Domain of entity (air, surface, subsurface, space, etc) */
  this.domain = 0;

   /** country to which the design of the entity is attributed */
  this.country = 0;

   /** category of entity */
  this.category = 0;

   /** subcategory of entity */
  this.subcategory = 0;

   /** specific info based on subcategory field, sql has a reserved word for specific */
  this.specificInfo = 0;

  this.extra = 0;

} // end of class
