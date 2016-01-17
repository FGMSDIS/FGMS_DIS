#import "DetonationPdu.h" 


@implementation DetonationPdu

@synthesize explodingEntityID;
@synthesize eventID;
@synthesize velocity;
@synthesize locationInWorldCoordinates;
@synthesize descriptor;
@synthesize locationOfEntityCoordinates;
@synthesize detonationResult;
@synthesize numberOfVariableParameters;
@synthesize pad;
@synthesize variableParameters;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:3];
    explodingEntityID = [[EntityID alloc] init];
    eventID = [[EventIdentifier alloc] init];
    velocity = [[Vector3Float alloc] init];
    locationInWorldCoordinates = [[Vector3Double alloc] init];
    descriptor = [[MunitionDescriptor alloc] init];
    locationOfEntityCoordinates = [[Vector3Float alloc] init];
    detonationResult = 0;
    numberOfVariableParameters = 0;
    pad = 0;
    variableParameters = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [explodingEntityID release];
  [eventID release];
  [velocity release];
  [locationInWorldCoordinates release];
  [descriptor release];
  [locationOfEntityCoordinates release];
  [variableParameters release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [explodingEntityID marshalUsingStream:dataStream];
    [eventID marshalUsingStream:dataStream];
    [velocity marshalUsingStream:dataStream];
    [locationInWorldCoordinates marshalUsingStream:dataStream];
    [descriptor marshalUsingStream:dataStream];
    [locationOfEntityCoordinates marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:detonationResult];
    [dataStream writeUnsignedByte:[variableParameters count]];
    [dataStream writeUnsignedShort:pad];

     for(int idx = 0; idx < [variableParameters count]; idx++)
     {
        VariableParameter* x = [variableParameters objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [explodingEntityID unmarshalUsingStream:dataStream];
    [eventID unmarshalUsingStream:dataStream];
    [velocity unmarshalUsingStream:dataStream];
    [locationInWorldCoordinates unmarshalUsingStream:dataStream];
    [descriptor unmarshalUsingStream:dataStream];
    [locationOfEntityCoordinates unmarshalUsingStream:dataStream];
    detonationResult = [dataStream readUnsignedByte];
    numberOfVariableParameters = [dataStream readUnsignedByte];
    pad = [dataStream readUnsignedShort];

     [variableParameters removeAllObjects];
     for(int idx = 0; idx < numberOfVariableParameters; idx++)
     {
        VariableParameter* x;
        [x unmarshalUsingStream:dataStream];
        [variableParameters addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [explodingEntityID getMarshalledSize];
   marshalSize = marshalSize + [eventID getMarshalledSize];
   marshalSize = marshalSize + [velocity getMarshalledSize];
   marshalSize = marshalSize + [locationInWorldCoordinates getMarshalledSize];
   marshalSize = marshalSize + [descriptor getMarshalledSize];
   marshalSize = marshalSize + [locationOfEntityCoordinates getMarshalledSize];
   marshalSize = marshalSize + 1;  // detonationResult
   marshalSize = marshalSize + 1;  // numberOfVariableParameters
   marshalSize = marshalSize + 2;  // pad

   for(int idx=0; idx < [variableParameters count]; idx++)
   {
        VariableParameter* listElement = [variableParameters objectAtIndex:idx];
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
