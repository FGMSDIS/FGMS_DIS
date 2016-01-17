#import "EntityID.h"
#import <Foundation/Foundation.h>
#import "DataInput.h"
#import "DataOutput.h"


// Association or disassociation of two entities.  Section 6.2.93.4

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface  EntityAssociation: NSObject
{
  /** the identification of the Variable Parameter record. Enumeration from EBV */
  unsigned char recordType; 

  /** Indicates if this VP has changed since last issuance */
  unsigned char changeIndicator; 

  /** Indicates association status between two entities; 8 bit enum */
  unsigned char associationStatus; 

  /** Type of association; 8 bit enum */
  unsigned char associationType; 

  /** Object ID of entity associated with this entity */
  EntityID *entityID; 

  /** Station location on one's own entity. EBV doc. */
  unsigned short owsSttionLocation; 

  /** Type of physical connection. EBV doc */
  unsigned short physicalConnectionType; 

  /** Type of member the entity is within th egroup */
  unsigned char groupMemberType; 

  /** Group if any to which the entity belongs */
  unsigned short groupNumber; 

}

@property(readwrite, assign) unsigned char recordType; 
@property(readwrite, assign) unsigned char changeIndicator; 
@property(readwrite, assign) unsigned char associationStatus; 
@property(readwrite, assign) unsigned char associationType; 
@property(readwrite, retain) EntityID* entityID; 
@property(readwrite, assign) unsigned short owsSttionLocation; 
@property(readwrite, assign) unsigned short physicalConnectionType; 
@property(readwrite, assign) unsigned char groupMemberType; 
@property(readwrite, assign) unsigned short groupNumber; 

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
