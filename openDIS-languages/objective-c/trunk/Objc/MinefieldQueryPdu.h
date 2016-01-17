#import "EntityID.h"
#import "EntityID.h"
#import "EntityType.h"
#import "Point.h"
#import "TwoByteChunk.h"
#import <Foundation/Foundation.h>
#import "MinefieldFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.10.2 Query a minefield for information about individual mines. Requires manual clean up to get the padding right. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface MinefieldQueryPdu : MinefieldFamilyPdu
{
  /** Minefield ID */
  EntityID *minefieldID; 

  /** EID of entity making the request */
  EntityID *requestingEntityID; 

  /** request ID */
  unsigned char requestID; 

  /** Number of perimeter points for the minefield */
  unsigned char numberOfPerimeterPoints; 

  /** Padding */
  unsigned char pad2; 

  /** Number of sensor types */
  unsigned char numberOfSensorTypes; 

  /** data filter, 32 boolean fields */
  unsigned int dataFilter; 

  /** Entity type of mine being requested */
  EntityType *requestedMineType; 

  /** perimeter points of request */
  NSMutableArray *requestedPerimeterPoints; 

  /** Sensor types, each 16 bits long */
  NSMutableArray *sensorTypes; 

}

@property(readwrite, retain) EntityID* minefieldID; 
@property(readwrite, retain) EntityID* requestingEntityID; 
@property(readwrite, assign) unsigned char requestID; 
@property(readwrite, assign) unsigned char numberOfPerimeterPoints; 
@property(readwrite, assign) unsigned char pad2; 
@property(readwrite, assign) unsigned char numberOfSensorTypes; 
@property(readwrite, assign) unsigned int dataFilter; 
@property(readwrite, retain) EntityType* requestedMineType; 
@property(readwrite, retain) NSMutableArray*requestedPerimeterPoints; 
@property(readwrite, retain) NSMutableArray*sensorTypes; 

-(id)init; // Initializer
-(void)dealloc;
-(void)marshalUsingStream:(DataOutput*) dataStream;
-(void)unmarshalUsingStream:(DataInput*) dataStream;

-(int)getMarshalledSize;

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
