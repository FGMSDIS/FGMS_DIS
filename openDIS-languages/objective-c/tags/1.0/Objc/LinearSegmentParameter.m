#import "LinearSegmentParameter.h" 


@implementation LinearSegmentParameter

@synthesize segmentNumber;
@synthesize segmentAppearance;
@synthesize location;
@synthesize orientation;
@synthesize segmentLength;
@synthesize segmentWidth;
@synthesize segmentHeight;
@synthesize segmentDepth;
@synthesize pad1;

-(id)init
{
  self = [super init];
  if(self)
  {
    segmentNumber = 0;
    segmentAppearance = [[SixByteChunk alloc] init];
    location = [[Vector3Double alloc] init];
    orientation = [[Orientation alloc] init];
    segmentLength = 0;
    segmentWidth = 0;
    segmentHeight = 0;
    segmentDepth = 0;
    pad1 = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [segmentAppearance release];
  [location release];
  [orientation release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedByte:segmentNumber];
    [segmentAppearance marshalUsingStream:dataStream];
    [location marshalUsingStream:dataStream];
    [orientation marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:segmentLength];
    [dataStream writeUnsignedShort:segmentWidth];
    [dataStream writeUnsignedShort:segmentHeight];
    [dataStream writeUnsignedShort:segmentDepth];
    [dataStream writeUnsignedInt:pad1];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    segmentNumber = [dataStream readUnsignedByte];
    [segmentAppearance unmarshalUsingStream:dataStream];
    [location unmarshalUsingStream:dataStream];
    [orientation unmarshalUsingStream:dataStream];
    segmentLength = [dataStream readUnsignedShort];
    segmentWidth = [dataStream readUnsignedShort];
    segmentHeight = [dataStream readUnsignedShort];
    segmentDepth = [dataStream readUnsignedShort];
    pad1 = [dataStream readUnsignedInt];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 1;  // segmentNumber
   marshalSize = marshalSize + [segmentAppearance getMarshalledSize];
   marshalSize = marshalSize + [location getMarshalledSize];
   marshalSize = marshalSize + [orientation getMarshalledSize];
   marshalSize = marshalSize + 2;  // segmentLength
   marshalSize = marshalSize + 2;  // segmentWidth
   marshalSize = marshalSize + 2;  // segmentHeight
   marshalSize = marshalSize + 2;  // segmentDepth
   marshalSize = marshalSize + 4;  // pad1
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
