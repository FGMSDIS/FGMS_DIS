#import "EntityID.h"
#import "EntityType.h"
#import "AggregateMarking.h"
#import "Vector3Float.h"
#import "Orientation.h"
#import "Vector3Double.h"
#import "Vector3Float.h"
#import "AggregateID.h"
#import "EntityID.h"
#import "EntityType.h"
#import "EntityType.h"
#import "VariableDatum.h"
#import <Foundation/Foundation.h>
#import "EntityManagementFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.9.1 informationa bout aggregating entities anc communicating information about the aggregated entities.        requires manual intervention to fix the padding between entityID lists and silent aggregate sysem lists--this padding        is dependent on how many entityIDs there are, and needs to be on a 32 bit word boundary. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface AggregateStatePdu : EntityManagementFamilyPdu
{
  /** ID of aggregated entities */
  EntityID *aggregateID; 

  /** force ID */
  unsigned char forceID; 

  /** state of aggregate */
  unsigned char aggregateState; 

  /** entity type of the aggregated entities */
  EntityType *aggregateType; 

  /** formation of aggregated entities */
  unsigned int formation; 

  /** marking for aggregate; first char is charset type, rest is char data */
  AggregateMarking *aggregateMarking; 

  /** dimensions of bounding box for the aggregated entities, origin at the center of mass */
  Vector3Float *dimensions; 

  /** orientation of the bounding box */
  Orientation *orientation; 

  /** center of mass of the aggregation */
  Vector3Double *centerOfMass; 

  /** velocity of aggregation */
  Vector3Float *velocity; 

  /** number of aggregates */
  unsigned short numberOfDisAggregates; 

  /** number of entities */
  unsigned short numberOfDisEntities; 

  /** number of silent aggregate types */
  unsigned short numberOfSilentAggregateTypes; 

  /** number of silent entity types */
  unsigned short numberOfSilentEntityTypes; 

  /** aggregates  list */
  NSMutableArray *aggregateIDList; 

  /** entity ID list */
  NSMutableArray *entityIDList; 

  /** ^^^padding to put the start of the next list on a 32 bit boundary. This needs to be fixed */
  unsigned char pad2; 

  /** silent entity types */
  NSMutableArray *silentAggregateSystemList; 

  /** silent entity types */
  NSMutableArray *silentEntitySystemList; 

  /** number of variable datum records */
  unsigned int numberOfVariableDatumRecords; 

  /** variableDatums */
  NSMutableArray *variableDatumList; 

}

@property(readwrite, retain) EntityID* aggregateID; 
@property(readwrite, assign) unsigned char forceID; 
@property(readwrite, assign) unsigned char aggregateState; 
@property(readwrite, retain) EntityType* aggregateType; 
@property(readwrite, assign) unsigned int formation; 
@property(readwrite, retain) AggregateMarking* aggregateMarking; 
@property(readwrite, retain) Vector3Float* dimensions; 
@property(readwrite, retain) Orientation* orientation; 
@property(readwrite, retain) Vector3Double* centerOfMass; 
@property(readwrite, retain) Vector3Float* velocity; 
@property(readwrite, assign) unsigned short numberOfDisAggregates; 
@property(readwrite, assign) unsigned short numberOfDisEntities; 
@property(readwrite, assign) unsigned short numberOfSilentAggregateTypes; 
@property(readwrite, assign) unsigned short numberOfSilentEntityTypes; 
@property(readwrite, retain) NSMutableArray*aggregateIDList; 
@property(readwrite, retain) NSMutableArray*entityIDList; 
@property(readwrite, assign) unsigned char pad2; 
@property(readwrite, retain) NSMutableArray*silentAggregateSystemList; 
@property(readwrite, retain) NSMutableArray*silentEntitySystemList; 
@property(readwrite, assign) unsigned int numberOfVariableDatumRecords; 
@property(readwrite, retain) NSMutableArray*variableDatumList; 

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
