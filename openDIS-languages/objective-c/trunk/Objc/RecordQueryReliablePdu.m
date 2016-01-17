#import "RecordQueryReliablePdu.h" 


@implementation RecordQueryReliablePdu

@synthesize requestID;
@synthesize requiredReliabilityService;
@synthesize pad1;
@synthesize pad2;
@synthesize eventType;
@synthesize time;
@synthesize numberOfRecords;
@synthesize recordIDs;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:63];
    requestID = 0;
    requiredReliabilityService = 0;
    pad1 = 0;
    pad2 = 0;
    eventType = 0;
    time = 0;
    numberOfRecords = 0;
    recordIDs = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [recordIDs release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [dataStream writeUnsignedInt:requestID];
    [dataStream writeUnsignedByte:requiredReliabilityService];
    [dataStream writeUnsignedShort:pad1];
    [dataStream writeUnsignedByte:pad2];
    [dataStream writeUnsignedShort:eventType];
    [dataStream writeUnsignedInt:time];
    [dataStream writeUnsignedInt:[recordIDs count]];

     for(int idx = 0; idx < [recordIDs count]; idx++)
     {
        FourByteChunk* x = [recordIDs objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    requestID = [dataStream readUnsignedInt];
    requiredReliabilityService = [dataStream readUnsignedByte];
    pad1 = [dataStream readUnsignedShort];
    pad2 = [dataStream readUnsignedByte];
    eventType = [dataStream readUnsignedShort];
    time = [dataStream readUnsignedInt];
    numberOfRecords = [dataStream readUnsignedInt];

     [recordIDs removeAllObjects];
     for(int idx = 0; idx < numberOfRecords; idx++)
     {
        FourByteChunk* x;
        [x unmarshalUsingStream:dataStream];
        [recordIDs addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + 4;  // requestID
   marshalSize = marshalSize + 1;  // requiredReliabilityService
   marshalSize = marshalSize + 2;  // pad1
   marshalSize = marshalSize + 1;  // pad2
   marshalSize = marshalSize + 2;  // eventType
   marshalSize = marshalSize + 4;  // time
   marshalSize = marshalSize + 4;  // numberOfRecords

   for(int idx=0; idx < [recordIDs count]; idx++)
   {
        FourByteChunk* listElement = [recordIDs objectAtIndex:idx];
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
