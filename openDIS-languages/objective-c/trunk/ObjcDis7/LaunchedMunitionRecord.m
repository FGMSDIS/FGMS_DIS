#import "LaunchedMunitionRecord.h" 


@implementation LaunchedMunitionRecord

@synthesize fireEventID;
@synthesize padding;
@synthesize firingEntityID;
@synthesize padding2;
@synthesize targetEntityID;
@synthesize padding3;
@synthesize targetLocation;

-(id)init
{
  self = [super init];
  if(self)
  {
    fireEventID = [[EventIdentifier alloc] init];
    padding = 0;
    firingEntityID = [[EventIdentifier alloc] init];
    padding2 = 0;
    targetEntityID = [[EventIdentifier alloc] init];
    padding3 = 0;
    targetLocation = [[Vector3Double alloc] init];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [fireEventID release];
  [firingEntityID release];
  [targetEntityID release];
  [targetLocation release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [fireEventID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:padding];
    [firingEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:padding2];
    [targetEntityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:padding3];
    [targetLocation marshalUsingStream:dataStream];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [fireEventID unmarshalUsingStream:dataStream];
    padding = [dataStream readUnsignedShort];
    [firingEntityID unmarshalUsingStream:dataStream];
    padding2 = [dataStream readUnsignedShort];
    [targetEntityID unmarshalUsingStream:dataStream];
    padding3 = [dataStream readUnsignedShort];
    [targetLocation unmarshalUsingStream:dataStream];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + [fireEventID getMarshalledSize];
   marshalSize = marshalSize + 2;  // padding
   marshalSize = marshalSize + [firingEntityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // padding2
   marshalSize = marshalSize + [targetEntityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // padding3
   marshalSize = marshalSize + [targetLocation getMarshalledSize];
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
