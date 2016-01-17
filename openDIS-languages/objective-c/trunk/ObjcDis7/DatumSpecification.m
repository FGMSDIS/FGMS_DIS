#import "DatumSpecification.h" 


@implementation DatumSpecification

@synthesize numberOfFixedDatums;
@synthesize numberOfVariableDatums;
@synthesize fixedDatumIDList;
@synthesize variableDatumIDList;

-(id)init
{
  self = [super init];
  if(self)
  {
    numberOfFixedDatums = 0;
    numberOfVariableDatums = 0;
    fixedDatumIDList = [NSMutableArray arrayWithCapacity:1];
    variableDatumIDList = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [fixedDatumIDList release];
  [variableDatumIDList release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedInt:[fixedDatumIDList count]];
    [dataStream writeUnsignedInt:[variableDatumIDList count]];

     for(int idx = 0; idx < [fixedDatumIDList count]; idx++)
     {
        FixedDatum* x = [fixedDatumIDList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [variableDatumIDList count]; idx++)
     {
        VariableDatum* x = [variableDatumIDList objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    numberOfFixedDatums = [dataStream readUnsignedInt];
    numberOfVariableDatums = [dataStream readUnsignedInt];

     [fixedDatumIDList removeAllObjects];
     for(int idx = 0; idx < numberOfFixedDatums; idx++)
     {
        FixedDatum* x;
        [x unmarshalUsingStream:dataStream];
        [fixedDatumIDList addObject:x];
     }

     [variableDatumIDList removeAllObjects];
     for(int idx = 0; idx < numberOfVariableDatums; idx++)
     {
        VariableDatum* x;
        [x unmarshalUsingStream:dataStream];
        [variableDatumIDList addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 4;  // numberOfFixedDatums
   marshalSize = marshalSize + 4;  // numberOfVariableDatums

   for(int idx=0; idx < [fixedDatumIDList count]; idx++)
   {
        FixedDatum* listElement = [fixedDatumIDList objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [variableDatumIDList count]; idx++)
   {
        VariableDatum* listElement = [variableDatumIDList objectAtIndex:idx];
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
