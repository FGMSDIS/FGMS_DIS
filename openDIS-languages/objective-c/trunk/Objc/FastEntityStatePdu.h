#import "ArticulationParameter.h"
#import <Foundation/Foundation.h>
#import "EntityInformationFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.3.1. Represents the postion and state of one entity in the world. This is identical in function to entity state pdu, but generates less garbage to collect in the Java world. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface FastEntityStatePdu : EntityInformationFamilyPdu
{
  /** The site ID */
  unsigned short site; 

  /** The application ID */
  unsigned short application; 

  /** the entity ID */
  unsigned short entity; 

  /** what force this entity is affiliated with, eg red, blue, neutral, etc */
  unsigned char forceId; 

  /** How many articulation parameters are in the variable length list */
  char numberOfArticulationParameters; 

  /** Kind of entity */
  unsigned char entityKind; 

  /** Domain of entity (air, surface, subsurface, space, etc) */
  unsigned char domain; 

  /** country to which the design of the entity is attributed */
  unsigned short country; 

  /** category of entity */
  unsigned char category; 

  /** subcategory of entity */
  unsigned char subcategory; 

  /** specific info based on subcategory field */
  unsigned char specific; 

  unsigned char extra; 

  /** Kind of entity */
  unsigned char altEntityKind; 

  /** Domain of entity (air, surface, subsurface, space, etc) */
  unsigned char altDomain; 

  /** country to which the design of the entity is attributed */
  unsigned short altCountry; 

  /** category of entity */
  unsigned char altCategory; 

  /** subcategory of entity */
  unsigned char altSubcategory; 

  /** specific info based on subcategory field */
  unsigned char altSpecific; 

  unsigned char altExtra; 

  /** X velo */
  float xVelocity; 

  /** y Value */
  float yVelocity; 

  /** Z value */
  float zVelocity; 

  /** X value */
  double xLocation; 

  /** y Value */
  double yLocation; 

  /** Z value */
  double zLocation; 

  float psi; 

  float theta; 

  float phi; 

  /** a series of bit flags that are used to help draw the entity, such as smoking, on fire, etc. */
  int entityAppearance; 

  /** enumeration of what dead reckoning algorighm to use */
  unsigned char deadReckoningAlgorithm; 

  /** other parameters to use in the dead reckoning algorithm */
  char otherParameters[15]; 
  // Length of the above array
  int otherParametersLength;
  // Ptr to the array (fixes a syntax types problem with properties)
   char * otherParametersPtr; 

  /** X value */
  float xAcceleration; 

  /** y Value */
  float yAcceleration; 

  /** Z value */
  float zAcceleration; 

  /** X value */
  float xAngularVelocity; 

  /** y Value */
  float yAngularVelocity; 

  /** Z value */
  float zAngularVelocity; 

  /** characters that can be used for debugging, or to draw unique strings on the side of entities in the world */
  char marking[12]; 
  // Length of the above array
  int markingLength;
  // Ptr to the array (fixes a syntax types problem with properties)
   char * markingPtr; 

  /** a series of bit flags */
  int capabilities; 

  /** variable length list of articulation parameters */
  NSMutableArray *articulationParameters; 

}

@property(readwrite, assign) unsigned short site; 
@property(readwrite, assign) unsigned short application; 
@property(readwrite, assign) unsigned short entity; 
@property(readwrite, assign) unsigned char forceId; 
@property(readwrite, assign) char numberOfArticulationParameters; 
@property(readwrite, assign) unsigned char entityKind; 
@property(readwrite, assign) unsigned char domain; 
@property(readwrite, assign) unsigned short country; 
@property(readwrite, assign) unsigned char category; 
@property(readwrite, assign) unsigned char subcategory; 
@property(readwrite, assign) unsigned char specific; 
@property(readwrite, assign) unsigned char extra; 
@property(readwrite, assign) unsigned char altEntityKind; 
@property(readwrite, assign) unsigned char altDomain; 
@property(readwrite, assign) unsigned short altCountry; 
@property(readwrite, assign) unsigned char altCategory; 
@property(readwrite, assign) unsigned char altSubcategory; 
@property(readwrite, assign) unsigned char altSpecific; 
@property(readwrite, assign) unsigned char altExtra; 
@property(readwrite, assign) float xVelocity; 
@property(readwrite, assign) float yVelocity; 
@property(readwrite, assign) float zVelocity; 
@property(readwrite, assign) double xLocation; 
@property(readwrite, assign) double yLocation; 
@property(readwrite, assign) double zLocation; 
@property(readwrite, assign) float psi; 
@property(readwrite, assign) float theta; 
@property(readwrite, assign) float phi; 
@property(readwrite, assign) int entityAppearance; 
@property(readwrite, assign) unsigned char deadReckoningAlgorithm; 
@property(readwrite) char* otherParametersPtr;
@property(readonly) int otherParametersLength;
@property(readwrite, assign) float xAcceleration; 
@property(readwrite, assign) float yAcceleration; 
@property(readwrite, assign) float zAcceleration; 
@property(readwrite, assign) float xAngularVelocity; 
@property(readwrite, assign) float yAngularVelocity; 
@property(readwrite, assign) float zAngularVelocity; 
@property(readwrite) char* markingPtr;
@property(readonly) int markingLength;
@property(readwrite, assign) int capabilities; 
@property(readwrite, retain) NSMutableArray*articulationParameters; 

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
