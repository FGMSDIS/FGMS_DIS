#import "BeamAntennaPattern.h" 


@implementation BeamAntennaPattern

@synthesize beamDirection;
@synthesize azimuthBeamwidth;
@synthesize referenceSystem;
@synthesize padding1;
@synthesize padding2;
@synthesize ez;
@synthesize ex;
@synthesize phase;

-(id)init
{
  self = [super init];
  if(self)
  {
    azimuthBeamwidth = 0;
    referenceSystem = 0;
    padding1 = 0;
    padding2 = 0;
    beamDirection = [[Orientation alloc] init];
    ez = 0;
    ex = 0;
    phase = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [beamDirection release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [beamDirection marshalUsingStream:dataStream];
    [dataStream writeFloat:azimuthBeamwidth];
    [dataStream writeFloat:referenceSystem];
    [dataStream writeShort:padding1];
    [dataStream writeByte:padding2];
    [dataStream writeFloat:ez];
    [dataStream writeFloat:ex];
    [dataStream writeFloat:phase];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [beamDirection unmarshalUsingStream:dataStream];
    azimuthBeamwidth = [dataStream readFloat];
    referenceSystem = [dataStream readFloat];
    padding1 = [dataStream readShort];
    padding2 = [dataStream readByte];
    ez = [dataStream readFloat];
    ex = [dataStream readFloat];
    phase = [dataStream readFloat];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + [beamDirection getMarshalledSize];
   marshalSize = marshalSize + 4;  // azimuthBeamwidth
   marshalSize = marshalSize + 4;  // referenceSystem
   marshalSize = marshalSize + 2;  // padding1
   marshalSize = marshalSize + 1;  // padding2
   marshalSize = marshalSize + 4;  // ez
   marshalSize = marshalSize + 4;  // ex
   marshalSize = marshalSize + 4;  // phase
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
