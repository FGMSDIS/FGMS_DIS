#import "ElectronicEmissionsPdu.h" 


@implementation ElectronicEmissionsPdu

@synthesize emittingEntityID;
@synthesize eventID;
@synthesize stateUpdateIndicator;
@synthesize numberOfSystems;
@synthesize paddingForEmissionsPdu;
@synthesize systemDataLength;
@synthesize numberOfBeams;
@synthesize emitterSystem;
@synthesize location;
@synthesize systems;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:23];
    [self setPaddingForEmissionsPdu:0];
    emittingEntityID = [[EntityID alloc] init];
    eventID = [[EventIdentifier alloc] init];
    stateUpdateIndicator = 0;
    numberOfSystems = 0;
    systemDataLength = 0;
    numberOfBeams = 0;
    emitterSystem = [[EmitterSystem alloc] init];
    location = [[Vector3Float alloc] init];
    systems = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [emittingEntityID release];
  [eventID release];
  [emitterSystem release];
  [location release];
  [systems release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [emittingEntityID marshalUsingStream:dataStream];
    [eventID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:stateUpdateIndicator];
    [dataStream writeUnsignedByte:[systems count]];
    [dataStream writeUnsignedShort:paddingForEmissionsPdu];
    [dataStream writeUnsignedByte:systemDataLength];
    [dataStream writeUnsignedByte:numberOfBeams];
    [emitterSystem marshalUsingStream:dataStream];
    [location marshalUsingStream:dataStream];

     for(int idx = 0; idx < [systems count]; idx++)
     {
        Vector3Float* x = [systems objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [emittingEntityID unmarshalUsingStream:dataStream];
    [eventID unmarshalUsingStream:dataStream];
    stateUpdateIndicator = [dataStream readUnsignedByte];
    numberOfSystems = [dataStream readUnsignedByte];
    paddingForEmissionsPdu = [dataStream readUnsignedShort];
    systemDataLength = [dataStream readUnsignedByte];
    numberOfBeams = [dataStream readUnsignedByte];
    [emitterSystem unmarshalUsingStream:dataStream];
    [location unmarshalUsingStream:dataStream];

     [systems removeAllObjects];
     for(int idx = 0; idx < numberOfSystems; idx++)
     {
        Vector3Float* x;
        [x unmarshalUsingStream:dataStream];
        [systems addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [emittingEntityID getMarshalledSize];
   marshalSize = marshalSize + [eventID getMarshalledSize];
   marshalSize = marshalSize + 1;  // stateUpdateIndicator
   marshalSize = marshalSize + 1;  // numberOfSystems
   marshalSize = marshalSize + 2;  // paddingForEmissionsPdu
   marshalSize = marshalSize + 1;  // systemDataLength
   marshalSize = marshalSize + 1;  // numberOfBeams
   marshalSize = marshalSize + [emitterSystem getMarshalledSize];
   marshalSize = marshalSize + [location getMarshalledSize];

   for(int idx=0; idx < [systems count]; idx++)
   {
        Vector3Float* listElement = [systems objectAtIndex:idx];
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
