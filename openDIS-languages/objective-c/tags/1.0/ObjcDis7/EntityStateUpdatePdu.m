#import "EntityStateUpdatePdu.h" 


@implementation EntityStateUpdatePdu

@synthesize entityID;
@synthesize padding1;
@synthesize numberOfVariableParameters;
@synthesize entityLinearVelocity;
@synthesize entityLocation;
@synthesize entityOrientation;
@synthesize entityAppearance;
@synthesize variableParameters;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:67];
    [self setProtocolFamily:1];
    entityID = [[EntityID alloc] init];
    padding1 = 0;
    numberOfVariableParameters = 0;
    entityLinearVelocity = [[Vector3Float alloc] init];
    entityLocation = [[Vector3Double alloc] init];
    entityOrientation = [[EulerAngles alloc] init];
    entityAppearance = 0;
    variableParameters = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [entityID release];
  [entityLinearVelocity release];
  [entityLocation release];
  [entityOrientation release];
  [variableParameters release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [entityID marshalUsingStream:dataStream];
    [dataStream writeByte:padding1];
    [dataStream writeUnsignedByte:[variableParameters count]];
    [entityLinearVelocity marshalUsingStream:dataStream];
    [entityLocation marshalUsingStream:dataStream];
    [entityOrientation marshalUsingStream:dataStream];
    [dataStream writeUnsignedInt:entityAppearance];

     for(int idx = 0; idx < [variableParameters count]; idx++)
     {
        VariableParameter* x = [variableParameters objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [entityID unmarshalUsingStream:dataStream];
    padding1 = [dataStream readByte];
    numberOfVariableParameters = [dataStream readUnsignedByte];
    [entityLinearVelocity unmarshalUsingStream:dataStream];
    [entityLocation unmarshalUsingStream:dataStream];
    [entityOrientation unmarshalUsingStream:dataStream];
    entityAppearance = [dataStream readUnsignedInt];

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
   marshalSize = marshalSize + [entityID getMarshalledSize];
   marshalSize = marshalSize + 1;  // padding1
   marshalSize = marshalSize + 1;  // numberOfVariableParameters
   marshalSize = marshalSize + [entityLinearVelocity getMarshalledSize];
   marshalSize = marshalSize + [entityLocation getMarshalledSize];
   marshalSize = marshalSize + [entityOrientation getMarshalledSize];
   marshalSize = marshalSize + 4;  // entityAppearance

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
