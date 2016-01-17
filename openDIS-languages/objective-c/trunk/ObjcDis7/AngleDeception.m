#import "AngleDeception.h" 


@implementation AngleDeception

@synthesize recordType;
@synthesize recordLength;
@synthesize padding;
@synthesize emitterNumber;
@synthesize beamNumber;
@synthesize stateIndicator;
@synthesize padding2;
@synthesize azimuthOffset;
@synthesize azimuthWidth;
@synthesize azimuthPullRate;
@synthesize azimuthPullAcceleration;
@synthesize elevationOffset;
@synthesize elevationWidth;
@synthesize elevationPullRate;
@synthesize elevationPullAcceleration;
@synthesize padding3;

-(id)init
{
  self = [super init];
  if(self)
  {
    recordType = 3501;
    recordLength = 48;
    padding = 0;
    padding2 = 0;
    padding3 = 0;
    emitterNumber = 0;
    beamNumber = 0;
    stateIndicator = 0;
    azimuthOffset = 0;
    azimuthWidth = 0;
    azimuthPullRate = 0;
    azimuthPullAcceleration = 0;
    elevationOffset = 0;
    elevationWidth = 0;
    elevationPullRate = 0;
    elevationPullAcceleration = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedInt:recordType];
    [dataStream writeUnsignedShort:recordLength];
    [dataStream writeUnsignedShort:padding];
    [dataStream writeUnsignedByte:emitterNumber];
    [dataStream writeUnsignedByte:beamNumber];
    [dataStream writeUnsignedByte:stateIndicator];
    [dataStream writeUnsignedInt:padding2];
    [dataStream writeFloat:azimuthOffset];
    [dataStream writeFloat:azimuthWidth];
    [dataStream writeFloat:azimuthPullRate];
    [dataStream writeFloat:azimuthPullAcceleration];
    [dataStream writeFloat:elevationOffset];
    [dataStream writeFloat:elevationWidth];
    [dataStream writeFloat:elevationPullRate];
    [dataStream writeFloat:elevationPullAcceleration];
    [dataStream writeUnsignedInt:padding3];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    recordType = [dataStream readUnsignedInt];
    recordLength = [dataStream readUnsignedShort];
    padding = [dataStream readUnsignedShort];
    emitterNumber = [dataStream readUnsignedByte];
    beamNumber = [dataStream readUnsignedByte];
    stateIndicator = [dataStream readUnsignedByte];
    padding2 = [dataStream readUnsignedInt];
    azimuthOffset = [dataStream readFloat];
    azimuthWidth = [dataStream readFloat];
    azimuthPullRate = [dataStream readFloat];
    azimuthPullAcceleration = [dataStream readFloat];
    elevationOffset = [dataStream readFloat];
    elevationWidth = [dataStream readFloat];
    elevationPullRate = [dataStream readFloat];
    elevationPullAcceleration = [dataStream readFloat];
    padding3 = [dataStream readUnsignedInt];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 4;  // recordType
   marshalSize = marshalSize + 2;  // recordLength
   marshalSize = marshalSize + 2;  // padding
   marshalSize = marshalSize + 1;  // emitterNumber
   marshalSize = marshalSize + 1;  // beamNumber
   marshalSize = marshalSize + 1;  // stateIndicator
   marshalSize = marshalSize + 4;  // padding2
   marshalSize = marshalSize + 4;  // azimuthOffset
   marshalSize = marshalSize + 4;  // azimuthWidth
   marshalSize = marshalSize + 4;  // azimuthPullRate
   marshalSize = marshalSize + 4;  // azimuthPullAcceleration
   marshalSize = marshalSize + 4;  // elevationOffset
   marshalSize = marshalSize + 4;  // elevationWidth
   marshalSize = marshalSize + 4;  // elevationPullRate
   marshalSize = marshalSize + 4;  // elevationPullAcceleration
   marshalSize = marshalSize + 4;  // padding3
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
