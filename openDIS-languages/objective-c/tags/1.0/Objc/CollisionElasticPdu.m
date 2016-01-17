#import "CollisionElasticPdu.h" 


@implementation CollisionElasticPdu

@synthesize issuingEntityID;
@synthesize collidingEntityID;
@synthesize collisionEventID;
@synthesize pad;
@synthesize contactVelocity;
@synthesize mass;
@synthesize location;
@synthesize collisionResultXX;
@synthesize collisionResultXY;
@synthesize collisionResultXZ;
@synthesize collisionResultYY;
@synthesize collisionResultYZ;
@synthesize collisionResultZZ;
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
    collisionEventID = [[EventID alloc] init];
    contactVelocity = [[Vector3Float alloc] init];
    mass = 0;
    location = [[Vector3Float alloc] init];
    collisionResultXX = 0;
    collisionResultXY = 0;
    collisionResultXZ = 0;
    collisionResultYY = 0;
    collisionResultYZ = 0;
    collisionResultZZ = 0;
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
  [location release];
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
    [location marshalUsingStream:dataStream];
    [dataStream writeFloat:collisionResultXX];
    [dataStream writeFloat:collisionResultXY];
    [dataStream writeFloat:collisionResultXZ];
    [dataStream writeFloat:collisionResultYY];
    [dataStream writeFloat:collisionResultYZ];
    [dataStream writeFloat:collisionResultZZ];
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
    [location unmarshalUsingStream:dataStream];
    collisionResultXX = [dataStream readFloat];
    collisionResultXY = [dataStream readFloat];
    collisionResultXZ = [dataStream readFloat];
    collisionResultYY = [dataStream readFloat];
    collisionResultYZ = [dataStream readFloat];
    collisionResultZZ = [dataStream readFloat];
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
   marshalSize = marshalSize + [location getMarshalledSize];
   marshalSize = marshalSize + 4;  // collisionResultXX
   marshalSize = marshalSize + 4;  // collisionResultXY
   marshalSize = marshalSize + 4;  // collisionResultXZ
   marshalSize = marshalSize + 4;  // collisionResultYY
   marshalSize = marshalSize + 4;  // collisionResultYZ
   marshalSize = marshalSize + 4;  // collisionResultZZ
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
