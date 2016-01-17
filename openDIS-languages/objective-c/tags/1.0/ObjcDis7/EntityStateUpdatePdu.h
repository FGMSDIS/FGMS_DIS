#import "EntityID.h"
#import "Vector3Float.h"
#import "Vector3Double.h"
#import "EulerAngles.h"
#import "VariableParameter.h"
#import <Foundation/Foundation.h>
#import "EntityInformationFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Nonstatic information about a particular entity may be communicated by issuing an Entity State Update PDU. Section 7.2.5. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface EntityStateUpdatePdu : EntityInformationFamilyPdu
{
  /** This field shall identify the entity issuing the PDU, and shall be represented by an Entity Identifier record (see 6.2.28). */
  EntityID *entityID; 

  /** Padding */
  char padding1; 

  /** This field shall specify the number of variable parameters present. This field shall be represented by an 8-bit unsigned integer (see Annex I). */
  unsigned char numberOfVariableParameters; 

  /** This field shall specify an entity’s linear velocity. The coordinate system for an entity’s linear velocity depends on the dead reckoning algorithm used. This field shall be represented by a Linear Velocity Vector record [see 6.2.95 item c)]). */
  Vector3Float *entityLinearVelocity; 

  /** This field shall specify an entity’s physical location in the simulated world and shall be represented by a World Coordinates record (see 6.2.97). */
  Vector3Double *entityLocation; 

  /** This field shall specify an entity’s orientation and shall be represented by an Euler Angles record (see 6.2.33). */
  EulerAngles *entityOrientation; 

  /** This field shall specify the dynamic changes to the entity’s appearance attributes. This field shall be represented by an Entity Appearance record (see 6.2.26). */
  unsigned int entityAppearance; 

  /** This field shall specify the parameter values for each Variable Parameter record that is included (see 6.2.93 and Annex I). */
  NSMutableArray *variableParameters; 

}

@property(readwrite, retain) EntityID* entityID; 
@property(readwrite, assign) char padding1; 
@property(readwrite, assign) unsigned char numberOfVariableParameters; 
@property(readwrite, retain) Vector3Float* entityLinearVelocity; 
@property(readwrite, retain) Vector3Double* entityLocation; 
@property(readwrite, retain) EulerAngles* entityOrientation; 
@property(readwrite, assign) unsigned int entityAppearance; 
@property(readwrite, retain) NSMutableArray*variableParameters; 

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
