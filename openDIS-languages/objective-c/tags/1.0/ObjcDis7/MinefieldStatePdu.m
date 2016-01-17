#import "MinefieldStatePdu.h" 


@implementation MinefieldStatePdu

@synthesize minefieldID;
@synthesize minefieldSequence;
@synthesize forceID;
@synthesize numberOfPerimeterPoints;
@synthesize minefieldType;
@synthesize numberOfMineTypes;
@synthesize minefieldLocation;
@synthesize minefieldOrientation;
@synthesize appearance;
@synthesize protocolMode;
@synthesize perimeterPoints;
@synthesize mineType;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:37];
    minefieldID = [[MinefieldIdentifier alloc] init];
    minefieldSequence = 0;
    forceID = 0;
    numberOfPerimeterPoints = 0;
    minefieldType = [[EntityType alloc] init];
    numberOfMineTypes = 0;
    minefieldLocation = [[Vector3Double alloc] init];
    minefieldOrientation = [[EulerAngles alloc] init];
    appearance = 0;
    protocolMode = 0;
    perimeterPoints = [NSMutableArray arrayWithCapacity:1];
    mineType = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [minefieldID release];
  [minefieldType release];
  [minefieldLocation release];
  [minefieldOrientation release];
  [perimeterPoints release];
  [mineType release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [minefieldID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:minefieldSequence];
    [dataStream writeUnsignedByte:forceID];
    [dataStream writeUnsignedByte:[perimeterPoints count]];
    [minefieldType marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:[mineType count]];
    [minefieldLocation marshalUsingStream:dataStream];
    [minefieldOrientation marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:appearance];
    [dataStream writeUnsignedShort:protocolMode];

     for(int idx = 0; idx < [perimeterPoints count]; idx++)
     {
        Vector2Float* x = [perimeterPoints objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }


     for(int idx = 0; idx < [mineType count]; idx++)
     {
        EntityType* x = [mineType objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    [minefieldID unmarshalUsingStream:dataStream];
    minefieldSequence = [dataStream readUnsignedShort];
    forceID = [dataStream readUnsignedByte];
    numberOfPerimeterPoints = [dataStream readUnsignedByte];
    [minefieldType unmarshalUsingStream:dataStream];
    numberOfMineTypes = [dataStream readUnsignedShort];
    [minefieldLocation unmarshalUsingStream:dataStream];
    [minefieldOrientation unmarshalUsingStream:dataStream];
    appearance = [dataStream readUnsignedShort];
    protocolMode = [dataStream readUnsignedShort];

     [perimeterPoints removeAllObjects];
     for(int idx = 0; idx < numberOfPerimeterPoints; idx++)
     {
        Vector2Float* x;
        [x unmarshalUsingStream:dataStream];
        [perimeterPoints addObject:x];
     }

     [mineType removeAllObjects];
     for(int idx = 0; idx < numberOfMineTypes; idx++)
     {
        EntityType* x;
        [x unmarshalUsingStream:dataStream];
        [mineType addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + [minefieldID getMarshalledSize];
   marshalSize = marshalSize + 2;  // minefieldSequence
   marshalSize = marshalSize + 1;  // forceID
   marshalSize = marshalSize + 1;  // numberOfPerimeterPoints
   marshalSize = marshalSize + [minefieldType getMarshalledSize];
   marshalSize = marshalSize + 2;  // numberOfMineTypes
   marshalSize = marshalSize + [minefieldLocation getMarshalledSize];
   marshalSize = marshalSize + [minefieldOrientation getMarshalledSize];
   marshalSize = marshalSize + 2;  // appearance
   marshalSize = marshalSize + 2;  // protocolMode

   for(int idx=0; idx < [perimeterPoints count]; idx++)
   {
        Vector2Float* listElement = [perimeterPoints objectAtIndex:idx];
        marshalSize = marshalSize + [listElement getMarshalledSize];
    }


   for(int idx=0; idx < [mineType count]; idx++)
   {
        EntityType* listElement = [mineType objectAtIndex:idx];
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
