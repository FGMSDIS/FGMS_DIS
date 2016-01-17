#import "EntityID.h"
#import "EventID.h"
#import "ShaftRPMs.h"
#import "ApaData.h"
#import "AcousticEmitterSystemData.h"
#import <Foundation/Foundation.h>
#import "DistributedEmissionsFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.7.3. Information about underwater acoustic emmissions. This requires manual cleanup.  The beam data records should ALL be a the finish, rather than attached to each emitter system. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface UaPdu : DistributedEmissionsFamilyPdu
{
  /** ID of the entity that is the source of the emission */
  EntityID *emittingEntityID; 

  /** ID of event */
  EventID *eventID; 

  /** This field shall be used to indicate whether the data in the UA PDU represent a state update or data that have changed since issuance of the last UA PDU */
  char stateChangeIndicator; 

  /** padding */
  char pad; 

  /** This field indicates which database record (or file) shall be used in the definition of passive signature (unintentional) emissions of the entity. The indicated database record (or  file) shall define all noise generated as a function of propulsion plant configurations and associated  auxiliaries. */
  unsigned short passiveParameterIndex; 

  /** This field shall specify the entity propulsion plant configuration. This field is used to determine the passive signature characteristics of an entity. */
  unsigned char propulsionPlantConfiguration; 

  /**  This field shall represent the number of shafts on a platform */
  unsigned char numberOfShafts; 

  /** This field shall indicate the number of APAs described in the current UA PDU */
  unsigned char numberOfAPAs; 

  /** This field shall specify the number of UA emitter systems being described in the current UA PDU */
  unsigned char numberOfUAEmitterSystems; 

  /** shaft RPM values */
  NSMutableArray *shaftRPMs; 

  /** apaData */
  NSMutableArray *apaData; 

  NSMutableArray *emitterSystems; 

}

@property(readwrite, retain) EntityID* emittingEntityID; 
@property(readwrite, retain) EventID* eventID; 
@property(readwrite, assign) char stateChangeIndicator; 
@property(readwrite, assign) char pad; 
@property(readwrite, assign) unsigned short passiveParameterIndex; 
@property(readwrite, assign) unsigned char propulsionPlantConfiguration; 
@property(readwrite, assign) unsigned char numberOfShafts; 
@property(readwrite, assign) unsigned char numberOfAPAs; 
@property(readwrite, assign) unsigned char numberOfUAEmitterSystems; 
@property(readwrite, retain) NSMutableArray*shaftRPMs; 
@property(readwrite, retain) NSMutableArray*apaData; 
@property(readwrite, retain) NSMutableArray*emitterSystems; 

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
