#import "EntityID.h"
#import "EventIdentifier.h"
#import "Vector3Float.h"
#import "Vector3Double.h"
#import "MunitionDescriptor.h"
#import "Vector3Float.h"
#import "VariableParameter.h"
#import <Foundation/Foundation.h>
#import "WarfareFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Detonation or impact of munitions, as well as, non-munition explosions, the burst or initial bloom of chaff, and the ignition of a flare shall be indicated. Section 7.3.3  COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface DetonationPdu : WarfareFamilyPdu
{
  /** ID of the expendable entity, Section 7.3.3  */
  EntityID *explodingEntityID; 

  /** ID of event, Section 7.3.3 */
  EventIdentifier *eventID; 

  /** velocity of the munition immediately before detonation/impact, Section 7.3.3  */
  Vector3Float *velocity; 

  /** location of the munition detonation, the expendable detonation, Section 7.3.3  */
  Vector3Double *locationInWorldCoordinates; 

  /** Describes the detonation represented, Section 7.3.3  */
  MunitionDescriptor *descriptor; 

  /** Velocity of the ammunition, Section 7.3.3  */
  Vector3Float *locationOfEntityCoordinates; 

  /** result of the detonation, Section 7.3.3  */
  unsigned char detonationResult; 

  /** How many articulation parameters we have, Section 7.3.3  */
  unsigned char numberOfVariableParameters; 

  /** padding */
  unsigned short pad; 

  /** specify the parameter values for each Variable Parameter record, Section 7.3.3  */
  NSMutableArray *variableParameters; 

}

@property(readwrite, retain) EntityID* explodingEntityID; 
@property(readwrite, retain) EventIdentifier* eventID; 
@property(readwrite, retain) Vector3Float* velocity; 
@property(readwrite, retain) Vector3Double* locationInWorldCoordinates; 
@property(readwrite, retain) MunitionDescriptor* descriptor; 
@property(readwrite, retain) Vector3Float* locationOfEntityCoordinates; 
@property(readwrite, assign) unsigned char detonationResult; 
@property(readwrite, assign) unsigned char numberOfVariableParameters; 
@property(readwrite, assign) unsigned short pad; 
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
