#import "IntercomSignalPdu.h" 


@implementation IntercomSignalPdu

@synthesize entityID;
@synthesize communicationsDeviceID;
@synthesize encodingScheme;
@synthesize tdlType;
@synthesize sampleRate;
@synthesize dataLength;
@synthesize samples;
@synthesize data;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:31];
    entityID = [[EntityID alloc] init];
    communicationsDeviceID = 0;
    encodingScheme = 0;
    tdlType = 0;
    sampleRate = 0;
    dataLength = 0;
    samples = 0;
    data = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [entityID release];
  [data release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [entityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:communicationsDeviceID];
    [dataStream writeUnsignedShort:encodingScheme];
    [dataStream writeUnsignedShort:tdlType];
    [dataStream writeUnsignedInt:sampleRate];
    [dataStream writeUnsignedShort:[data count]];
    [dataStream writeUnsignedShort:samples];

     for(int idx = 0; idx < [data count]; idx++)
     {
        OneByteChunk* x = [data objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [entityID unmarshalUsingStream:dataStream];
    communicationsDeviceID = [dataStream readUnsignedShort];
    encodingScheme = [dataStream readUnsignedShort];
    tdlType = [dataStream readUnsignedShort];
    sampleRate = [dataStream readUnsignedInt];
    dataLength = [dataStream readUnsignedShort];
    samples = [dataStream readUnsignedShort];

     [data removeAllObjects];
     for(int idx = 0; idx < dataLength; idx++)
     {
        OneByteChunk* x;
        [x unmarshalUsingStream:dataStream];
        [data addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [entityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // communicationsDeviceID
   marshalSize = marshalSize + 2;  // encodingScheme
   marshalSize = marshalSize + 2;  // tdlType
   marshalSize = marshalSize + 4;  // sampleRate
   marshalSize = marshalSize + 2;  // dataLength
   marshalSize = marshalSize + 2;  // samples

   for(int idx=0; idx < [data count]; idx++)
   {
        OneByteChunk* listElement = [data objectAtIndex:idx];
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
