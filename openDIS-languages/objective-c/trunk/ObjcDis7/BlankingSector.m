#import "BlankingSector.h" 


@implementation BlankingSector

@synthesize recordType;
@synthesize recordLength;
@synthesize emitterNumber;
@synthesize beamNumber;
@synthesize stateIndicator;
@synthesize leftAzimuth;
@synthesize rightAzimuth;
@synthesize lowerElevation;
@synthesize upperElevation;
@synthesize residualPower;

-(id)init
{
  self = [super init];
  if(self)
  {
    recordType = 3500;
    recordLength = 0;
    emitterNumber = 0;
    beamNumber = 0;
    stateIndicator = 0;
    leftAzimuth = 0;
    rightAzimuth = 0;
    lowerElevation = 0;
    upperElevation = 0;
    residualPower = 0;
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
    [dataStream writeUnsignedByte:emitterNumber];
    [dataStream writeUnsignedByte:beamNumber];
    [dataStream writeUnsignedByte:stateIndicator];
    [dataStream writeFloat:leftAzimuth];
    [dataStream writeFloat:rightAzimuth];
    [dataStream writeFloat:lowerElevation];
    [dataStream writeFloat:upperElevation];
    [dataStream writeFloat:residualPower];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    recordType = [dataStream readUnsignedInt];
    recordLength = [dataStream readUnsignedShort];
    emitterNumber = [dataStream readUnsignedByte];
    beamNumber = [dataStream readUnsignedByte];
    stateIndicator = [dataStream readUnsignedByte];
    leftAzimuth = [dataStream readFloat];
    rightAzimuth = [dataStream readFloat];
    lowerElevation = [dataStream readFloat];
    upperElevation = [dataStream readFloat];
    residualPower = [dataStream readFloat];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 4;  // recordType
   marshalSize = marshalSize + 2;  // recordLength
   marshalSize = marshalSize + 1;  // emitterNumber
   marshalSize = marshalSize + 1;  // beamNumber
   marshalSize = marshalSize + 1;  // stateIndicator
   marshalSize = marshalSize + 4;  // leftAzimuth
   marshalSize = marshalSize + 4;  // rightAzimuth
   marshalSize = marshalSize + 4;  // lowerElevation
   marshalSize = marshalSize + 4;  // upperElevation
   marshalSize = marshalSize + 4;  // residualPower
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
