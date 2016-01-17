#import "LinearSegmentParameter.h" 


@implementation LinearSegmentParameter

@synthesize segmentNumber;
@synthesize segmentModification;
@synthesize generalSegmentAppearance;
@synthesize specificSegmentAppearance;
@synthesize segmentLocation;
@synthesize segmentOrientation;
@synthesize segmentLength;
@synthesize segmentWidth;
@synthesize segmentHeight;
@synthesize segmentDepth;

-(id)init
{
  self = [super init];
  if(self)
  {
    segmentNumber = 0;
    segmentModification = 0;
    generalSegmentAppearance = 0;
    specificSegmentAppearance = 0;
    segmentLocation = [[Vector3Double alloc] init];
    segmentOrientation = [[EulerAngles alloc] init];
    segmentLength = 0;
    segmentWidth = 0;
    segmentHeight = 0;
    segmentDepth = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [segmentLocation release];
  [segmentOrientation release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedByte:segmentNumber];
    [dataStream writeUnsignedByte:segmentModification];
    [dataStream writeUnsignedShort:generalSegmentAppearance];
    [dataStream writeUnsignedShort:specificSegmentAppearance];
    [segmentLocation marshalUsingStream:dataStream];
    [segmentOrientation marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:segmentLength];
    [dataStream writeUnsignedShort:segmentWidth];
    [dataStream writeUnsignedShort:segmentHeight];
    [dataStream writeUnsignedShort:segmentDepth];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    segmentNumber = [dataStream readUnsignedByte];
    segmentModification = [dataStream readUnsignedByte];
    generalSegmentAppearance = [dataStream readUnsignedShort];
    specificSegmentAppearance = [dataStream readUnsignedShort];
    [segmentLocation unmarshalUsingStream:dataStream];
    [segmentOrientation unmarshalUsingStream:dataStream];
    segmentLength = [dataStream readUnsignedShort];
    segmentWidth = [dataStream readUnsignedShort];
    segmentHeight = [dataStream readUnsignedShort];
    segmentDepth = [dataStream readUnsignedShort];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 1;  // segmentNumber
   marshalSize = marshalSize + 1;  // segmentModification
   marshalSize = marshalSize + 2;  // generalSegmentAppearance
   marshalSize = marshalSize + 2;  // specificSegmentAppearance
   marshalSize = marshalSize + [segmentLocation getMarshalledSize];
   marshalSize = marshalSize + [segmentOrientation getMarshalledSize];
   marshalSize = marshalSize + 2;  // segmentLength
   marshalSize = marshalSize + 2;  // segmentWidth
   marshalSize = marshalSize + 2;  // segmentHeight
   marshalSize = marshalSize + 2;  // segmentDepth
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
