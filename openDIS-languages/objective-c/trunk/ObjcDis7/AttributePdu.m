#import "AttributePdu.h" 


@implementation AttributePdu

@synthesize originatingSimulationAddress;
@synthesize padding1;
@synthesize padding2;
@synthesize attributeRecordPduType;
@synthesize attributeRecordProtocolVersion;
@synthesize masterAttributeRecordType;
@synthesize actionCode;
@synthesize padding3;
@synthesize numberAttributeRecordSet;

-(id)init
{
  self = [super init];
  if(self)
  {
    originatingSimulationAddress = [[SimulationAddress alloc] init];
    padding1 = 0;
    padding2 = 0;
    attributeRecordPduType = 0;
    attributeRecordProtocolVersion = 0;
    masterAttributeRecordType = 0;
    actionCode = 0;
    padding3 = 0;
    numberAttributeRecordSet = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [originatingSimulationAddress release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [originatingSimulationAddress marshalUsingStream:dataStream];
    [dataStream writeInt:padding1];
    [dataStream writeShort:padding2];
    [dataStream writeUnsignedByte:attributeRecordPduType];
    [dataStream writeUnsignedByte:attributeRecordProtocolVersion];
    [dataStream writeUnsignedInt:masterAttributeRecordType];
    [dataStream writeUnsignedByte:actionCode];
    [dataStream writeByte:padding3];
    [dataStream writeUnsignedShort:numberAttributeRecordSet];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [originatingSimulationAddress unmarshalUsingStream:dataStream];
    padding1 = [dataStream readInt];
    padding2 = [dataStream readShort];
    attributeRecordPduType = [dataStream readUnsignedByte];
    attributeRecordProtocolVersion = [dataStream readUnsignedByte];
    masterAttributeRecordType = [dataStream readUnsignedInt];
    actionCode = [dataStream readUnsignedByte];
    padding3 = [dataStream readByte];
    numberAttributeRecordSet = [dataStream readUnsignedShort];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [originatingSimulationAddress getMarshalledSize];
   marshalSize = marshalSize + 4;  // padding1
   marshalSize = marshalSize + 2;  // padding2
   marshalSize = marshalSize + 1;  // attributeRecordPduType
   marshalSize = marshalSize + 1;  // attributeRecordProtocolVersion
   marshalSize = marshalSize + 4;  // masterAttributeRecordType
   marshalSize = marshalSize + 1;  // actionCode
   marshalSize = marshalSize + 1;  // padding3
   marshalSize = marshalSize + 2;  // numberAttributeRecordSet
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
