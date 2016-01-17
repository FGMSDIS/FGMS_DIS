#import "DesignatorPdu.h" 


@implementation DesignatorPdu

@synthesize designatingEntityID;
@synthesize codeName;
@synthesize designatedEntityID;
@synthesize designatorCode;
@synthesize designatorPower;
@synthesize designatorWavelength;
@synthesize designatorSpotWrtDesignated;
@synthesize designatorSpotLocation;
@synthesize deadReckoningAlgorithm;
@synthesize padding1;
@synthesize padding2;
@synthesize entityLinearAcceleration;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:24];
    designatingEntityID = [[EntityID alloc] init];
    codeName = 0;
    designatedEntityID = [[EntityID alloc] init];
    designatorCode = 0;
    designatorPower = 0;
    designatorWavelength = 0;
    designatorSpotWrtDesignated = [[Vector3Float alloc] init];
    designatorSpotLocation = [[Vector3Double alloc] init];
    deadReckoningAlgorithm = 0;
    padding1 = 0;
    padding2 = 0;
    entityLinearAcceleration = [[Vector3Float alloc] init];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [designatingEntityID release];
  [designatedEntityID release];
  [designatorSpotWrtDesignated release];
  [designatorSpotLocation release];
  [entityLinearAcceleration release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [designatingEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:codeName];
    [designatedEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:designatorCode];
    [dataStream writeFloat:designatorPower];
    [dataStream writeFloat:designatorWavelength];
    [designatorSpotWrtDesignated marshalUsingStream:dataStream];
    [designatorSpotLocation marshalUsingStream:dataStream];
    [dataStream writeByte:deadReckoningAlgorithm];
    [dataStream writeUnsignedShort:padding1];
    [dataStream writeByte:padding2];
    [entityLinearAcceleration marshalUsingStream:dataStream];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [designatingEntityID unmarshalUsingStream:dataStream];
    codeName = [dataStream readUnsignedShort];
    [designatedEntityID unmarshalUsingStream:dataStream];
    designatorCode = [dataStream readUnsignedShort];
    designatorPower = [dataStream readFloat];
    designatorWavelength = [dataStream readFloat];
    [designatorSpotWrtDesignated unmarshalUsingStream:dataStream];
    [designatorSpotLocation unmarshalUsingStream:dataStream];
    deadReckoningAlgorithm = [dataStream readByte];
    padding1 = [dataStream readUnsignedShort];
    padding2 = [dataStream readByte];
    [entityLinearAcceleration unmarshalUsingStream:dataStream];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [designatingEntityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // codeName
   marshalSize = marshalSize + [designatedEntityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // designatorCode
   marshalSize = marshalSize + 4;  // designatorPower
   marshalSize = marshalSize + 4;  // designatorWavelength
   marshalSize = marshalSize + [designatorSpotWrtDesignated getMarshalledSize];
   marshalSize = marshalSize + [designatorSpotLocation getMarshalledSize];
   marshalSize = marshalSize + 1;  // deadReckoningAlgorithm
   marshalSize = marshalSize + 2;  // padding1
   marshalSize = marshalSize + 1;  // padding2
   marshalSize = marshalSize + [entityLinearAcceleration getMarshalledSize];
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
