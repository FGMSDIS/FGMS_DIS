#import "ElectronicEmissionSystemData.h" 


@implementation ElectronicEmissionSystemData

@synthesize systemDataLength;
@synthesize numberOfBeams;
@synthesize emissionsPadding2;
@synthesize emitterSystem;
@synthesize location;
@synthesize beamDataRecords;

-(id)init
{
  self = [super init];
  if(self)
  {
    emissionsPadding2 = 0;
    systemDataLength = 0;
    numberOfBeams = 0;
    emitterSystem = [[EmitterSystem alloc] init];
    location = [[Vector3Float alloc] init];
    beamDataRecords = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [emitterSystem release];
  [location release];
  [beamDataRecords release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedByte:systemDataLength];
    [dataStream writeUnsignedByte:[beamDataRecords count]];
    [dataStream writeUnsignedShort:emissionsPadding2];
    [emitterSystem marshalUsingStream:dataStream];
    [location marshalUsingStream:dataStream];

     for(int idx = 0; idx < [beamDataRecords count]; idx++)
     {
        ElectronicEmissionBeamData* x = [beamDataRecords objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    systemDataLength = [dataStream readUnsignedByte];
    numberOfBeams = [dataStream readUnsignedByte];
    emissionsPadding2 = [dataStream readUnsignedShort];
    [emitterSystem unmarshalUsingStream:dataStream];
    [location unmarshalUsingStream:dataStream];

     [beamDataRecords removeAllObjects];
     for(int idx = 0; idx < numberOfBeams; idx++)
     {
        ElectronicEmissionBeamData* x;
        [x unmarshalUsingStream:dataStream];
        [beamDataRecords addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 1;  // systemDataLength
   marshalSize = marshalSize + 1;  // numberOfBeams
   marshalSize = marshalSize + 2;  // emissionsPadding2
   marshalSize = marshalSize + [emitterSystem getMarshalledSize];
   marshalSize = marshalSize + [location getMarshalledSize];

   for(int idx=0; idx < [beamDataRecords count]; idx++)
   {
        ElectronicEmissionBeamData* listElement = [beamDataRecords objectAtIndex:idx];
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
