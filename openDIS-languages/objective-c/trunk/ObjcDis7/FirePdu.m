#import "FirePdu.h" 


@implementation FirePdu

@synthesize munitionExpendibleID;
@synthesize eventID;
@synthesize fireMissionIndex;
@synthesize locationInWorldCoordinates;
@synthesize descriptor;
@synthesize velocity;
@synthesize range;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:2];
    munitionExpendibleID = [[EntityID alloc] init];
    eventID = [[EventIdentifier alloc] init];
    fireMissionIndex = 0;
    locationInWorldCoordinates = [[Vector3Double alloc] init];
    descriptor = [[MunitionDescriptor alloc] init];
    velocity = [[Vector3Float alloc] init];
    range = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [munitionExpendibleID release];
  [eventID release];
  [locationInWorldCoordinates release];
  [descriptor release];
  [velocity release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [munitionExpendibleID marshalUsingStream:dataStream];
    [eventID marshalUsingStream:dataStream];
    [dataStream writeUnsignedInt:fireMissionIndex];
    [locationInWorldCoordinates marshalUsingStream:dataStream];
    [descriptor marshalUsingStream:dataStream];
    [velocity marshalUsingStream:dataStream];
    [dataStream writeFloat:range];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [munitionExpendibleID unmarshalUsingStream:dataStream];
    [eventID unmarshalUsingStream:dataStream];
    fireMissionIndex = [dataStream readUnsignedInt];
    [locationInWorldCoordinates unmarshalUsingStream:dataStream];
    [descriptor unmarshalUsingStream:dataStream];
    [velocity unmarshalUsingStream:dataStream];
    range = [dataStream readFloat];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [munitionExpendibleID getMarshalledSize];
   marshalSize = marshalSize + [eventID getMarshalledSize];
   marshalSize = marshalSize + 4;  // fireMissionIndex
   marshalSize = marshalSize + [locationInWorldCoordinates getMarshalledSize];
   marshalSize = marshalSize + [descriptor getMarshalledSize];
   marshalSize = marshalSize + [velocity getMarshalledSize];
   marshalSize = marshalSize + 4;  // range
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
