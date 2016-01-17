#import "EntityDamageStatusPdu.h" 


@implementation EntityDamageStatusPdu

@synthesize damagedEntityID;
@synthesize padding1;
@synthesize padding2;
@synthesize numberOfDamageDescription;
@synthesize damageDescriptionRecords;

-(id)init
{
  self = [super init];
  if(self)
  {
    padding1 = 0;
    padding2 = 0;
    numberOfDamageDescription = 0;
    [self setPduType:69];
    damagedEntityID = [[EntityID alloc] init];
    damageDescriptionRecords = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [damagedEntityID release];
  [damageDescriptionRecords release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [damagedEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:padding1];
    [dataStream writeUnsignedShort:padding2];
    [dataStream writeUnsignedShort:[damageDescriptionRecords count]];

     for(int idx = 0; idx < [damageDescriptionRecords count]; idx++)
     {
        DirectedEnergyDamage* x = [damageDescriptionRecords objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [damagedEntityID unmarshalUsingStream:dataStream];
    padding1 = [dataStream readUnsignedShort];
    padding2 = [dataStream readUnsignedShort];
    numberOfDamageDescription = [dataStream readUnsignedShort];

     [damageDescriptionRecords removeAllObjects];
     for(int idx = 0; idx < numberOfDamageDescription; idx++)
     {
        DirectedEnergyDamage* x;
        [x unmarshalUsingStream:dataStream];
        [damageDescriptionRecords addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [damagedEntityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // padding1
   marshalSize = marshalSize + 2;  // padding2
   marshalSize = marshalSize + 2;  // numberOfDamageDescription

   for(int idx=0; idx < [damageDescriptionRecords count]; idx++)
   {
        DirectedEnergyDamage* listElement = [damageDescriptionRecords objectAtIndex:idx];
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
