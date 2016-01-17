/**
 * Identifies type of object. This is a shorter version of EntityType that omits the specific and extra fields.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.ObjectType = function()
{
   /** Kind of entity */
  this.entityKind = 0;

   /** Domain of entity (air, surface, subsurface, space, etc) */
  this.domain = 0;

   /** country to which the design of the entity is attributed */
  this.country = 0;

   /** category of entity */
  this.category = 0;

   /** subcategory of entity */
  this.subcategory = 0;

} // end of class
