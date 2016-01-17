#import "Vector3Float.h"
#import "EventIdentifier.h"
#import <Foundation/Foundation.h>
#import "DataInput.h"
#import "DataOutput.h"


// Damage sustained by an entity due to directed energy. Location of the damage based on a relative x,y,z location from the center of the entity. Section 6.2.17.2

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface  DirectedEnergyDamage: NSObject
{
  /** DE Record Type. */
  unsigned int recordType; 

  /** DE Record Length (bytes). */
  unsigned short recordLength; 

  /** padding. */
  unsigned short padding; 

  /** location of damage, relative to center of entity */
  Vector3Float *damageLocation; 

  /** Size of damaged area, in meters. */
  float damageDiameter; 

  /** average temp of the damaged area, in degrees celsius. If firing entitty does not model this, use a value of -273.15 */
  float temperature; 

  /** enumeration */
  unsigned char componentIdentification; 

  /** enumeration */
  unsigned char componentDamageStatus; 

  /** enumeration */
  unsigned char componentVisualDamageStatus; 

  /** enumeration */
  unsigned char componentVisualSmokeColor; 

  /** For any component damage resulting this field shall be set to the fire event ID from that PDU. */
  EventIdentifier *fireEventID; 

  /** padding */
  unsigned short padding2; 

}

@property(readwrite, assign) unsigned int recordType; 
@property(readwrite, assign) unsigned short recordLength; 
@property(readwrite, assign) unsigned short padding; 
@property(readwrite, retain) Vector3Float* damageLocation; 
@property(readwrite, assign) float damageDiameter; 
@property(readwrite, assign) float temperature; 
@property(readwrite, assign) unsigned char componentIdentification; 
@property(readwrite, assign) unsigned char componentDamageStatus; 
@property(readwrite, assign) unsigned char componentVisualDamageStatus; 
@property(readwrite, assign) unsigned char componentVisualSmokeColor; 
@property(readwrite, retain) EventIdentifier* fireEventID; 
@property(readwrite, assign) unsigned short padding2; 

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
