#import "LinearObjectStatePdu.h" 


@implementation LinearObjectStatePdu

@synthesize objectID;
@synthesize referencedObjectID;
@synthesize updateNumber;
@synthesize forceID;
@synthesize numberOfSegments;
@synthesize requesterID;
@synthesize receivingID;
@synthesize objectType;
@synthesize linearSegmentParameters;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:44];
    objectID = [[EntityID alloc] init];
    referencedObjectID = [[EntityID alloc] init];
    updateNumber = 0;
    forceID = 0;
    numberOfSegments = 0;
    requesterID = [[SimulationAddress alloc] init];
    receivingID = [[SimulationAddress alloc] init];
    objectType = [[ObjectType alloc] init];
    linearSegmentParameters = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [objectID release];
  [referencedObjectID release];
  [requesterID release];
  [receivingID release];
  [objectType release];
  [linearSegmentParameters release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [objectID marshalUsingStream:dataStream];
    [referencedObjectID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:updateNumber];
    [dataStream writeUnsignedByte:forceID];
    [dataStream writeUnsignedByte:[linearSegmentParameters count]];
    [requesterID marshalUsingStream:dataStream];
    [receivingID marshalUsingStream:dataStream];
    [objectType marshalUsingStream:dataStream];

     for(int idx = 0; idx < [linearSegmentParameters count]; idx++)
     {
        LinearSegmentParameter* x = [linearSegmentParameters objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [objectID unmarshalUsingStream:dataStream];
    [referencedObjectID unmarshalUsingStream:dataStream];
    updateNumber = [dataStream readUnsignedShort];
    forceID = [dataStream readUnsignedByte];
    numberOfSegments = [dataStream readUnsignedByte];
    [requesterID unmarshalUsingStream:dataStream];
    [receivingID unmarshalUsingStream:dataStream];
    [objectType unmarshalUsingStream:dataStream];

     [linearSegmentParameters removeAllObjects];
     for(int idx = 0; idx < numberOfSegments; idx++)
     {
        LinearSegmentParameter* x;
        [x unmarshalUsingStream:dataStream];
        [linearSegmentParameters addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [objectID getMarshalledSize];
   marshalSize = marshalSize + [referencedObjectID getMarshalledSize];
   marshalSize = marshalSize + 2;  // updateNumber
   marshalSize = marshalSize + 1;  // forceID
   marshalSize = marshalSize + 1;  // numberOfSegments
   marshalSize = marshalSize + [requesterID getMarshalledSize];
   marshalSize = marshalSize + [receivingID getMarshalledSize];
   marshalSize = marshalSize + [objectType getMarshalledSize];

   for(int idx=0; idx < [linearSegmentParameters count]; idx++)
   {
        LinearSegmentParameter* listElement = [linearSegmentParameters objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }

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
