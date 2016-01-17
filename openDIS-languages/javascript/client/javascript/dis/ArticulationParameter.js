/**
 * Section 5.2.5. Articulation parameters for  movable parts and attached parts of an entity. Specifes wether or not a change has occured,  the part identifcation of the articulated part to which it is attached, and the type and value of each parameter.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.ArticulationParameter = function()
{
  this.parameterTypeDesignator = 0;

  this.changeIndicator = 0;

  this.partAttachedTo = 0;

  this.parameterType = 0;

  this.parameterValue = 0;

} // end of class
