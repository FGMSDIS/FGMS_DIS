#import "SetDataPdu.h" 


@implementation SetDataPdu

@synthesize requestID;
@synthesize padding1;
@synthesize numberOfFixedDatumRecords;
@synthesize numberOfVariableDatumRecords;
@synthesize fixedDatums;
@synthesize variableDatums;

-(id)init
{
  self = [super init];
  if(self)
  {
    padding1 = 0;
    [self setPduType:19];
    requestID = 0;
    numberOfFixedDatumRecords = 0;
    numberOfVariableDatumRecords = 0;
    fixedDatums = [NSMutableArray arrayWithCapacity:1];
    variableDatums = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [fixedDatums release];
  [variableDatums release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [dataStream writeUnsignedInt:requestID];
    [dataStream writeUnsignedInt:padding1];
    [dataStream writeUnsignedInt:[fixedDatums count]];
    [dataStream writeUnsignedInt:[variableDatums count]];

     for(int idx = 0; idx < [fixedDatums count]; idx++)
     {
        FixedDatum* x = [fixedDatums objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [variableDatums count]; idx++)
     {
        VariableDatum* x = [variableDatums objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    requestID = [dataStream readUnsignedInt];
    padding1 = [dataStream readUnsignedInt];
    numberOfFixedDatumRecords = [dataStream readUnsignedInt];
    numberOfVariableDatumRecords = [dataStream readUnsignedInt];

     [fixedDatums removeAllObjects];
     for(int idx = 0; idx < numberOfFixedDatumRecords; idx++)
     {
        FixedDatum* x;
        [x unmarshalUsingStream:dataStream];
        [fixedDatums addObject:x];
     }

     [variableDatums removeAllObjects];
     for(int idx = 0; idx < numberOfVariableDatumRecords; idx++)
     {
        VariableDatum* x;
        [x unmarshalUsingStream:dataStream];
        [variableDatums addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + 4;  // requestID
   marshalSize = marshalSize + 4;  // padding1
   marshalSize = marshalSize + 4;  // numberOfFixedDatumRecords
   marshalSize = marshalSize + 4;  // numberOfVariableDatumRecords

   for(int idx=0; idx < [fixedDatums count]; idx++)
   {
        FixedDatum* listElement = [fixedDatums objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [variableDatums count]; idx++)
   {
        VariableDatum* listElement = [variableDatums objectAtIndex:idx];
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
