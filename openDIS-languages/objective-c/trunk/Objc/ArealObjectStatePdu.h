#import "EntityID.h"
#import "EntityID.h"
#import "EntityType.h"
#import "SixByteChunk.h"
#import "SimulationAddress.h"
#import "SimulationAddress.h"
#import "Vector3Double.h"
#import <Foundation/Foundation.h>
#import "SyntheticEnvironmentFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.11.5: Information about the addition/modification of an oobject that is geometrically      achored to the terrain with a set of three or more points that come to a closure. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface ArealObjectStatePdu : SyntheticEnvironmentFamilyPdu
{
  /** Object in synthetic environment */
  EntityID *objectID; 

  /** Object with which this point object is associated */
  EntityID *referencedObjectID; 

  /** unique update number of each state transition of an object */
  unsigned short updateNumber; 

  /** force ID */
  unsigned char forceID; 

  /** modifications enumeration */
  unsigned char modifications; 

  /** Object type */
  EntityType *objectType; 

  /** Object appearance */
  SixByteChunk *objectAppearance; 

  /** Number of points */
  unsigned short numberOfPoints; 

  /** requesterID */
  SimulationAddress *requesterID; 

  /** receiver ID */
  SimulationAddress *receivingID; 

  /** location of object */
  NSMutableArray *objectLocation; 

}

@property(readwrite, retain) EntityID* objectID; 
@property(readwrite, retain) EntityID* referencedObjectID; 
@property(readwrite, assign) unsigned short updateNumber; 
@property(readwrite, assign) unsigned char forceID; 
@property(readwrite, assign) unsigned char modifications; 
@property(readwrite, retain) EntityType* objectType; 
@property(readwrite, retain) SixByteChunk* objectAppearance; 
@property(readwrite, assign) unsigned short numberOfPoints; 
@property(readwrite, retain) SimulationAddress* requesterID; 
@property(readwrite, retain) SimulationAddress* receivingID; 
@property(readwrite, retain) NSMutableArray*objectLocation; 

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
