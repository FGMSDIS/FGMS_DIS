#import "EntityID.h"
#import "EntityID.h"
#import "EntityType.h"
#import "TwoByteChunk.h"
#import "Vector3Float.h"
#import <Foundation/Foundation.h>
#import "MinefieldFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.10.3 Information about individual mines within a minefield. This is very, very wrong. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface MinefieldDataPdu : MinefieldFamilyPdu
{
  /** Minefield ID */
  EntityID *minefieldID; 

  /** ID of entity making request */
  EntityID *requestingEntityID; 

  /** Minefield sequence number */
  unsigned short minefieldSequenceNumbeer; 

  /** request ID */
  unsigned char requestID; 

  /** pdu sequence number */
  unsigned char pduSequenceNumber; 

  /** number of pdus in response */
  unsigned char numberOfPdus; 

  /** how many mines are in this PDU */
  unsigned char numberOfMinesInThisPdu; 

  /** how many sensor type are in this PDU */
  unsigned char numberOfSensorTypes; 

  /** padding */
  unsigned char pad2; 

  /** 32 boolean fields */
  unsigned int dataFilter; 

  /** Mine type */
  EntityType *mineType; 

  /** Sensor types, each 16 bits long */
  NSMutableArray *sensorTypes; 

  /** Padding to get things 32-bit aligned. ^^^this is wrong--dyanmically sized padding needed */
  unsigned char pad3; 

  /** Mine locations */
  NSMutableArray *mineLocation; 

}

@property(readwrite, retain) EntityID* minefieldID; 
@property(readwrite, retain) EntityID* requestingEntityID; 
@property(readwrite, assign) unsigned short minefieldSequenceNumbeer; 
@property(readwrite, assign) unsigned char requestID; 
@property(readwrite, assign) unsigned char pduSequenceNumber; 
@property(readwrite, assign) unsigned char numberOfPdus; 
@property(readwrite, assign) unsigned char numberOfMinesInThisPdu; 
@property(readwrite, assign) unsigned char numberOfSensorTypes; 
@property(readwrite, assign) unsigned char pad2; 
@property(readwrite, assign) unsigned int dataFilter; 
@property(readwrite, retain) EntityType* mineType; 
@property(readwrite, retain) NSMutableArray*sensorTypes; 
@property(readwrite, assign) unsigned char pad3; 
@property(readwrite, retain) NSMutableArray*mineLocation; 

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
