#import "IsGroupOfPdu.h" 


@implementation IsGroupOfPdu

@synthesize groupEntityID;
@synthesize groupedEntityCategory;
@synthesize numberOfGroupedEntities;
@synthesize pad2;
@synthesize latitude;
@synthesize longitude;
@synthesize groupedEntityDescriptions;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:34];
    groupEntityID = [[EntityID alloc] init];
    groupedEntityCategory = 0;
    numberOfGroupedEntities = 0;
    pad2 = 0;
    latitude = 0;
    longitude = 0;
    groupedEntityDescriptions = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [groupEntityID release];
  [groupedEntityDescriptions release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [groupEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:groupedEntityCategory];
    [dataStream writeUnsignedByte:[groupedEntityDescriptions count]];
    [dataStream writeUnsignedInt:pad2];
    [dataStream writeDouble:latitude];
    [dataStream writeDouble:longitude];

     for(int idx = 0; idx < [groupedEntityDescriptions count]; idx++)
     {
        VariableDatum* x = [groupedEntityDescriptions objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [groupEntityID unmarshalUsingStream:dataStream];
    groupedEntityCategory = [dataStream readUnsignedByte];
    numberOfGroupedEntities = [dataStream readUnsignedByte];
    pad2 = [dataStream readUnsignedInt];
    latitude = [dataStream readDouble];
    longitude = [dataStream readDouble];

     [groupedEntityDescriptions removeAllObjects];
     for(int idx = 0; idx < numberOfGroupedEntities; idx++)
     {
        VariableDatum* x;
        [x unmarshalUsingStream:dataStream];
        [groupedEntityDescriptions addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [groupEntityID getMarshalledSize];
   marshalSize = marshalSize + 1;  // groupedEntityCategory
   marshalSize = marshalSize + 1;  // numberOfGroupedEntities
   marshalSize = marshalSize + 4;  // pad2
   marshalSize = marshalSize + 8;  // latitude
   marshalSize = marshalSize + 8;  // longitude

   for(int idx=0; idx < [groupedEntityDescriptions count]; idx++)
   {
        VariableDatum* listElement = [groupedEntityDescriptions objectAtIndex:idx];
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
