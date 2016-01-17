/**
 * represents values used in dead reckoning algorithms
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.DeadReckoningParameter = function()
{
   /** enumeration of what dead reckoning algorighm to use */
  this.deadReckoningAlgorithm = 0;

   /** other parameters to use in the dead reckoning algorithm */
   /** Linear acceleration of the entity */
   this.entityLinearAcceleration = new dis.Vector3Float(); 

   /** angular velocity of the entity */
   this.entityAngularVelocity = new dis.Vector3Float(); 

} // end of class
