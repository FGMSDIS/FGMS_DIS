#import "EntityID.h"
#import "EventIdentifier.h"
#import "EmitterSystem.h"
#import "Vector3Float.h"
#import "Vector3Float.h"
#import <Foundation/Foundation.h>
#import "DistributedEmissionsFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.7.1. Information about active electronic warfare (EW) emissions and active EW countermeasures shall be communicated using an Electromagnetic Emission PDU. NOT COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface ElectronicEmissionsPdu : DistributedEmissionsFamilyPdu
{
  /** ID of the entity emitting */
  EntityID *emittingEntityID; 

  /** ID of event */
  EventIdentifier *eventID; 

  /** This field shall be used to indicate if the data in the PDU represents a state update or just data that has changed since issuance of the last Electromagnetic Emission PDU [relative to the identified entity and emission system(s)]. */
  unsigned char stateUpdateIndicator; 

  /** This field shall specify the number of emission systems being described in the current PDU. */
  unsigned char numberOfSystems; 

  /** padding */
  unsigned short paddingForEmissionsPdu; 

  /**  this field shall specify the length of this emitter system's data in 32-bit words. */
  unsigned char systemDataLength; 

  /** the number of beams being described in the current PDU for the emitter system being described.  */
  unsigned char numberOfBeams; 

  /**  information about a particular emitter system and shall be represented by an Emitter System record (see 6.2.23). */
  EmitterSystem *emitterSystem; 

  /** the location of the antenna beam source with respect to the emitting entity's coordinate system. This location shall be the origin of the emitter coordinate system that shall have the same orientation as the entity coordinate system. This field shall be represented by an Entity Coordinate Vector record see 6.2.95  */
  Vector3Float *location; 

  /** Electronic emmissions systems THIS IS WRONG. It has the WRONG class type and will cause problems in any marshalling. */
  NSMutableArray *systems; 

}

@property(readwrite, retain) EntityID* emittingEntityID; 
@property(readwrite, retain) EventIdentifier* eventID; 
@property(readwrite, assign) unsigned char stateUpdateIndicator; 
@property(readwrite, assign) unsigned char numberOfSystems; 
@property(readwrite, assign) unsigned short paddingForEmissionsPdu; 
@property(readwrite, assign) unsigned char systemDataLength; 
@property(readwrite, assign) unsigned char numberOfBeams; 
@property(readwrite, retain) EmitterSystem* emitterSystem; 
@property(readwrite, retain) Vector3Float* location; 
@property(readwrite, retain) NSMutableArray*systems; 

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
