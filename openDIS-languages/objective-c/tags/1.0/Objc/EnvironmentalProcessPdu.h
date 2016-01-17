#import "EntityID.h"
#import "EntityType.h"
#import "Environment.h"
#import <Foundation/Foundation.h>
#import "SyntheticEnvironmentFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.11.1: Information about environmental effects and processes. This requires manual cleanup. the environmental        record is variable, as is the padding. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface EnvironmentalProcessPdu : SyntheticEnvironmentFamilyPdu
{
  /** Environmental process ID */
  EntityID *environementalProcessID; 

  /** Environment type */
  EntityType *environmentType; 

  /** model type */
  unsigned char modelType; 

  /** Environment status */
  unsigned char environmentStatus; 

  /** number of environment records  */
  unsigned char numberOfEnvironmentRecords; 

  /** PDU sequence number for the environmentla process if pdu sequencing required */
  unsigned short sequenceNumber; 

  /** environemt records */
  NSMutableArray *environmentRecords; 

}

@property(readwrite, retain) EntityID* environementalProcessID; 
@property(readwrite, retain) EntityType* environmentType; 
@property(readwrite, assign) unsigned char modelType; 
@property(readwrite, assign) unsigned char environmentStatus; 
@property(readwrite, assign) unsigned char numberOfEnvironmentRecords; 
@property(readwrite, assign) unsigned short sequenceNumber; 
@property(readwrite, retain) NSMutableArray*environmentRecords; 

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
