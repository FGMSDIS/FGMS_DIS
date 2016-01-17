#import "CollisionElasticPdu.h" 


@implementation CollisionElasticPdu

@synthesize issuingEntityID;
@synthesize collidingEntityID;
@synthesize collisionEventID;
@synthesize pad;
@synthesize contactVelocity;
@synthesize mass;
@synthesize locationOfImpact;
@synthesize collisionIntermediateResultXX;
@synthesize collisionIntermediateResultXY;
@synthesize collisionIntermediateResultXZ;
@synthesize collisionIntermediateResultYY;
@synthesize collisionIntermediateResultYZ;
@synthesize collisionIntermediateResultZZ;
@synthesize unitSurfaceNormal;
@synthesize coefficientOfRestitution;

-(id)init
{
  self = [super init];
  if(self)
  {
    pad = 0;
    [self setPduType:66];
    [self setProtocolFamily:1];
    issuingEntityID = [[EntityID alloc] init];
    collidingEntityID = [[EntityID alloc] init];
    collisionEventID = [[EventIdentifier alloc] init];
    contactVelocity = [[Vector3Float alloc] init];
    mass = 0;
    locationOfImpact = [[Vector3Float alloc] init];
    collisionIntermediateResultXX = 0;
    collisionIntermediateResultXY = 0;
    collisionIntermediateResultXZ = 0;
    collisionIntermediateResultYY = 0;
    collisionIntermediateResultYZ = 0;
    collisionIntermediateResultZZ = 0;
    unitSurfaceNormal = [[Vector3Float alloc] init];
    coefficientOfRestitution = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [issuingEntityID release];
  [collidingEntityID release];
  [collisionEventID release];
  [contactVelocity release];
  [locationOfImpact release];
  [unitSurfaceNormal release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [issuingEntityID marshalUsingStream:dataStream];
    [collidingEntityID marshalUsingStream:dataStream];
    [collisionEventID marshalUsingStream:dataStream];
    [dataStream writeShort:pad];
    [contactVelocity marshalUsingStream:dataStream];
    [dataStream writeFloat:mass];
    [locationOfImpact marshalUsingStream:dataStream];
    [dataStream writeFloat:collisionIntermediateResultXX];
    [dataStream writeFloat:collisionIntermediateResultXY];
    [dataStream writeFloat:collisionIntermediateResultXZ];
    [dataStream writeFloat:collisionIntermediateResultYY];
    [dataStream writeFloat:collisionIntermediateResultYZ];
    [dataStream writeFloat:collisionIntermediateResultZZ];
    [unitSurfaceNormal marshalUsingStream:dataStream];
    [dataStream writeFloat:coefficientOfRestitution];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [issuingEntityID unmarshalUsingStream:dataStream];
    [collidingEntityID unmarshalUsingStream:dataStream];
    [collisionEventID unmarshalUsingStream:dataStream];
    pad = [dataStream readShort];
    [contactVelocity unmarshalUsingStream:dataStream];
    mass = [dataStream readFloat];
    [locationOfImpact unmarshalUsingStream:dataStream];
    collisionIntermediateResultXX = [dataStream readFloat];
    collisionIntermediateResultXY = [dataStream readFloat];
    collisionIntermediateResultXZ = [dataStream readFloat];
    collisionIntermediateResultYY = [dataStream readFloat];
    collisionIntermediateResultYZ = [dataStream readFloat];
    collisionIntermediateResultZZ = [dataStream readFloat];
    [unitSurfaceNormal unmarshalUsingStream:dataStream];
    coefficientOfRestitution = [dataStream readFloat];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [issuingEntityID getMarshalledSize];
   marshalSize = marshalSize + [collidingEntityID getMarshalledSize];
   marshalSize = marshalSize + [collisionEventID getMarshalledSize];
   marshalSize = marshalSize + 2;  // pad
   marshalSize = marshalSize + [contactVelocity getMarshalledSize];
   marshalSize = marshalSize + 4;  // mass
   marshalSize = marshalSize + [locationOfImpact getMarshalledSize];
   marshalSize = marshalSize + 4;  // collisionIntermediateResultXX
   marshalSize = marshalSize + 4;  // collisionIntermediateResultXY
   marshalSize = marshalSize + 4;  // collisionIntermediateResultXZ
   marshalSize = marshalSize + 4;  // collisionIntermediateResultYY
   marshalSize = marshalSize + 4;  // collisionIntermediateResultYZ
   marshalSize = marshalSize + 4;  // collisionIntermediateResultZZ
   marshalSize = marshalSize + [unitSurfaceNormal getMarshalledSize];
   marshalSize = marshalSize + 4;  // coefficientOfRestitution
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
