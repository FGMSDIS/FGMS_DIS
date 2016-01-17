#import "UaPdu.h" 


@implementation UaPdu

@synthesize emittingEntityID;
@synthesize eventID;
@synthesize stateChangeIndicator;
@synthesize pad;
@synthesize passiveParameterIndex;
@synthesize propulsionPlantConfiguration;
@synthesize numberOfShafts;
@synthesize numberOfAPAs;
@synthesize numberOfUAEmitterSystems;
@synthesize shaftRPMs;
@synthesize apaData;
@synthesize emitterSystems;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:29];
    emittingEntityID = [[EntityID alloc] init];
    eventID = [[EventID alloc] init];
    stateChangeIndicator = 0;
    pad = 0;
    passiveParameterIndex = 0;
    propulsionPlantConfiguration = 0;
    numberOfShafts = 0;
    numberOfAPAs = 0;
    numberOfUAEmitterSystems = 0;
    shaftRPMs = [NSMutableArray arrayWithCapacity:1];
    apaData = [NSMutableArray arrayWithCapacity:1];
    emitterSystems = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [emittingEntityID release];
  [eventID release];
  [shaftRPMs release];
  [apaData release];
  [emitterSystems release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [emittingEntityID marshalUsingStream:dataStream];
    [eventID marshalUsingStream:dataStream];
    [dataStream writeByte:stateChangeIndicator];
    [dataStream writeByte:pad];
    [dataStream writeUnsignedShort:passiveParameterIndex];
    [dataStream writeUnsignedByte:propulsionPlantConfiguration];
    [dataStream writeUnsignedByte:[shaftRPMs count]];
    [dataStream writeUnsignedByte:[apaData count]];
    [dataStream writeUnsignedByte:[emitterSystems count]];

     for(int idx = 0; idx < [shaftRPMs count]; idx++)
     {
        ShaftRPMs* x = [shaftRPMs objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [apaData count]; idx++)
     {
        ApaData* x = [apaData objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [emitterSystems count]; idx++)
     {
        AcousticEmitterSystemData* x = [emitterSystems objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [emittingEntityID unmarshalUsingStream:dataStream];
    [eventID unmarshalUsingStream:dataStream];
    stateChangeIndicator = [dataStream readByte];
    pad = [dataStream readByte];
    passiveParameterIndex = [dataStream readUnsignedShort];
    propulsionPlantConfiguration = [dataStream readUnsignedByte];
    numberOfShafts = [dataStream readUnsignedByte];
    numberOfAPAs = [dataStream readUnsignedByte];
    numberOfUAEmitterSystems = [dataStream readUnsignedByte];

     [shaftRPMs removeAllObjects];
     for(int idx = 0; idx < numberOfShafts; idx++)
     {
        ShaftRPMs* x;
        [x unmarshalUsingStream:dataStream];
        [shaftRPMs addObject:x];
     }

     [apaData removeAllObjects];
     for(int idx = 0; idx < numberOfAPAs; idx++)
     {
        ApaData* x;
        [x unmarshalUsingStream:dataStream];
        [apaData addObject:x];
     }

     [emitterSystems removeAllObjects];
     for(int idx = 0; idx < numberOfUAEmitterSystems; idx++)
     {
        AcousticEmitterSystemData* x;
        [x unmarshalUsingStream:dataStream];
        [emitterSystems addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [emittingEntityID getMarshalledSize];
   marshalSize = marshalSize + [eventID getMarshalledSize];
   marshalSize = marshalSize + 1;  // stateChangeIndicator
   marshalSize = marshalSize + 1;  // pad
   marshalSize = marshalSize + 2;  // passiveParameterIndex
   marshalSize = marshalSize + 1;  // propulsionPlantConfiguration
   marshalSize = marshalSize + 1;  // numberOfShafts
   marshalSize = marshalSize + 1;  // numberOfAPAs
   marshalSize = marshalSize + 1;  // numberOfUAEmitterSystems

   for(int idx=0; idx < [shaftRPMs count]; idx++)
   {
        ShaftRPMs* listElement = [shaftRPMs objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [apaData count]; idx++)
   {
        ApaData* listElement = [apaData objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [emitterSystems count]; idx++)
   {
        AcousticEmitterSystemData* listElement = [emitterSystems objectAtIndex:idx];
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
