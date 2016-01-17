#import "FundamentalParameterDataIff.h" 


@implementation FundamentalParameterDataIff

@synthesize erp;
@synthesize frequency;
@synthesize pgrf;
@synthesize pulseWidth;
@synthesize burstLength;
@synthesize applicableModes;
@synthesize pad2;
@synthesize pad3;

-(id)init
{
  self = [super init];
  if(self)
  {
    erp = 0;
    frequency = 0;
    pgrf = 0;
    pulseWidth = 0;
    burstLength = 0;
    applicableModes = 0;
    pad2 = 0;
    pad3 = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeFloat:erp];
    [dataStream writeFloat:frequency];
    [dataStream writeFloat:pgrf];
    [dataStream writeFloat:pulseWidth];
    [dataStream writeUnsignedInt:burstLength];
    [dataStream writeUnsignedByte:applicableModes];
    [dataStream writeUnsignedShort:pad2];
    [dataStream writeUnsignedByte:pad3];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    erp = [dataStream readFloat];
    frequency = [dataStream readFloat];
    pgrf = [dataStream readFloat];
    pulseWidth = [dataStream readFloat];
    burstLength = [dataStream readUnsignedInt];
    applicableModes = [dataStream readUnsignedByte];
    pad2 = [dataStream readUnsignedShort];
    pad3 = [dataStream readUnsignedByte];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 4;  // erp
   marshalSize = marshalSize + 4;  // frequency
   marshalSize = marshalSize + 4;  // pgrf
   marshalSize = marshalSize + 4;  // pulseWidth
   marshalSize = marshalSize + 4;  // burstLength
   marshalSize = marshalSize + 1;  // applicableModes
   marshalSize = marshalSize + 2;  // pad2
   marshalSize = marshalSize + 1;  // pad3
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
