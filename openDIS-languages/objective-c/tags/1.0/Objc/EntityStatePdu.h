#import "EntityID.h"
#import "EntityType.h"
#import "EntityType.h"
#import "Vector3Float.h"
#import "Vector3Double.h"
#import "Orientation.h"
#import "DeadReckoningParameter.h"
#import "Marking.h"
#import "ArticulationParameter.h"
#import <Foundation/Foundation.h>
#import "EntityInformationFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.3.1. Represents the postion and state of one entity in the world. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface EntityStatePdu : EntityInformationFamilyPdu
{
  /** Unique ID for an entity that is tied to this state information */
  EntityID *entityID; 

  /** What force this entity is affiliated with, eg red, blue, neutral, etc */
  unsigned char forceId; 

  /** How many articulation parameters are in the variable length list */
  char numberOfArticulationParameters; 

  /** Describes the type of entity in the world */
  EntityType *entityType; 

  EntityType *alternativeEntityType; 

  /** Describes the speed of the entity in the world */
  Vector3Float *entityLinearVelocity; 

  /** describes the location of the entity in the world */
  Vector3Double *entityLocation; 

  /** describes the orientation of the entity, in euler angles */
  Orientation *entityOrientation; 

  /** a series of bit flags that are used to help draw the entity, such as smoking, on fire, etc. */
  int entityAppearance; 

  /** parameters used for dead reckoning */
  DeadReckoningParameter *deadReckoningParameters; 

  /** characters that can be used for debugging, or to draw unique strings on the side of entities in the world */
  Marking *marking; 

  /** a series of bit flags */
  int capabilities; 

  /** variable length list of articulation parameters */
  NSMutableArray *articulationParameters; 

}

@property(readwrite, retain) EntityID* entityID; 
@property(readwrite, assign) unsigned char forceId; 
@property(readwrite, assign) char numberOfArticulationParameters; 
@property(readwrite, retain) EntityType* entityType; 
@property(readwrite, retain) EntityType* alternativeEntityType; 
@property(readwrite, retain) Vector3Float* entityLinearVelocity; 
@property(readwrite, retain) Vector3Double* entityLocation; 
@property(readwrite, retain) Orientation* entityOrientation; 
@property(readwrite, assign) int entityAppearance; 
@property(readwrite, retain) DeadReckoningParameter* deadReckoningParameters; 
@property(readwrite, retain) Marking* marking; 
@property(readwrite, assign) int capabilities; 
@property(readwrite, retain) NSMutableArray*articulationParameters; 

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
