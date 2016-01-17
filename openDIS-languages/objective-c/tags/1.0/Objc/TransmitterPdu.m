#import "TransmitterPdu.h" 


@implementation TransmitterPdu

@synthesize radioEntityType;
@synthesize transmitState;
@synthesize inputSource;
@synthesize padding1;
@synthesize antennaLocation;
@synthesize relativeAntennaLocation;
@synthesize antennaPatternType;
@synthesize antennaPatternCount;
@synthesize frequency;
@synthesize transmitFrequencyBandwidth;
@synthesize power;
@synthesize modulationType;
@synthesize cryptoSystem;
@synthesize cryptoKeyId;
@synthesize modulationParameterCount;
@synthesize padding2;
@synthesize padding3;
@synthesize modulationParametersList;
@synthesize antennaPatternList;

-(id)init
{
  self = [super init];
  if(self)
  {
    padding2 = 0;
    padding3 = 0;
    [self setPduType:25];
    radioEntityType = [[RadioEntityType alloc] init];
    transmitState = 0;
    inputSource = 0;
    padding1 = 0;
    antennaLocation = [[Vector3Double alloc] init];
    relativeAntennaLocation = [[Vector3Float alloc] init];
    antennaPatternType = 0;
    antennaPatternCount = 0;
    frequency = 0;
    transmitFrequencyBandwidth = 0;
    power = 0;
    modulationType = [[ModulationType alloc] init];
    cryptoSystem = 0;
    cryptoKeyId = 0;
    modulationParameterCount = 0;
    modulationParametersList = [NSMutableArray arrayWithCapacity:1];
    antennaPatternList = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [radioEntityType release];
  [antennaLocation release];
  [relativeAntennaLocation release];
  [modulationType release];
  [modulationParametersList release];
  [antennaPatternList release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [radioEntityType marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:transmitState];
    [dataStream writeUnsignedByte:inputSource];
    [dataStream writeUnsignedShort:padding1];
    [antennaLocation marshalUsingStream:dataStream];
    [relativeAntennaLocation marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:antennaPatternType];
    [dataStream writeUnsignedShort:[antennaPatternList count]];
    [dataStream writeLong:frequency];
    [dataStream writeFloat:transmitFrequencyBandwidth];
    [dataStream writeFloat:power];
    [modulationType marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:cryptoSystem];
    [dataStream writeUnsignedShort:cryptoKeyId];
    [dataStream writeUnsignedByte:[modulationParametersList count]];
    [dataStream writeUnsignedShort:padding2];
    [dataStream writeUnsignedByte:padding3];

     for(int idx = 0; idx < [modulationParametersList count]; idx++)
     {
        Vector3Float* x = [modulationParametersList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [antennaPatternList count]; idx++)
     {
        Vector3Float* x = [antennaPatternList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [radioEntityType unmarshalUsingStream:dataStream];
    transmitState = [dataStream readUnsignedByte];
    inputSource = [dataStream readUnsignedByte];
    padding1 = [dataStream readUnsignedShort];
    [antennaLocation unmarshalUsingStream:dataStream];
    [relativeAntennaLocation unmarshalUsingStream:dataStream];
    antennaPatternType = [dataStream readUnsignedShort];
    antennaPatternCount = [dataStream readUnsignedShort];
    frequency = [dataStream readLong];
    transmitFrequencyBandwidth = [dataStream readFloat];
    power = [dataStream readFloat];
    [modulationType unmarshalUsingStream:dataStream];
    cryptoSystem = [dataStream readUnsignedShort];
    cryptoKeyId = [dataStream readUnsignedShort];
    modulationParameterCount = [dataStream readUnsignedByte];
    padding2 = [dataStream readUnsignedShort];
    padding3 = [dataStream readUnsignedByte];

     [modulationParametersList removeAllObjects];
     for(int idx = 0; idx < modulationParameterCount; idx++)
     {
        Vector3Float* x;
        [x unmarshalUsingStream:dataStream];
        [modulationParametersList addObject:x];
     }

     [antennaPatternList removeAllObjects];
     for(int idx = 0; idx < antennaPatternCount; idx++)
     {
        Vector3Float* x;
        [x unmarshalUsingStream:dataStream];
        [antennaPatternList addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [radioEntityType getMarshalledSize];
   marshalSize = marshalSize + 1;  // transmitState
   marshalSize = marshalSize + 1;  // inputSource
   marshalSize = marshalSize + 2;  // padding1
   marshalSize = marshalSize + [antennaLocation getMarshalledSize];
   marshalSize = marshalSize + [relativeAntennaLocation getMarshalledSize];
   marshalSize = marshalSize + 2;  // antennaPatternType
   marshalSize = marshalSize + 2;  // antennaPatternCount
   marshalSize = marshalSize + 8;  // frequency
   marshalSize = marshalSize + 4;  // transmitFrequencyBandwidth
   marshalSize = marshalSize + 4;  // power
   marshalSize = marshalSize + [modulationType getMarshalledSize];
   marshalSize = marshalSize + 2;  // cryptoSystem
   marshalSize = marshalSize + 2;  // cryptoKeyId
   marshalSize = marshalSize + 1;  // modulationParameterCount
   marshalSize = marshalSize + 2;  // padding2
   marshalSize = marshalSize + 1;  // padding3

   for(int idx=0; idx < [modulationParametersList count]; idx++)
   {
        Vector3Float* listElement = [modulationParametersList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [antennaPatternList count]; idx++)
   {
        Vector3Float* listElement = [antennaPatternList objectAtIndex:idx];
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
