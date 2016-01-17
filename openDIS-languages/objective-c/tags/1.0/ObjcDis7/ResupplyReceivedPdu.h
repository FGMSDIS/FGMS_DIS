#import "EntityID.h"
#import "EntityID.h"
#import "SupplyQuantity.h"
#import <Foundation/Foundation.h>
#import "LogisticsFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 7.4.4. Receipt of supplies is communicated by issuing Resupply Received PDU. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface ResupplyReceivedPdu : LogisticsFamilyPdu
{
  /** Entity that is receiving service.  Shall be represented by Entity Identifier record (see 6.2.28) */
  EntityID *receivingEntityID; 

  /** Entity that is supplying.  Shall be represented by Entity Identifier record (see 6.2.28) */
  EntityID *supplyingEntityID; 

  /** How many supplies are taken by receiving entity */
  unsigned char numberOfSupplyTypes; 

  /** padding */
  short padding1; 

  /** padding */
  char padding2; 

  /** Type and amount of supplies for each specified supply type.  See 6.2.85 for supply quantity record. */
  NSMutableArray *supplies; 

}

@property(readwrite, retain) EntityID* receivingEntityID; 
@property(readwrite, retain) EntityID* supplyingEntityID; 
@property(readwrite, assign) unsigned char numberOfSupplyTypes; 
@property(readwrite, assign) short padding1; 
@property(readwrite, assign) char padding2; 
@property(readwrite, retain) NSMutableArray*supplies; 

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
