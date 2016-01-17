#import "MinefieldDataPdu.h" 


@implementation MinefieldDataPdu

@synthesize minefieldID;
@synthesize requestingEntityID;
@synthesize minefieldSequenceNumbeer;
@synthesize requestID;
@synthesize pduSequenceNumber;
@synthesize numberOfPdus;
@synthesize numberOfMinesInThisPdu;
@synthesize numberOfSensorTypes;
@synthesize pad2;
@synthesize dataFilter;
@synthesize mineType;
@synthesize sensorTypes;
@synthesize pad3;
@synthesize mineLocation;

-(id)init
{
  self = [super init];
  if(self)
  {
    pad2 = 0;
    [self setPduType:39];
    minefieldID = [[EntityID alloc] init];
    requestingEntityID = [[EntityID alloc] init];
    minefieldSequenceNumbeer = 0;
    requestID = 0;
    pduSequenceNumber = 0;
    numberOfPdus = 0;
    numberOfMinesInThisPdu = 0;
    numberOfSensorTypes = 0;
    dataFilter = 0;
    mineType = [[EntityType alloc] init];
    sensorTypes = [NSMutableArray arrayWithCapacity:1];
    pad3 = 0;
    mineLocation = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [minefieldID release];
  [requestingEntityID release];
  [mineType release];
  [sensorTypes release];
  [mineLocation release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [minefieldID marshalUsingStream:dataStream];
    [requestingEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:minefieldSequenceNumbeer];
    [dataStream writeUnsignedByte:requestID];
    [dataStream writeUnsignedByte:pduSequenceNumber];
    [dataStream writeUnsignedByte:numberOfPdus];
    [dataStream writeUnsignedByte:[mineLocation count]];
    [dataStream writeUnsignedByte:[sensorTypes count]];
    [dataStream writeUnsignedByte:pad2];
    [dataStream writeUnsignedInt:dataFilter];
    [mineType marshalUsingStream:dataStream];

     for(int idx = 0; idx < [sensorTypes count]; idx++)
     {
        TwoByteChunk* x = [sensorTypes objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

    [dataStream writeUnsignedByte:pad3];

     for(int idx = 0; idx < [mineLocation count]; idx++)
     {
        Vector3Float* x = [mineLocation objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [minefieldID unmarshalUsingStream:dataStream];
    [requestingEntityID unmarshalUsingStream:dataStream];
    minefieldSequenceNumbeer = [dataStream readUnsignedShort];
    requestID = [dataStream readUnsignedByte];
    pduSequenceNumber = [dataStream readUnsignedByte];
    numberOfPdus = [dataStream readUnsignedByte];
    numberOfMinesInThisPdu = [dataStream readUnsignedByte];
    numberOfSensorTypes = [dataStream readUnsignedByte];
    pad2 = [dataStream readUnsignedByte];
    dataFilter = [dataStream readUnsignedInt];
    [mineType unmarshalUsingStream:dataStream];

     [sensorTypes removeAllObjects];
     for(int idx = 0; idx < numberOfSensorTypes; idx++)
     {
        TwoByteChunk* x;
        [x unmarshalUsingStream:dataStream];
        [sensorTypes addObject:x];
     }
    pad3 = [dataStream readUnsignedByte];

     [mineLocation removeAllObjects];
     for(int idx = 0; idx < numberOfMinesInThisPdu; idx++)
     {
        Vector3Float* x;
        [x unmarshalUsingStream:dataStream];
        [mineLocation addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [minefieldID getMarshalledSize];
   marshalSize = marshalSize + [requestingEntityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // minefieldSequenceNumbeer
   marshalSize = marshalSize + 1;  // requestID
   marshalSize = marshalSize + 1;  // pduSequenceNumber
   marshalSize = marshalSize + 1;  // numberOfPdus
   marshalSize = marshalSize + 1;  // numberOfMinesInThisPdu
   marshalSize = marshalSize + 1;  // numberOfSensorTypes
   marshalSize = marshalSize + 1;  // pad2
   marshalSize = marshalSize + 4;  // dataFilter
   marshalSize = marshalSize + [mineType getMarshalledSize];

   for(int idx=0; idx < [sensorTypes count]; idx++)
   {
        TwoByteChunk* listElement = [sensorTypes objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }

   marshalSize = marshalSize + 1;  // pad3

   for(int idx=0; idx < [mineLocation count]; idx++)
   {
        Vector3Float* listElement = [mineLocation objectAtIndex:idx];
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
