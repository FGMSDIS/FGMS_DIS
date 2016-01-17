#import "DirectedEnergyDamage.h" 


@implementation DirectedEnergyDamage

@synthesize recordType;
@synthesize recordLength;
@synthesize padding;
@synthesize damageLocation;
@synthesize damageDiameter;
@synthesize temperature;
@synthesize componentIdentification;
@synthesize componentDamageStatus;
@synthesize componentVisualDamageStatus;
@synthesize componentVisualSmokeColor;
@synthesize fireEventID;
@synthesize padding2;

-(id)init
{
  self = [super init];
  if(self)
  {
    recordType = 4500;
    recordLength = 40;
    padding = 0;
    temperature = -273.15;
    padding2 = 0;
    damageLocation = [[Vector3Float alloc] init];
    damageDiameter = 0;
    componentIdentification = 0;
    componentDamageStatus = 0;
    componentVisualDamageStatus = 0;
    componentVisualSmokeColor = 0;
    fireEventID = [[EventIdentifier alloc] init];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [damageLocation release];
  [fireEventID release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedInt:recordType];
    [dataStream writeUnsignedShort:recordLength];
    [dataStream writeUnsignedShort:padding];
    [damageLocation marshalUsingStream:dataStream];
    [dataStream writeFloat:damageDiameter];
    [dataStream writeFloat:temperature];
    [dataStream writeUnsignedByte:componentIdentification];
    [dataStream writeUnsignedByte:componentDamageStatus];
    [dataStream writeUnsignedByte:componentVisualDamageStatus];
    [dataStream writeUnsignedByte:componentVisualSmokeColor];
    [fireEventID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:padding2];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    recordType = [dataStream readUnsignedInt];
    recordLength = [dataStream readUnsignedShort];
    padding = [dataStream readUnsignedShort];
    [damageLocation unmarshalUsingStream:dataStream];
    damageDiameter = [dataStream readFloat];
    temperature = [dataStream readFloat];
    componentIdentification = [dataStream readUnsignedByte];
    componentDamageStatus = [dataStream readUnsignedByte];
    componentVisualDamageStatus = [dataStream readUnsignedByte];
    componentVisualSmokeColor = [dataStream readUnsignedByte];
    [fireEventID unmarshalUsingStream:dataStream];
    padding2 = [dataStream readUnsignedShort];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 4;  // recordType
   marshalSize = marshalSize + 2;  // recordLength
   marshalSize = marshalSize + 2;  // padding
   marshalSize = marshalSize + [damageLocation getMarshalledSize];
   marshalSize = marshalSize + 4;  // damageDiameter
   marshalSize = marshalSize + 4;  // temperature
   marshalSize = marshalSize + 1;  // componentIdentification
   marshalSize = marshalSize + 1;  // componentDamageStatus
   marshalSize = marshalSize + 1;  // componentVisualDamageStatus
   marshalSize = marshalSize + 1;  // componentVisualSmokeColor
   marshalSize = marshalSize + [fireEventID getMarshalledSize];
   marshalSize = marshalSize + 2;  // padding2
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
