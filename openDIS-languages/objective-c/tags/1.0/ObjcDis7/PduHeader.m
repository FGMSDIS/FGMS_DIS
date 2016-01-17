#import "PduHeader.h" 


@implementation PduHeader

@synthesize protocolVersion;
@synthesize exerciseID;
@synthesize pduType;
@synthesize protocolFamily;
@synthesize timestamp;
@synthesize pduLength;
@synthesize pduStatus;
@synthesize padding;

-(id)init
{
  self = [super init];
  if(self)
  {
    protocolVersion = 7;
    exerciseID = 0;
    padding = 0;
    pduType = 0;
    protocolFamily = 0;
    timestamp = 0;
    pduLength = 0;
    pduStatus = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedByte:protocolVersion];
    [dataStream writeUnsignedByte:exerciseID];
    [dataStream writeUnsignedByte:pduType];
    [dataStream writeUnsignedByte:protocolFamily];
    [dataStream writeUnsignedInt:timestamp];
    [dataStream writeUnsignedByte:pduLength];
    [dataStream writeUnsignedShort:pduStatus];
    [dataStream writeUnsignedByte:padding];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    protocolVersion = [dataStream readUnsignedByte];
    exerciseID = [dataStream readUnsignedByte];
    pduType = [dataStream readUnsignedByte];
    protocolFamily = [dataStream readUnsignedByte];
    timestamp = [dataStream readUnsignedInt];
    pduLength = [dataStream readUnsignedByte];
    pduStatus = [dataStream readUnsignedShort];
    padding = [dataStream readUnsignedByte];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 1;  // protocolVersion
   marshalSize = marshalSize + 1;  // exerciseID
   marshalSize = marshalSize + 1;  // pduType
   marshalSize = marshalSize + 1;  // protocolFamily
   marshalSize = marshalSize + 4;  // timestamp
   marshalSize = marshalSize + 1;  // pduLength
   marshalSize = marshalSize + 2;  // pduStatus
   marshalSize = marshalSize + 1;  // padding
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
