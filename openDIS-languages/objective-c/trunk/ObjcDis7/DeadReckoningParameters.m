#import "DeadReckoningParameters.h" 


@implementation DeadReckoningParameters

@synthesize deadReckoningAlgorithm;
@synthesize parametersPtr;
@synthesize parametersLength;
@synthesize entityLinearAcceleration;
@synthesize entityAngularVelocity;

-(id)init
{
  self = [super init];
  if(self)
  {
    deadReckoningAlgorithm = 0;
     // Initialize fixed length array
     int lengthparameters;
     for(lengthparameters = 0; lengthparameters < 15; lengthparameters++)
     {
         parameters[lengthparameters] = 0;
     }
     parametersPtr = &parameters[0];

    entityLinearAcceleration = [[Vector3Float alloc] init];
    entityAngularVelocity = [[Vector3Float alloc] init];
  } // end if(self)
  return self;
}


-(void)dealloc
{
  [entityLinearAcceleration release];
  [entityAngularVelocity release];
  [super dealloc];
}

-(void) marshalUsingStream:(DataOutput*) dataStream
{
    [dataStream writeUnsignedByte:deadReckoningAlgorithm];

     for(int idx = 0; idx < 15; idx++)
     {
    [dataStream writeUnsignedByte:parameters[idx]];
     }

    [entityLinearAcceleration marshalUsingStream:dataStream];
    [entityAngularVelocity marshalUsingStream:dataStream];
}

-(void) unmarshalUsingStream:(DataInput*)dataStream;
{
    deadReckoningAlgorithm = [dataStream readUnsignedByte];

     for(int idx = 0; idx < 15; idx++)
     {
          parameters[idx] = [dataStream readUnsignedByte];
     }

    [entityLinearAcceleration unmarshalUsingStream:dataStream];
    [entityAngularVelocity unmarshalUsingStream:dataStream];
}


-(int)getMarshalledSize
{
   int marshalSize = 0;

   marshalSize = marshalSize + 1;  // deadReckoningAlgorithm
   marshalSize = marshalSize + 15 * 1;  // parameters
   marshalSize = marshalSize + [entityLinearAcceleration getMarshalledSize];
   marshalSize = marshalSize + [entityAngularVelocity getMarshalledSize];
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
