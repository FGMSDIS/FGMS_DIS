#import "DirectedEnergyPrecisionAimpoint.h" 


@implementation DirectedEnergyPrecisionAimpoint

@synthesize recordType;
@synthesize recordLength;
@synthesize padding;
@synthesize targetSpotLocation;
@synthesize targetSpotEntityLocation;
@synthesize targetSpotVelocity;
@synthesize targetSpotAcceleration;
@synthesize targetEntityID;
@synthesize targetComponentID;
@synthesize SpotShape;
@synthesize BeamSpotXSecSemiMajorAxis;
@synthesize BeamSpotCrossSectionSemiMinorAxis;
@synthesize BeamSpotCrossSectionOrientAngle;

-(id)init
{
  self = [super init];
  if(self)
  {
    recordType = 4000;
    recordLength = 88;
    padding = 0;
    targetComponentID = 0;
    SpotShape = 0;
    BeamSpotXSecSemiMajorAxis = 0;
    BeamSpotCrossSectionSemiMinorAxis = 0;
    BeamSpotCrossSectionOrientAngle = 0;
    targetSpotLocation = [[Vector3Double alloc] init];
    targetSpotEntityLocation = [[Vector3Float alloc] init];
    targetSpotVelocity = [[Vector3Float alloc] init];
    targetSpotAcceleration = [[Vector3Float alloc] init];
    targetEntityID = [[EntityID alloc] init];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [targetSpotLocation release];
  [targetSpotEntityLocation release];
  [targetSpotVelocity release];
  [targetSpotAcceleration release];
  [targetEntityID release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedInt:recordType];
    [dataStream writeUnsignedShort:recordLength];
    [dataStream writeUnsignedShort:padding];
    [targetSpotLocation marshalUsingStream:dataStream];
    [targetSpotEntityLocation marshalUsingStream:dataStream];
    [targetSpotVelocity marshalUsingStream:dataStream];
    [targetSpotAcceleration marshalUsingStream:dataStream];
    [targetEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:targetComponentID];
    [dataStream writeUnsignedByte:SpotShape];
    [dataStream writeFloat:BeamSpotXSecSemiMajorAxis];
    [dataStream writeFloat:BeamSpotCrossSectionSemiMinorAxis];
    [dataStream writeFloat:BeamSpotCrossSectionOrientAngle];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    recordType = [dataStream readUnsignedInt];
    recordLength = [dataStream readUnsignedShort];
    padding = [dataStream readUnsignedShort];
    [targetSpotLocation unmarshalUsingStream:dataStream];
    [targetSpotEntityLocation unmarshalUsingStream:dataStream];
    [targetSpotVelocity unmarshalUsingStream:dataStream];
    [targetSpotAcceleration unmarshalUsingStream:dataStream];
    [targetEntityID unmarshalUsingStream:dataStream];
    targetComponentID = [dataStream readUnsignedByte];
    SpotShape = [dataStream readUnsignedByte];
    BeamSpotXSecSemiMajorAxis = [dataStream readFloat];
    BeamSpotCrossSectionSemiMinorAxis = [dataStream readFloat];
    BeamSpotCrossSectionOrientAngle = [dataStream readFloat];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 4;  // recordType
   marshalSize = marshalSize + 2;  // recordLength
   marshalSize = marshalSize + 2;  // padding
   marshalSize = marshalSize + [targetSpotLocation getMarshalledSize];
   marshalSize = marshalSize + [targetSpotEntityLocation getMarshalledSize];
   marshalSize = marshalSize + [targetSpotVelocity getMarshalledSize];
   marshalSize = marshalSize + [targetSpotAcceleration getMarshalledSize];
   marshalSize = marshalSize + [targetEntityID getMarshalledSize];
   marshalSize = marshalSize + 1;  // targetComponentID
   marshalSize = marshalSize + 1;  // SpotShape
   marshalSize = marshalSize + 4;  // BeamSpotXSecSemiMajorAxis
   marshalSize = marshalSize + 4;  // BeamSpotCrossSectionSemiMinorAxis
   marshalSize = marshalSize + 4;  // BeamSpotCrossSectionOrientAngle
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
