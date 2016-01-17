#import "MinefieldQueryPdu.h" 


@implementation MinefieldQueryPdu

@synthesize minefieldID;
@synthesize requestingEntityID;
@synthesize requestID;
@synthesize numberOfPerimeterPoints;
@synthesize pad2;
@synthesize numberOfSensorTypes;
@synthesize dataFilter;
@synthesize requestedMineType;
@synthesize requestedPerimeterPoints;
@synthesize sensorTypes;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:38];
    minefieldID = [[EntityID alloc] init];
    requestingEntityID = [[EntityID alloc] init];
    requestID = 0;
    numberOfPerimeterPoints = 0;
    pad2 = 0;
    numberOfSensorTypes = 0;
    dataFilter = 0;
    requestedMineType = [[EntityType alloc] init];
    requestedPerimeterPoints = [NSMutableArray arrayWithCapacity:1];
    sensorTypes = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [minefieldID release];
  [requestingEntityID release];
  [requestedMineType release];
  [requestedPerimeterPoints release];
  [sensorTypes release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [minefieldID marshalUsingStream:dataStream];
    [requestingEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:requestID];
    [dataStream writeUnsignedByte:[requestedPerimeterPoints count]];
    [dataStream writeUnsignedByte:pad2];
    [dataStream writeUnsignedByte:[sensorTypes count]];
    [dataStream writeUnsignedInt:dataFilter];
    [requestedMineType marshalUsingStream:dataStream];

     for(int idx = 0; idx < [requestedPerimeterPoints count]; idx++)
     {
        Point* x = [requestedPerimeterPoints objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [sensorTypes count]; idx++)
     {
        TwoByteChunk* x = [sensorTypes objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [minefieldID unmarshalUsingStream:dataStream];
    [requestingEntityID unmarshalUsingStream:dataStream];
    requestID = [dataStream readUnsignedByte];
    numberOfPerimeterPoints = [dataStream readUnsignedByte];
    pad2 = [dataStream readUnsignedByte];
    numberOfSensorTypes = [dataStream readUnsignedByte];
    dataFilter = [dataStream readUnsignedInt];
    [requestedMineType unmarshalUsingStream:dataStream];

     [requestedPerimeterPoints removeAllObjects];
     for(int idx = 0; idx < numberOfPerimeterPoints; idx++)
     {
        Point* x;
        [x unmarshalUsingStream:dataStream];
        [requestedPerimeterPoints addObject:x];
     }

     [sensorTypes removeAllObjects];
     for(int idx = 0; idx < numberOfSensorTypes; idx++)
     {
        TwoByteChunk* x;
        [x unmarshalUsingStream:dataStream];
        [sensorTypes addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [minefieldID getMarshalledSize];
   marshalSize = marshalSize + [requestingEntityID getMarshalledSize];
   marshalSize = marshalSize + 1;  // requestID
   marshalSize = marshalSize + 1;  // numberOfPerimeterPoints
   marshalSize = marshalSize + 1;  // pad2
   marshalSize = marshalSize + 1;  // numberOfSensorTypes
   marshalSize = marshalSize + 4;  // dataFilter
   marshalSize = marshalSize + [requestedMineType getMarshalledSize];

   for(int idx=0; idx < [requestedPerimeterPoints count]; idx++)
   {
        Point* listElement = [requestedPerimeterPoints objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [sensorTypes count]; idx++)
   {
        TwoByteChunk* listElement = [sensorTypes objectAtIndex:idx];
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
