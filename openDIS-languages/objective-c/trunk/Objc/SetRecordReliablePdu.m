#import "SetRecordReliablePdu.h" 


@implementation SetRecordReliablePdu

@synthesize requestID;
@synthesize requiredReliabilityService;
@synthesize pad1;
@synthesize pad2;
@synthesize numberOfRecordSets;
@synthesize recordSets;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:64];
    requestID = 0;
    requiredReliabilityService = 0;
    pad1 = 0;
    pad2 = 0;
    numberOfRecordSets = 0;
    recordSets = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [recordSets release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [dataStream writeUnsignedInt:requestID];
    [dataStream writeUnsignedByte:requiredReliabilityService];
    [dataStream writeUnsignedShort:pad1];
    [dataStream writeUnsignedByte:pad2];
    [dataStream writeUnsignedInt:[recordSets count]];

     for(int idx = 0; idx < [recordSets count]; idx++)
     {
        RecordSet* x = [recordSets objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    requestID = [dataStream readUnsignedInt];
    requiredReliabilityService = [dataStream readUnsignedByte];
    pad1 = [dataStream readUnsignedShort];
    pad2 = [dataStream readUnsignedByte];
    numberOfRecordSets = [dataStream readUnsignedInt];

     [recordSets removeAllObjects];
     for(int idx = 0; idx < numberOfRecordSets; idx++)
     {
        RecordSet* x;
        [x unmarshalUsingStream:dataStream];
        [recordSets addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + 4;  // requestID
   marshalSize = marshalSize + 1;  // requiredReliabilityService
   marshalSize = marshalSize + 2;  // pad1
   marshalSize = marshalSize + 1;  // pad2
   marshalSize = marshalSize + 4;  // numberOfRecordSets

   for(int idx=0; idx < [recordSets count]; idx++)
   {
        RecordSet* listElement = [recordSets objectAtIndex:idx];
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
