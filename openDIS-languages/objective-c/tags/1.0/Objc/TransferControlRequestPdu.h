#import "EntityID.h"
#import "EntityID.h"
#import "EntityID.h"
#import "RecordSet.h"
#import <Foundation/Foundation.h>
#import "EntityManagementFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.9.3 Information initiating the dyanic allocation and control of simulation entities         between two simulation applications. Requires manual cleanup. The padding between record sets is variable. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface TransferControlRequestPdu : EntityManagementFamilyPdu
{
  /** ID of entity originating request */
  EntityID *orginatingEntityID; 

  /** ID of entity receiving request */
  EntityID *recevingEntityID; 

  /** ID ofrequest */
  unsigned int requestID; 

  /** required level of reliabliity service. */
  unsigned char requiredReliabilityService; 

  /** type of transfer desired */
  unsigned char tranferType; 

  /** The entity for which control is being requested to transfer */
  EntityID *transferEntityID; 

  /** number of record sets to transfer */
  unsigned char numberOfRecordSets; 

  /** ^^^This is wrong--the RecordSet class needs more work */
  NSMutableArray *recordSets; 

}

@property(readwrite, retain) EntityID* orginatingEntityID; 
@property(readwrite, retain) EntityID* recevingEntityID; 
@property(readwrite, assign) unsigned int requestID; 
@property(readwrite, assign) unsigned char requiredReliabilityService; 
@property(readwrite, assign) unsigned char tranferType; 
@property(readwrite, retain) EntityID* transferEntityID; 
@property(readwrite, assign) unsigned char numberOfRecordSets; 
@property(readwrite, retain) NSMutableArray*recordSets; 

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
