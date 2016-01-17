#import "FastEntityStatePdu.h" 


@implementation FastEntityStatePdu

@synthesize site;
@synthesize application;
@synthesize entity;
@synthesize forceId;
@synthesize numberOfVariableParameters;
@synthesize entityKind;
@synthesize domain;
@synthesize country;
@synthesize category;
@synthesize subcategory;
@synthesize specific;
@synthesize extra;
@synthesize altEntityKind;
@synthesize altDomain;
@synthesize altCountry;
@synthesize altCategory;
@synthesize altSubcategory;
@synthesize altSpecific;
@synthesize altExtra;
@synthesize xVelocity;
@synthesize yVelocity;
@synthesize zVelocity;
@synthesize xLocation;
@synthesize yLocation;
@synthesize zLocation;
@synthesize psi;
@synthesize theta;
@synthesize phi;
@synthesize entityAppearance;
@synthesize deadReckoningAlgorithm;
@synthesize otherParametersPtr;
@synthesize otherParametersLength;
@synthesize xAcceleration;
@synthesize yAcceleration;
@synthesize zAcceleration;
@synthesize xAngularVelocity;
@synthesize yAngularVelocity;
@synthesize zAngularVelocity;
@synthesize markingPtr;
@synthesize markingLength;
@synthesize capabilities;
@synthesize variableParameters;

-(id)init
{
  self = [super init];
  if(self)
  {
    [self setPduType:1];
    site = 0;
    application = 0;
    entity = 0;
    forceId = 0;
    numberOfVariableParameters = 0;
    entityKind = 0;
    domain = 0;
    country = 0;
    category = 0;
    subcategory = 0;
    specific = 0;
    extra = 0;
    altEntityKind = 0;
    altDomain = 0;
    altCountry = 0;
    altCategory = 0;
    altSubcategory = 0;
    altSpecific = 0;
    altExtra = 0;
    xVelocity = 0;
    yVelocity = 0;
    zVelocity = 0;
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
    psi = 0;
    theta = 0;
    phi = 0;
    entityAppearance = 0;
    deadReckoningAlgorithm = 0;
     // Initialize fixed length array
     int lengthotherParameters;
     for(lengthotherParameters = 0; lengthotherParameters < 15; lengthotherParameters++)
     {
         otherParameters[lengthotherParameters] = 0;
     }
     otherParametersPtr = &otherParameters[0];

    xAcceleration = 0;
    yAcceleration = 0;
    zAcceleration = 0;
    xAngularVelocity = 0;
    yAngularVelocity = 0;
    zAngularVelocity = 0;
     // Initialize fixed length array
     int lengthmarking;
     for(lengthmarking = 0; lengthmarking < 12; lengthmarking++)
     {
         marking[lengthmarking] = 0;
     }
     markingPtr = &marking[0];

    capabilities = 0;
    variableParameters = [NSMutableArray arrayWithCapacity:1];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [variableParameters release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [super marshalUsingStream:dataStream]; // Marshal information in superclass first
    [dataStream writeUnsignedShort:site];
    [dataStream writeUnsignedShort:application];
    [dataStream writeUnsignedShort:entity];
    [dataStream writeUnsignedByte:forceId];
    [dataStream writeByte:[variableParameters count]];
    [dataStream writeUnsignedByte:entityKind];
    [dataStream writeUnsignedByte:domain];
    [dataStream writeUnsignedShort:country];
    [dataStream writeUnsignedByte:category];
    [dataStream writeUnsignedByte:subcategory];
    [dataStream writeUnsignedByte:specific];
    [dataStream writeUnsignedByte:extra];
    [dataStream writeUnsignedByte:altEntityKind];
    [dataStream writeUnsignedByte:altDomain];
    [dataStream writeUnsignedShort:altCountry];
    [dataStream writeUnsignedByte:altCategory];
    [dataStream writeUnsignedByte:altSubcategory];
    [dataStream writeUnsignedByte:altSpecific];
    [dataStream writeUnsignedByte:altExtra];
    [dataStream writeFloat:xVelocity];
    [dataStream writeFloat:yVelocity];
    [dataStream writeFloat:zVelocity];
    [dataStream writeDouble:xLocation];
    [dataStream writeDouble:yLocation];
    [dataStream writeDouble:zLocation];
    [dataStream writeFloat:psi];
    [dataStream writeFloat:theta];
    [dataStream writeFloat:phi];
    [dataStream writeInt:entityAppearance];
    [dataStream writeUnsignedByte:deadReckoningAlgorithm];

     for(int idx = 0; idx < 15; idx++)
     {
    [dataStream writeByte:otherParameters[idx]];
     }

    [dataStream writeFloat:xAcceleration];
    [dataStream writeFloat:yAcceleration];
    [dataStream writeFloat:zAcceleration];
    [dataStream writeFloat:xAngularVelocity];
    [dataStream writeFloat:yAngularVelocity];
    [dataStream writeFloat:zAngularVelocity];

     for(int idx = 0; idx < 12; idx++)
     {
    [dataStream writeByte:marking[idx]];
     }

    [dataStream writeInt:capabilities];

     for(int idx = 0; idx < [variableParameters count]; idx++)
     {
        VariableParameter* x = [variableParameters objectAtIndex:idx];
        [x marshalUsingStream:dataStream];
     }

}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    [super unmarshalUsingStream:dataStream]; // unmarshal information in superclass first
    site = [dataStream readUnsignedShort];
    application = [dataStream readUnsignedShort];
    entity = [dataStream readUnsignedShort];
    forceId = [dataStream readUnsignedByte];
    numberOfVariableParameters = [dataStream readByte];
    entityKind = [dataStream readUnsignedByte];
    domain = [dataStream readUnsignedByte];
    country = [dataStream readUnsignedShort];
    category = [dataStream readUnsignedByte];
    subcategory = [dataStream readUnsignedByte];
    specific = [dataStream readUnsignedByte];
    extra = [dataStream readUnsignedByte];
    altEntityKind = [dataStream readUnsignedByte];
    altDomain = [dataStream readUnsignedByte];
    altCountry = [dataStream readUnsignedShort];
    altCategory = [dataStream readUnsignedByte];
    altSubcategory = [dataStream readUnsignedByte];
    altSpecific = [dataStream readUnsignedByte];
    altExtra = [dataStream readUnsignedByte];
    xVelocity = [dataStream readFloat];
    yVelocity = [dataStream readFloat];
    zVelocity = [dataStream readFloat];
    xLocation = [dataStream readDouble];
    yLocation = [dataStream readDouble];
    zLocation = [dataStream readDouble];
    psi = [dataStream readFloat];
    theta = [dataStream readFloat];
    phi = [dataStream readFloat];
    entityAppearance = [dataStream readInt];
    deadReckoningAlgorithm = [dataStream readUnsignedByte];

     for(int idx = 0; idx < 15; idx++)
     {
          otherParameters[idx] = [dataStream readByte];
     }

    xAcceleration = [dataStream readFloat];
    yAcceleration = [dataStream readFloat];
    zAcceleration = [dataStream readFloat];
    xAngularVelocity = [dataStream readFloat];
    yAngularVelocity = [dataStream readFloat];
    zAngularVelocity = [dataStream readFloat];

     for(int idx = 0; idx < 12; idx++)
     {
          marking[idx] = [dataStream readByte];
     }

    capabilities = [dataStream readInt];

     [variableParameters removeAllObjects];
     for(int idx = 0; idx < numberOfVariableParameters; idx++)
     {
        VariableParameter* x;
        [x unmarshalUsingStream:dataStream];
        [variableParameters addObject:x];
     }
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = [super getMarshalledSize];
   marshalSize = marshalSize + 2;  // site
   marshalSize = marshalSize + 2;  // application
   marshalSize = marshalSize + 2;  // entity
   marshalSize = marshalSize + 1;  // forceId
   marshalSize = marshalSize + 1;  // numberOfVariableParameters
   marshalSize = marshalSize + 1;  // entityKind
   marshalSize = marshalSize + 1;  // domain
   marshalSize = marshalSize + 2;  // country
   marshalSize = marshalSize + 1;  // category
   marshalSize = marshalSize + 1;  // subcategory
   marshalSize = marshalSize + 1;  // specific
   marshalSize = marshalSize + 1;  // extra
   marshalSize = marshalSize + 1;  // altEntityKind
   marshalSize = marshalSize + 1;  // altDomain
   marshalSize = marshalSize + 2;  // altCountry
   marshalSize = marshalSize + 1;  // altCategory
   marshalSize = marshalSize + 1;  // altSubcategory
   marshalSize = marshalSize + 1;  // altSpecific
   marshalSize = marshalSize + 1;  // altExtra
   marshalSize = marshalSize + 4;  // xVelocity
   marshalSize = marshalSize + 4;  // yVelocity
   marshalSize = marshalSize + 4;  // zVelocity
   marshalSize = marshalSize + 8;  // xLocation
   marshalSize = marshalSize + 8;  // yLocation
   marshalSize = marshalSize + 8;  // zLocation
   marshalSize = marshalSize + 4;  // psi
   marshalSize = marshalSize + 4;  // theta
   marshalSize = marshalSize + 4;  // phi
   marshalSize = marshalSize + 4;  // entityAppearance
   marshalSize = marshalSize + 1;  // deadReckoningAlgorithm
   marshalSize = marshalSize + 15 * 1;  // otherParameters
   marshalSize = marshalSize + 4;  // xAcceleration
   marshalSize = marshalSize + 4;  // yAcceleration
   marshalSize = marshalSize + 4;  // zAcceleration
   marshalSize = marshalSize + 4;  // xAngularVelocity
   marshalSize = marshalSize + 4;  // yAngularVelocity
   marshalSize = marshalSize + 4;  // zAngularVelocity
   marshalSize = marshalSize + 12 * 1;  // marking
   marshalSize = marshalSize + 4;  // capabilities

   for(int idx=0; idx < [variableParameters count]; idx++)
   {
        VariableParameter* listElement = [variableParameters objectAtIndex:idx];
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
