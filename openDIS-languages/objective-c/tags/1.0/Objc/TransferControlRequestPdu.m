#import "TransferControlRequestPdu.h" 


@implementation TransferControlRequestPdu

@synthesize orginatingEntityID;
@synthesize recevingEntityID;
@synthesize requestID;
@synthesize requiredReliabilityService;
@synthesize tranferType;
@synthesize transferEntityID;
@synthesize numberOfRecordSets;
@synthesize recordSets;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:35];
    orginatingEntityID = [[EntityID alloc] init];
    recevingEntityID = [[EntityID alloc] init];
    requestID = 0;
    requiredReliabilityService = 0;
    tranferType = 0;
    transferEntityID = [[EntityID alloc] init];
    numberOfRecordSets = 0;
    recordSets = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [orginatingEntityID release];
  [recevingEntityID release];
  [transferEntityID release];
  [recordSets release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [orginatingEntityID marshalUsingStream:dataStream];
    [recevingEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedInt:requestID];
    [dataStream writeUnsignedByte:requiredReliabilityService];
    [dataStream writeUnsignedByte:tranferType];
    [transferEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedByte:[recordSets count]];

     for(int idx = 0; idx < [recordSets count]; idx++)
     {
        RecordSet* x = [recordSets objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [orginatingEntityID unmarshalUsingStream:dataStream];
    [recevingEntityID unmarshalUsingStream:dataStream];
    requestID = [dataStream readUnsignedInt];
    requiredReliabilityService = [dataStream readUnsignedByte];
    tranferType = [dataStream readUnsignedByte];
    [transferEntityID unmarshalUsingStream:dataStream];
    numberOfRecordSets = [dataStream readUnsignedByte];

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
   marshalSize = marshalSize + [orginatingEntityID getMarshalledSize];
   marshalSize = marshalSize + [recevingEntityID getMarshalledSize];
   marshalSize = marshalSize + 4;  // requestID
   marshalSize = marshalSize + 1;  // requiredReliabilityService
   marshalSize = marshalSize + 1;  // tranferType
   marshalSize = marshalSize + [transferEntityID getMarshalledSize];
   marshalSize = marshalSize + 1;  // numberOfRecordSets

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
