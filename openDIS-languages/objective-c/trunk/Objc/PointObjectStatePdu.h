#import "EntityID.h"
#import "EntityID.h"
#import "ObjectType.h"
#import "Vector3Double.h"
#import "Orientation.h"
#import "SimulationAddress.h"
#import "SimulationAddress.h"
#import <Foundation/Foundation.h>
#import "SyntheticEnvironmentFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.11.3: Inormation abut the addition or modification of a synthecic enviroment object that is anchored      to the terrain with a single point. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface PointObjectStatePdu : SyntheticEnvironmentFamilyPdu
{
  /** Object in synthetic environment */
  EntityID *objectID; 

  /** Object with which this point object is associated */
  EntityID *referencedObjectID; 

  /** unique update number of each state transition of an object */
  unsigned short updateNumber; 

  /** force ID */
  unsigned char forceID; 

  /** modifications */
  unsigned char modifications; 

  /** Object type */
  ObjectType *objectType; 

  /** Object location */
  Vector3Double *objectLocation; 

  /** Object orientation */
  Orientation *objectOrientation; 

  /** Object apperance */
  double objectAppearance; 

  /** requesterID */
  SimulationAddress *requesterID; 

  /** receiver ID */
  SimulationAddress *receivingID; 

  /** padding */
  unsigned int pad2; 

}

@property(readwrite, retain) EntityID* objectID; 
@property(readwrite, retain) EntityID* referencedObjectID; 
@property(readwrite, assign) unsigned short updateNumber; 
@property(readwrite, assign) unsigned char forceID; 
@property(readwrite, assign) unsigned char modifications; 
@property(readwrite, retain) ObjectType* objectType; 
@property(readwrite, retain) Vector3Double* objectLocation; 
@property(readwrite, retain) Orientation* objectOrientation; 
@property(readwrite, assign) double objectAppearance; 
@property(readwrite, retain) SimulationAddress* requesterID; 
@property(readwrite, retain) SimulationAddress* receivingID; 
@property(readwrite, assign) unsigned int pad2; 

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
