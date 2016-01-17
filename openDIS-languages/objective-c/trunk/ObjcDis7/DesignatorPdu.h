#import "EntityID.h"
#import "EntityID.h"
#import "Vector3Float.h"
#import "Vector3Double.h"
#import "Vector3Float.h"
#import <Foundation/Foundation.h>
#import "DistributedEmissionsFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.7.2. Handles designating operations. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface DesignatorPdu : DistributedEmissionsFamilyPdu
{
  /** ID of the entity designating */
  EntityID *designatingEntityID; 

  /** This field shall specify a unique emitter database number assigned to  differentiate between otherwise similar or identical emitter beams within an emitter system. */
  unsigned short codeName; 

  /** ID of the entity being designated */
  EntityID *designatedEntityID; 

  /** This field shall identify the designator code being used by the designating entity  */
  unsigned short designatorCode; 

  /** This field shall identify the designator output power in watts */
  float designatorPower; 

  /** This field shall identify the designator wavelength in units of microns */
  float designatorWavelength; 

  /** designtor spot wrt the designated entity */
  Vector3Float *designatorSpotWrtDesignated; 

  /** designtor spot wrt the designated entity */
  Vector3Double *designatorSpotLocation; 

  /** Dead reckoning algorithm */
  char deadReckoningAlgorithm; 

  /** padding */
  unsigned short padding1; 

  /** padding */
  char padding2; 

  /** linear accelleration of entity */
  Vector3Float *entityLinearAcceleration; 

}

@property(readwrite, retain) EntityID* designatingEntityID; 
@property(readwrite, assign) unsigned short codeName; 
@property(readwrite, retain) EntityID* designatedEntityID; 
@property(readwrite, assign) unsigned short designatorCode; 
@property(readwrite, assign) float designatorPower; 
@property(readwrite, assign) float designatorWavelength; 
@property(readwrite, retain) Vector3Float* designatorSpotWrtDesignated; 
@property(readwrite, retain) Vector3Double* designatorSpotLocation; 
@property(readwrite, assign) char deadReckoningAlgorithm; 
@property(readwrite, assign) unsigned short padding1; 
@property(readwrite, assign) char padding2; 
@property(readwrite, retain) Vector3Float* entityLinearAcceleration; 

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
