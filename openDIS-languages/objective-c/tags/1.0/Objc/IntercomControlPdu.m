#import "IntercomControlPdu.h" 


@implementation IntercomControlPdu

@synthesize controlType;
@synthesize communicationsChannelType;
@synthesize sourceEntityID;
@synthesize sourceCommunicationsDeviceID;
@synthesize sourceLineID;
@synthesize transmitPriority;
@synthesize transmitLineState;
@synthesize command;
@synthesize masterEntityID;
@synthesize masterCommunicationsDeviceID;
@synthesize intercomParametersLength;
@synthesize intercomParameters;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:32];
    controlType = 0;
    communicationsChannelType = 0;
    sourceEntityID = [[EntityID alloc] init];
    sourceCommunicationsDeviceID = 0;
    sourceLineID = 0;
    transmitPriority = 0;
    transmitLineState = 0;
    command = 0;
    masterEntityID = [[EntityID alloc] init];
    masterCommunicationsDeviceID = 0;
    intercomParametersLength = 0;
    intercomParameters = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [sourceEntityID release];
  [masterEntityID release];
  [intercomParameters release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [dataStream writeUnsignedByte:controlType];
    [dataStream writeUnsignedByte:communicationsChannelType];
    [sourceEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:sourceCommunicationsDeviceID];
    [dataStream writeUnsignedByte:sourceLineID];
    [dataStream writeUnsignedByte:transmitPriority];
    [dataStream writeUnsignedByte:transmitLineState];
    [dataStream writeUnsignedByte:command];
    [masterEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:masterCommunicationsDeviceID];
    [dataStream writeUnsignedInt:[intercomParameters count]];

     for(int idx = 0; idx < [intercomParameters count]; idx++)
     {
        IntercomCommunicationsParameters* x = [intercomParameters objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    controlType = [dataStream readUnsignedByte];
    communicationsChannelType = [dataStream readUnsignedByte];
    [sourceEntityID unmarshalUsingStream:dataStream];
    sourceCommunicationsDeviceID = [dataStream readUnsignedByte];
    sourceLineID = [dataStream readUnsignedByte];
    transmitPriority = [dataStream readUnsignedByte];
    transmitLineState = [dataStream readUnsignedByte];
    command = [dataStream readUnsignedByte];
    [masterEntityID unmarshalUsingStream:dataStream];
    masterCommunicationsDeviceID = [dataStream readUnsignedShort];
    intercomParametersLength = [dataStream readUnsignedInt];

     [intercomParameters removeAllObjects];
     for(int idx = 0; idx < intercomParametersLength; idx++)
     {
        IntercomCommunicationsParameters* x;
        [x unmarshalUsingStream:dataStream];
        [intercomParameters addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + 1;  // controlType
   marshalSize = marshalSize + 1;  // communicationsChannelType
   marshalSize = marshalSize + [sourceEntityID getMarshalledSize];
   marshalSize = marshalSize + 1;  // sourceCommunicationsDeviceID
   marshalSize = marshalSize + 1;  // sourceLineID
   marshalSize = marshalSize + 1;  // transmitPriority
   marshalSize = marshalSize + 1;  // transmitLineState
   marshalSize = marshalSize + 1;  // command
   marshalSize = marshalSize + [masterEntityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // masterCommunicationsDeviceID
   marshalSize = marshalSize + 4;  // intercomParametersLength

   for(int idx=0; idx < [intercomParameters count]; idx++)
   {
        IntercomCommunicationsParameters* listElement = [intercomParameters objectAtIndex:idx];
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
