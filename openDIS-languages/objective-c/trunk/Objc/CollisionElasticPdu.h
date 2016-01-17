#import "EntityID.h"
#import "EntityID.h"
#import "EventID.h"
#import "Vector3Float.h"
#import "Vector3Float.h"
#import "Vector3Float.h"
#import <Foundation/Foundation.h>
#import "EntityInformationFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// 5.3.3.3. Information about elastic collisions in a DIS exercise shall be communicated using a Collision-Elastic PDU. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface CollisionElasticPdu : EntityInformationFamilyPdu
{
  /** ID of the entity that issued the collision PDU */
  EntityID *issuingEntityID; 

  /** ID of entity that has collided with the issuing entity ID */
  EntityID *collidingEntityID; 

  /** ID of event */
  EventID *collisionEventID; 

  /** some padding */
  short pad; 

  /** velocity at collision */
  Vector3Float *contactVelocity; 

  /** mass of issuing entity */
  float mass; 

  /** Location with respect to entity the issuing entity collided with */
  Vector3Float *location; 

  /** tensor values */
  float collisionResultXX; 

  /** tensor values */
  float collisionResultXY; 

  /** tensor values */
  float collisionResultXZ; 

  /** tensor values */
  float collisionResultYY; 

  /** tensor values */
  float collisionResultYZ; 

  /** tensor values */
  float collisionResultZZ; 

  /** This record shall represent the normal vector to the surface at the point of collision detection. The surface normal shall be represented in world coordinates. */
  Vector3Float *unitSurfaceNormal; 

  /** This field shall represent the degree to which energy is conserved in a collision */
  float coefficientOfRestitution; 

}

@property(readwrite, retain) EntityID* issuingEntityID; 
@property(readwrite, retain) EntityID* collidingEntityID; 
@property(readwrite, retain) EventID* collisionEventID; 
@property(readwrite, assign) short pad; 
@property(readwrite, retain) Vector3Float* contactVelocity; 
@property(readwrite, assign) float mass; 
@property(readwrite, retain) Vector3Float* location; 
@property(readwrite, assign) float collisionResultXX; 
@property(readwrite, assign) float collisionResultXY; 
@property(readwrite, assign) float collisionResultXZ; 
@property(readwrite, assign) float collisionResultYY; 
@property(readwrite, assign) float collisionResultYZ; 
@property(readwrite, assign) float collisionResultZZ; 
@property(readwrite, retain) Vector3Float* unitSurfaceNormal; 
@property(readwrite, assign) float coefficientOfRestitution; 

-(id)init; // Initializer
-(void)dealloc;
-(void)marshalUsingStream:(DataOutput*) dataStream;
-(void)unmarshalUsingStream:(DataInput*) dataStream;

-(int)getMarshalledSize;

@end

// Copyright (c) 1995-2009 held by the author(s).  All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
//  are met:
// 
//  * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * Neither the names of the Naval Postgraduate School (NPS)
//  Modeling Virtual Environments and Simulation (MOVES) Institute
// (http://www.nps.edu and http://www.MovesInstitute.org)
// nor the names of its contributors may be used to endorse or
//  promote products derived from this software without specific
// prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
