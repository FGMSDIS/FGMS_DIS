#import "FalseTargetsAttribute.h" 


@implementation FalseTargetsAttribute

@synthesize recordType;
@synthesize recordLength;
@synthesize padding;
@synthesize emitterNumber;
@synthesize beamNumber;
@synthesize stateIndicator;
@synthesize padding2;
@synthesize falseTargetCount;
@synthesize walkSpeed;
@synthesize walkAcceleration;
@synthesize maximumWalkDistance;
@synthesize keepTime;
@synthesize echoSpacing;
@synthesize padding3;

-(id)init
{
  self = [super init];
  if(self)
  {
    recordType = 3502;
    recordLength = 40;
    padding = 0;
    padding2 = 0;
    padding3 = 0;
    emitterNumber = 0;
    beamNumber = 0;
    stateIndicator = 0;
    falseTargetCount = 0;
    walkSpeed = 0;
    walkAcceleration = 0;
    maximumWalkDistance = 0;
    keepTime = 0;
    echoSpacing = 0;
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
    [dataStream writeUnsignedByte:padding2];
    [dataStream writeFloat:falseTargetCount];
    [dataStream writeFloat:walkSpeed];
    [dataStream writeFloat:walkAcceleration];
    [dataStream writeFloat:maximumWalkDistance];
    [dataStream writeFloat:keepTime];
    [dataStream writeFloat:echoSpacing];
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
    padding2 = [dataStream readUnsignedByte];
    falseTargetCount = [dataStream readFloat];
    walkSpeed = [dataStream readFloat];
    walkAcceleration = [dataStream readFloat];
    maximumWalkDistance = [dataStream readFloat];
    keepTime = [dataStream readFloat];
    echoSpacing = [dataStream readFloat];
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
   marshalSize = marshalSize + 1;  // padding2
   marshalSize = marshalSize + 4;  // falseTargetCount
   marshalSize = marshalSize + 4;  // walkSpeed
   marshalSize = marshalSize + 4;  // walkAcceleration
   marshalSize = marshalSize + 4;  // maximumWalkDistance
   marshalSize = marshalSize + 4;  // keepTime
   marshalSize = marshalSize + 4;  // echoSpacing
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
