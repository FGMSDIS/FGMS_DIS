#import "EntityID.h"
#import "EntityID.h"
#import "EventID.h"
#import "Vector3Float.h"
#import "Vector3Float.h"
#import <Foundation/Foundation.h>
#import "EntityInformationFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.3.2. Information about a collision. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface CollisionPdu : EntityInformationFamilyPdu
{
  /** ID of the entity that issued the collision PDU */
  EntityID *issuingEntityID; 

  /** ID of entity that has collided with the issuing entity ID */
  EntityID *collidingEntityID; 

  /** ID of event */
  EventID *eventID; 

  /** ID of event */
  unsigned char collisionType; 

  /** some padding */
  char pad; 

  /** velocity at collision */
  Vector3Float *velocity; 

  /** mass of issuing entity */
  float mass; 

  /** Location with respect to entity the issuing entity collided with */
  Vector3Float *location; 

}

@property(readwrite, retain) EntityID* issuingEntityID; 
@property(readwrite, retain) EntityID* collidingEntityID; 
@property(readwrite, retain) EventID* eventID; 
@property(readwrite, assign) unsigned char collisionType; 
@property(readwrite, assign) char pad; 
@property(readwrite, retain) Vector3Float* velocity; 
@property(readwrite, assign) float mass; 
@property(readwrite, retain) Vector3Float* location; 

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
