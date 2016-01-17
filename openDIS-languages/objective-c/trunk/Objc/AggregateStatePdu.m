#import "AggregateStatePdu.h" 


@implementation AggregateStatePdu

@synthesize aggregateID;
@synthesize forceID;
@synthesize aggregateState;
@synthesize aggregateType;
@synthesize formation;
@synthesize aggregateMarking;
@synthesize dimensions;
@synthesize orientation;
@synthesize centerOfMass;
@synthesize velocity;
@synthesize numberOfDisAggregates;
@synthesize numberOfDisEntities;
@synthesize numberOfSilentAggregateTypes;
@synthesize numberOfSilentEntityTypes;
@synthesize aggregateIDList;
@synthesize entityIDList;
@synthesize pad2;
@synthesize silentAggregateSystemList;
@synthesize silentEntitySystemList;
@synthesize numberOfVariableDatumRecords;
@synthesize variableDatumList;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:33];
    aggregateID = [[EntityID alloc] init];
    forceID = 0;
    aggregateState = 0;
    aggregateType = [[EntityType alloc] init];
    formation = 0;
    aggregateMarking = [[AggregateMarking alloc] init];
    dimensions = [[Vector3Float alloc] init];
    orientation = [[Orientation alloc] init];
    centerOfMass = [[Vector3Double alloc] init];
    velocity = [[Vector3Float alloc] init];
    numberOfDisAggregates = 0;
    numberOfDisEntities = 0;
    numberOfSilentAggregateTypes = 0;
    numberOfSilentEntityTypes = 0;
    aggregateIDList = [NSMutableArray arrayWithCapacity:1];
    entityIDList = [NSMutableArray arrayWithCapacity:1];
    pad2 = 0;
    silentAggregateSystemList = [NSMutableArray arrayWithCapacity:1];
    silentEntitySystemList = [NSMutableArray arrayWithCapacity:1];
    numberOfVariableDatumRecords = 0;
    variableDatumList = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [aggregateID release];
  [aggregateType release];
  [aggregateMarking release];
  [dimensions release];
  [orientation release];
  [centerOfMass release];
  [velocity release];
  [aggregateIDList release];
  [entityIDList release];
  [silentAggregateSystemList release];
  [silentEntitySystemList release];
  [variableDatumList release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [aggregateID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:forceID];
    [dataStream writeUnsignedByte:aggregateState];
    [aggregateType marshalUsingStream:dataStream];
    [dataStream writeUnsignedInt:formation];
    [aggregateMarking marshalUsingStream:dataStream];
    [dimensions marshalUsingStream:dataStream];
    [orientation marshalUsingStream:dataStream];
    [centerOfMass marshalUsingStream:dataStream];
    [velocity marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:[aggregateIDList count]];
    [dataStream writeUnsignedShort:[entityIDList count]];
    [dataStream writeUnsignedShort:[silentAggregateSystemList count]];
    [dataStream writeUnsignedShort:[silentEntitySystemList count]];

     for(int idx = 0; idx < [aggregateIDList count]; idx++)
     {
        AggregateID* x = [aggregateIDList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [entityIDList count]; idx++)
     {
        EntityID* x = [entityIDList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

    [dataStream writeUnsignedByte:pad2];

     for(int idx = 0; idx < [silentAggregateSystemList count]; idx++)
     {
        EntityType* x = [silentAggregateSystemList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [silentEntitySystemList count]; idx++)
     {
        EntityType* x = [silentEntitySystemList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

    [dataStream writeUnsignedInt:[variableDatumList count]];

     for(int idx = 0; idx < [variableDatumList count]; idx++)
     {
        VariableDatum* x = [variableDatumList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [aggregateID unmarshalUsingStream:dataStream];
    forceID = [dataStream readUnsignedByte];
    aggregateState = [dataStream readUnsignedByte];
    [aggregateType unmarshalUsingStream:dataStream];
    formation = [dataStream readUnsignedInt];
    [aggregateMarking unmarshalUsingStream:dataStream];
    [dimensions unmarshalUsingStream:dataStream];
    [orientation unmarshalUsingStream:dataStream];
    [centerOfMass unmarshalUsingStream:dataStream];
    [velocity unmarshalUsingStream:dataStream];
    numberOfDisAggregates = [dataStream readUnsignedShort];
    numberOfDisEntities = [dataStream readUnsignedShort];
    numberOfSilentAggregateTypes = [dataStream readUnsignedShort];
    numberOfSilentEntityTypes = [dataStream readUnsignedShort];

     [aggregateIDList removeAllObjects];
     for(int idx = 0; idx < numberOfDisAggregates; idx++)
     {
        AggregateID* x;
        [x unmarshalUsingStream:dataStream];
        [aggregateIDList addObject:x];
     }

     [entityIDList removeAllObjects];
     for(int idx = 0; idx < numberOfDisEntities; idx++)
     {
        EntityID* x;
        [x unmarshalUsingStream:dataStream];
        [entityIDList addObject:x];
     }
    pad2 = [dataStream readUnsignedByte];

     [silentAggregateSystemList removeAllObjects];
     for(int idx = 0; idx < numberOfSilentAggregateTypes; idx++)
     {
        EntityType* x;
        [x unmarshalUsingStream:dataStream];
        [silentAggregateSystemList addObject:x];
     }

     [silentEntitySystemList removeAllObjects];
     for(int idx = 0; idx < numberOfSilentEntityTypes; idx++)
     {
        EntityType* x;
        [x unmarshalUsingStream:dataStream];
        [silentEntitySystemList addObject:x];
     }
    numberOfVariableDatumRecords = [dataStream readUnsignedInt];

     [variableDatumList removeAllObjects];
     for(int idx = 0; idx < numberOfVariableDatumRecords; idx++)
     {
        VariableDatum* x;
        [x unmarshalUsingStream:dataStream];
        [variableDatumList addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [aggregateID getMarshalledSize];
   marshalSize = marshalSize + 1;  // forceID
   marshalSize = marshalSize + 1;  // aggregateState
   marshalSize = marshalSize + [aggregateType getMarshalledSize];
   marshalSize = marshalSize + 4;  // formation
   marshalSize = marshalSize + [aggregateMarking getMarshalledSize];
   marshalSize = marshalSize + [dimensions getMarshalledSize];
   marshalSize = marshalSize + [orientation getMarshalledSize];
   marshalSize = marshalSize + [centerOfMass getMarshalledSize];
   marshalSize = marshalSize + [velocity getMarshalledSize];
   marshalSize = marshalSize + 2;  // numberOfDisAggregates
   marshalSize = marshalSize + 2;  // numberOfDisEntities
   marshalSize = marshalSize + 2;  // numberOfSilentAggregateTypes
   marshalSize = marshalSize + 2;  // numberOfSilentEntityTypes

   for(int idx=0; idx < [aggregateIDList count]; idx++)
   {
        AggregateID* listElement = [aggregateIDList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [entityIDList count]; idx++)
   {
        EntityID* listElement = [entityIDList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }

   marshalSize = marshalSize + 1;  // pad2

   for(int idx=0; idx < [silentAggregateSystemList count]; idx++)
   {
        EntityType* listElement = [silentAggregateSystemList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [silentEntitySystemList count]; idx++)
   {
        EntityType* listElement = [silentEntitySystemList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }

   marshalSize = marshalSize + 4;  // numberOfVariableDatumRecords

   for(int idx=0; idx < [variableDatumList count]; idx++)
   {
        VariableDatum* listElement = [variableDatumList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }

    return marshalSize;
}

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
