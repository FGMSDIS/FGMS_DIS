#import "ElectronicEmissionBeamData.h" 


@implementation ElectronicEmissionBeamData

@synthesize beamDataLength;
@synthesize beamIDNumber;
@synthesize beamParameterIndex;
@synthesize fundamentalParameterData;
@synthesize beamFunction;
@synthesize numberOfTrackJamTargets;
@synthesize highDensityTrackJam;
@synthesize pad4;
@synthesize jammingModeSequence;
@synthesize trackJamTargets;

-(id)init
{
  self = [super init];
  if(self)
  {
    pad4 = 0;
    beamDataLength = 0;
    beamIDNumber = 0;
    beamParameterIndex = 0;
    fundamentalParameterData = [[FundamentalParameterData alloc] init];
    beamFunction = 0;
    numberOfTrackJamTargets = 0;
    highDensityTrackJam = 0;
    jammingModeSequence = 0;
    trackJamTargets = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [fundamentalParameterData release];
  [trackJamTargets release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedByte:beamDataLength];
    [dataStream writeUnsignedByte:beamIDNumber];
    [dataStream writeUnsignedShort:beamParameterIndex];
    [fundamentalParameterData marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:beamFunction];
    [dataStream writeUnsignedByte:[trackJamTargets count]];
    [dataStream writeUnsignedByte:highDensityTrackJam];
    [dataStream writeUnsignedByte:pad4];
    [dataStream writeUnsignedInt:jammingModeSequence];

     for(int idx = 0; idx < [trackJamTargets count]; idx++)
     {
        TrackJamTarget* x = [trackJamTargets objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    beamDataLength = [dataStream readUnsignedByte];
    beamIDNumber = [dataStream readUnsignedByte];
    beamParameterIndex = [dataStream readUnsignedShort];
    [fundamentalParameterData unmarshalUsingStream:dataStream];
    beamFunction = [dataStream readUnsignedByte];
    numberOfTrackJamTargets = [dataStream readUnsignedByte];
    highDensityTrackJam = [dataStream readUnsignedByte];
    pad4 = [dataStream readUnsignedByte];
    jammingModeSequence = [dataStream readUnsignedInt];

     [trackJamTargets removeAllObjects];
     for(int idx = 0; idx < numberOfTrackJamTargets; idx++)
     {
        TrackJamTarget* x;
        [x unmarshalUsingStream:dataStream];
        [trackJamTargets addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 1;  // beamDataLength
   marshalSize = marshalSize + 1;  // beamIDNumber
   marshalSize = marshalSize + 2;  // beamParameterIndex
   marshalSize = marshalSize + [fundamentalParameterData getMarshalledSize];
   marshalSize = marshalSize + 1;  // beamFunction
   marshalSize = marshalSize + 1;  // numberOfTrackJamTargets
   marshalSize = marshalSize + 1;  // highDensityTrackJam
   marshalSize = marshalSize + 1;  // pad4
   marshalSize = marshalSize + 4;  // jammingModeSequence

   for(int idx=0; idx < [trackJamTargets count]; idx++)
   {
        TrackJamTarget* listElement = [trackJamTargets objectAtIndex:idx];
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
