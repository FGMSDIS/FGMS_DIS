#import "DirectedEnergyAreaAimpoint.h" 


@implementation DirectedEnergyAreaAimpoint

@synthesize recordType;
@synthesize recordLength;
@synthesize padding;
@synthesize beamAntennaPatternRecordCount;
@synthesize directedEnergyTargetEnergyDepositionRecordCount;
@synthesize beamAntennaParameterList;
@synthesize directedEnergyTargetEnergyDepositionRecordList;

-(id)init
{
  self = [super init];
  if(self)
  {
    recordType = 4001;
    padding = 0;
    beamAntennaPatternRecordCount = 0;
    directedEnergyTargetEnergyDepositionRecordCount = 0;
    recordLength = 0;
    beamAntennaParameterList = [NSMutableArray arrayWithCapacity:1];
    directedEnergyTargetEnergyDepositionRecordList = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [beamAntennaParameterList release];
  [directedEnergyTargetEnergyDepositionRecordList release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedInt:recordType];
    [dataStream writeUnsignedShort:recordLength];
    [dataStream writeUnsignedShort:padding];
    [dataStream writeUnsignedShort:[beamAntennaParameterList count]];
    [dataStream writeUnsignedShort:[directedEnergyTargetEnergyDepositionRecordList count]];

     for(int idx = 0; idx < [beamAntennaParameterList count]; idx++)
     {
        BeamAntennaPattern* x = [beamAntennaParameterList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [directedEnergyTargetEnergyDepositionRecordList count]; idx++)
     {
        DirectedEnergyTargetEnergyDeposition* x = [directedEnergyTargetEnergyDepositionRecordList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    recordType = [dataStream readUnsignedInt];
    recordLength = [dataStream readUnsignedShort];
    padding = [dataStream readUnsignedShort];
    beamAntennaPatternRecordCount = [dataStream readUnsignedShort];
    directedEnergyTargetEnergyDepositionRecordCount = [dataStream readUnsignedShort];

     [beamAntennaParameterList removeAllObjects];
     for(int idx = 0; idx < beamAntennaPatternRecordCount; idx++)
     {
        BeamAntennaPattern* x;
        [x unmarshalUsingStream:dataStream];
        [beamAntennaParameterList addObject:x];
     }

     [directedEnergyTargetEnergyDepositionRecordList removeAllObjects];
     for(int idx = 0; idx < directedEnergyTargetEnergyDepositionRecordCount; idx++)
     {
        DirectedEnergyTargetEnergyDeposition* x;
        [x unmarshalUsingStream:dataStream];
        [directedEnergyTargetEnergyDepositionRecordList addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 4;  // recordType
   marshalSize = marshalSize + 2;  // recordLength
   marshalSize = marshalSize + 2;  // padding
   marshalSize = marshalSize + 2;  // beamAntennaPatternRecordCount
   marshalSize = marshalSize + 2;  // directedEnergyTargetEnergyDepositionRecordCount

   for(int idx=0; idx < [beamAntennaParameterList count]; idx++)
   {
        BeamAntennaPattern* listElement = [beamAntennaParameterList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [directedEnergyTargetEnergyDepositionRecordList count]; idx++)
   {
        DirectedEnergyTargetEnergyDeposition* listElement = [directedEnergyTargetEnergyDepositionRecordList objectAtIndex:idx];
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
