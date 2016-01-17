#import "EntityAssociation.h" 


@implementation EntityAssociation

@synthesize recordType;
@synthesize changeIndicator;
@synthesize associationStatus;
@synthesize associationType;
@synthesize entityID;
@synthesize owsSttionLocation;
@synthesize physicalConnectionType;
@synthesize groupMemberType;
@synthesize groupNumber;

-(id)init
{
  self = [super init];
  if(self)
  {
    recordType = 2;
    changeIndicator = 0;
    associationStatus = 0;
    associationType = 0;
    entityID = [[EntityID alloc] init];
    owsSttionLocation = 0;
    physicalConnectionType = 0;
    groupMemberType = 0;
    groupNumber = 0;
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [entityID release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedByte:recordType];
    [dataStream writeUnsignedByte:changeIndicator];
    [dataStream writeUnsignedByte:associationStatus];
    [dataStream writeUnsignedByte:associationType];
    [entityID marshalUsingStream:dataStream];
    [dataStream writeUnsignedShort:owsSttionLocation];
    [dataStream writeUnsignedShort:physicalConnectionType];
    [dataStream writeUnsignedByte:groupMemberType];
    [dataStream writeUnsignedShort:groupNumber];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    recordType = [dataStream readUnsignedByte];
    changeIndicator = [dataStream readUnsignedByte];
    associationStatus = [dataStream readUnsignedByte];
    associationType = [dataStream readUnsignedByte];
    [entityID unmarshalUsingStream:dataStream];
    owsSttionLocation = [dataStream readUnsignedShort];
    physicalConnectionType = [dataStream readUnsignedShort];
    groupMemberType = [dataStream readUnsignedByte];
    groupNumber = [dataStream readUnsignedShort];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 1;  // recordType
   marshalSize = marshalSize + 1;  // changeIndicator
   marshalSize = marshalSize + 1;  // associationStatus
   marshalSize = marshalSize + 1;  // associationType
   marshalSize = marshalSize + [entityID getMarshalledSize];
   marshalSize = marshalSize + 2;  // owsSttionLocation
   marshalSize = marshalSize + 2;  // physicalConnectionType
   marshalSize = marshalSize + 1;  // groupMemberType
   marshalSize = marshalSize + 2;  // groupNumber
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
