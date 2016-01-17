#import "CollisionPdu.h" 


@implementation CollisionPdu

@synthesize issuingEntityID;
@synthesize collidingEntityID;
@synthesize eventID;
@synthesize collisionType;
@synthesize pad;
@synthesize velocity;
@synthesize mass;
@synthesize location;

-(id)init
{
  self = [super init];
  if(self)
  {
    pad = 0;
    [self setPduType:4];
    [self setProtocolFamily:1];
    issuingEntityID = [[EntityID alloc] init];
    collidingEntityID = [[EntityID alloc] init];
    eventID = [[EventID alloc] init];
    collisionType = 0;
    velocity = [[Vector3Float alloc] init];
    mass = 0;
    location = [[Vector3Float alloc] init];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [issuingEntityID release];
  [collidingEntityID release];
  [eventID release];
  [velocity release];
  [location release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [issuingEntityID marshalUsingStream:dataStream];
    [collidingEntityID marshalUsingStream:dataStream];
    [eventID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:collisionType];
    [dataStream writeByte:pad];
    [velocity marshalUsingStream:dataStream];
    [dataStream writeFloat:mass];
    [location marshalUsingStream:dataStream];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [issuingEntityID unmarshalUsingStream:dataStream];
    [collidingEntityID unmarshalUsingStream:dataStream];
    [eventID unmarshalUsingStream:dataStream];
    collisionType = [dataStream readUnsignedByte];
    pad = [dataStream readByte];
    [velocity unmarshalUsingStream:dataStream];
    mass = [dataStream readFloat];
    [location unmarshalUsingStream:dataStream];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [issuingEntityID getMarshalledSize];
   marshalSize = marshalSize + [collidingEntityID getMarshalledSize];
   marshalSize = marshalSize + [eventID getMarshalledSize];
   marshalSize = marshalSize + 1;  // collisionType
   marshalSize = marshalSize + 1;  // pad
   marshalSize = marshalSize + [velocity getMarshalledSize];
   marshalSize = marshalSize + 4;  // mass
   marshalSize = marshalSize + [location getMarshalledSize];
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
