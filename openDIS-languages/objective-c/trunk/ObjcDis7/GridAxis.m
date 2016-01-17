#import "GridAxis.h" 


@implementation GridAxis

@synthesize domainInitialXi;
@synthesize domainFinalXi;
@synthesize domainPointsXi;
@synthesize interleafFactor;
@synthesize axisType;
@synthesize numberOfPointsOnXiAxis;
@synthesize initialIndex;

-(id)init
{
  self = [super init];
  if(self)
  {
    domainInitialXi = 0;
    domainFinalXi = 0;
    domainPointsXi = 0;
    interleafFactor = 0;
    axisType = 0;
    numberOfPointsOnXiAxis = 0;
    initialIndex = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeDouble:domainInitialXi];
    [dataStream writeDouble:domainFinalXi];
    [dataStream writeUnsignedShort:domainPointsXi];
    [dataStream writeUnsignedByte:interleafFactor];
    [dataStream writeUnsignedByte:axisType];
    [dataStream writeUnsignedShort:numberOfPointsOnXiAxis];
    [dataStream writeUnsignedShort:initialIndex];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    domainInitialXi = [dataStream readDouble];
    domainFinalXi = [dataStream readDouble];
    domainPointsXi = [dataStream readUnsignedShort];
    interleafFactor = [dataStream readUnsignedByte];
    axisType = [dataStream readUnsignedByte];
    numberOfPointsOnXiAxis = [dataStream readUnsignedShort];
    initialIndex = [dataStream readUnsignedShort];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 8;  // domainInitialXi
   marshalSize = marshalSize + 8;  // domainFinalXi
   marshalSize = marshalSize + 2;  // domainPointsXi
   marshalSize = marshalSize + 1;  // interleafFactor
   marshalSize = marshalSize + 1;  // axisType
   marshalSize = marshalSize + 2;  // numberOfPointsOnXiAxis
   marshalSize = marshalSize + 2;  // initialIndex
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
