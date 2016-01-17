/**
 * Section 5.2.25. Identifies the type of radio
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.RadioEntityType = function()
{
   /** Kind of entity */
  this.entityKind = 0;

   /** Domain of entity (air, surface, subsurface, space, etc) */
  this.domain = 0;

   /** country to which the design of the entity is attributed */
  this.country = 0;

   /** category of entity */
  this.category = 0;

   /** specific info based on subcategory field */
  this.nomenclatureVersion = 0;

  this.nomenclature = 0;

} // end of class
