#import "GriddedDataPdu.h" 


@implementation GriddedDataPdu

@synthesize environmentalSimulationApplicationID;
@synthesize fieldNumber;
@synthesize pduNumber;
@synthesize pduTotal;
@synthesize coordinateSystem;
@synthesize numberOfGridAxes;
@synthesize constantGrid;
@synthesize environmentType;
@synthesize orientation;
@synthesize sampleTime;
@synthesize totalValues;
@synthesize vectorDimension;
@synthesize padding1;
@synthesize padding2;
@synthesize gridDataList;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:42];
    environmentalSimulationApplicationID = [[EntityID alloc] init];
    fieldNumber = 0;
    pduNumber = 0;
    pduTotal = 0;
    coordinateSystem = 0;
    numberOfGridAxes = 0;
    constantGrid = 0;
    environmentType = [[EntityType alloc] init];
    orientation = [[Orientation alloc] init];
    sampleTime = 0;
    totalValues = 0;
    vectorDimension = 0;
    padding1 = 0;
    padding2 = 0;
    gridDataList = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [environmentalSimulationApplicationID release];
  [environmentType release];
  [orientation release];
  [gridDataList release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [environmentalSimulationApplicationID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:fieldNumber];
    [dataStream writeUnsignedShort:pduNumber];
    [dataStream writeUnsignedShort:pduTotal];
    [dataStream writeUnsignedShort:coordinateSystem];
    [dataStream writeUnsignedByte:[gridDataList count]];
    [dataStream writeUnsignedByte:constantGrid];
    [environmentType marshalUsingStream:dataStream];
    [orientation marshalUsingStream:dataStream];
    [dataStream writeLong:sampleTime];
    [dataStream writeUnsignedInt:totalValues];
    [dataStream writeUnsignedByte:vectorDimension];
    [dataStream writeUnsignedShort:padding1];
    [dataStream writeUnsignedByte:padding2];

     for(int idx = 0; idx < [gridDataList count]; idx++)
     {
        GridAxisRecord* x = [gridDataList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [environmentalSimulationApplicationID unmarshalUsingStream:dataStream];
    fieldNumber = [dataStream readUnsignedShort];
    pduNumber = [dataStream readUnsignedShort];
    pduTotal = [dataStream readUnsignedShort];
    coordinateSystem = [dataStream readUnsignedShort];
    numberOfGridAxes = [dataStream readUnsignedByte];
    constantGrid = [dataStream readUnsignedByte];
    [environmentType unmarshalUsingStream:dataStream];
    [orientation unmarshalUsingStream:dataStream];
    sampleTime = [dataStream readLong];
    totalValues = [dataStream readUnsignedInt];
    vectorDimension = [dataStream readUnsignedByte];
    padding1 = [dataStream readUnsignedShort];
    padding2 = [dataStream readUnsignedByte];

     [gridDataList removeAllObjects];
     for(int idx = 0; idx < numberOfGridAxes; idx++)
     {
        GridAxisRecord* x;
        [x unmarshalUsingStream:dataStream];
        [gridDataList addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [environmentalSimulationApplicationID getMarshalledSize];
   marshalSize = marshalSize + 2;  // fieldNumber
   marshalSize = marshalSize + 2;  // pduNumber
   marshalSize = marshalSize + 2;  // pduTotal
   marshalSize = marshalSize + 2;  // coordinateSystem
   marshalSize = marshalSize + 1;  // numberOfGridAxes
   marshalSize = marshalSize + 1;  // constantGrid
   marshalSize = marshalSize + [environmentType getMarshalledSize];
   marshalSize = marshalSize + [orientation getMarshalledSize];
   marshalSize = marshalSize + 8;  // sampleTime
   marshalSize = marshalSize + 4;  // totalValues
   marshalSize = marshalSize + 1;  // vectorDimension
   marshalSize = marshalSize + 2;  // padding1
   marshalSize = marshalSize + 1;  // padding2

   for(int idx=0; idx < [gridDataList count]; idx++)
   {
        GridAxisRecord* listElement = [gridDataList objectAtIndex:idx];
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
