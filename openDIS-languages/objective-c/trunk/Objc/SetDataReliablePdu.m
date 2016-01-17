#import "SetDataReliablePdu.h" 


@implementation SetDataReliablePdu

@synthesize requiredReliabilityService;
@synthesize pad1;
@synthesize pad2;
@synthesize requestID;
@synthesize numberOfFixedDatumRecords;
@synthesize numberOfVariableDatumRecords;
@synthesize fixedDatumRecords;
@synthesize variableDatumRecords;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:59];
    requiredReliabilityService = 0;
    pad1 = 0;
    pad2 = 0;
    requestID = 0;
    numberOfFixedDatumRecords = 0;
    numberOfVariableDatumRecords = 0;
    fixedDatumRecords = [NSMutableArray arrayWithCapacity:1];
    variableDatumRecords = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [fixedDatumRecords release];
  [variableDatumRecords release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [dataStream writeUnsignedByte:requiredReliabilityService];
    [dataStream writeUnsignedShort:pad1];
    [dataStream writeUnsignedByte:pad2];
    [dataStream writeUnsignedInt:requestID];
    [dataStream writeUnsignedInt:[fixedDatumRecords count]];
    [dataStream writeUnsignedInt:[variableDatumRecords count]];

     for(int idx = 0; idx < [fixedDatumRecords count]; idx++)
     {
        FixedDatum* x = [fixedDatumRecords objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [variableDatumRecords count]; idx++)
     {
        VariableDatum* x = [variableDatumRecords objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    requiredReliabilityService = [dataStream readUnsignedByte];
    pad1 = [dataStream readUnsignedShort];
    pad2 = [dataStream readUnsignedByte];
    requestID = [dataStream readUnsignedInt];
    numberOfFixedDatumRecords = [dataStream readUnsignedInt];
    numberOfVariableDatumRecords = [dataStream readUnsignedInt];

     [fixedDatumRecords removeAllObjects];
     for(int idx = 0; idx < numberOfFixedDatumRecords; idx++)
     {
        FixedDatum* x;
        [x unmarshalUsingStream:dataStream];
        [fixedDatumRecords addObject:x];
     }

     [variableDatumRecords removeAllObjects];
     for(int idx = 0; idx < numberOfVariableDatumRecords; idx++)
     {
        VariableDatum* x;
        [x unmarshalUsingStream:dataStream];
        [variableDatumRecords addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + 1;  // requiredReliabilityService
   marshalSize = marshalSize + 2;  // pad1
   marshalSize = marshalSize + 1;  // pad2
   marshalSize = marshalSize + 4;  // requestID
   marshalSize = marshalSize + 4;  // numberOfFixedDatumRecords
   marshalSize = marshalSize + 4;  // numberOfVariableDatumRecords

   for(int idx=0; idx < [fixedDatumRecords count]; idx++)
   {
        FixedDatum* listElement = [fixedDatumRecords objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [variableDatumRecords count]; idx++)
   {
        VariableDatum* listElement = [variableDatumRecords objectAtIndex:idx];
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
