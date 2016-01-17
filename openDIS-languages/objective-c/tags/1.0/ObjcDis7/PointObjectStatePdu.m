#import "PointObjectStatePdu.h" 


@implementation PointObjectStatePdu

@synthesize objectID;
@synthesize referencedObjectID;
@synthesize updateNumber;
@synthesize forceID;
@synthesize modifications;
@synthesize objectType;
@synthesize objectLocation;
@synthesize objectOrientation;
@synthesize objectAppearance;
@synthesize requesterID;
@synthesize receivingID;
@synthesize pad2;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:43];
    objectID = [[EntityID alloc] init];
    referencedObjectID = [[EntityID alloc] init];
    updateNumber = 0;
    forceID = 0;
    modifications = 0;
    objectType = [[ObjectType alloc] init];
    objectLocation = [[Vector3Double alloc] init];
    objectOrientation = [[EulerAngles alloc] init];
    objectAppearance = 0;
    requesterID = [[SimulationAddress alloc] init];
    receivingID = [[SimulationAddress alloc] init];
    pad2 = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [objectID release];
  [referencedObjectID release];
  [objectType release];
  [objectLocation release];
  [objectOrientation release];
  [requesterID release];
  [receivingID release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [objectID marshalUsingStream:dataStream];
    [referencedObjectID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:updateNumber];
    [dataStream writeUnsignedByte:forceID];
    [dataStream writeUnsignedByte:modifications];
    [objectType marshalUsingStream:dataStream];
    [objectLocation marshalUsingStream:dataStream];
    [objectOrientation marshalUsingStream:dataStream];
    [dataStream writeDouble:objectAppearance];
    [requesterID marshalUsingStream:dataStream];
    [receivingID marshalUsingStream:dataStream];
    [dataStream writeUnsignedInt:pad2];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [objectID unmarshalUsingStream:dataStream];
    [referencedObjectID unmarshalUsingStream:dataStream];
    updateNumber = [dataStream readUnsignedShort];
    forceID = [dataStream readUnsignedByte];
    modifications = [dataStream readUnsignedByte];
    [objectType unmarshalUsingStream:dataStream];
    [objectLocation unmarshalUsingStream:dataStream];
    [objectOrientation unmarshalUsingStream:dataStream];
    objectAppearance = [dataStream readDouble];
    [requesterID unmarshalUsingStream:dataStream];
    [receivingID unmarshalUsingStream:dataStream];
    pad2 = [dataStream readUnsignedInt];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [objectID getMarshalledSize];
   marshalSize = marshalSize + [referencedObjectID getMarshalledSize];
   marshalSize = marshalSize + 2;  // updateNumber
   marshalSize = marshalSize + 1;  // forceID
   marshalSize = marshalSize + 1;  // modifications
   marshalSize = marshalSize + [objectType getMarshalledSize];
   marshalSize = marshalSize + [objectLocation getMarshalledSize];
   marshalSize = marshalSize + [objectOrientation getMarshalledSize];
   marshalSize = marshalSize + 8;  // objectAppearance
   marshalSize = marshalSize + [requesterID getMarshalledSize];
   marshalSize = marshalSize + [receivingID getMarshalledSize];
   marshalSize = marshalSize + 4;  // pad2
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
