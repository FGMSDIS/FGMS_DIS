#import "EntityID.h"
#import "EntityType.h"
#import "Vector3Double.h"
#import "Orientation.h"
#import "Point.h"
#import "EntityType.h"
#import <Foundation/Foundation.h>
#import "MinefieldFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.10.1 Abstract superclass for PDUs relating to minefields. COMPLETE

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface MinefieldStatePdu : MinefieldFamilyPdu
{
  /** Minefield ID */
  EntityID *minefieldID; 

  /** Minefield sequence */
  unsigned short minefieldSequence; 

  /** force ID */
  unsigned char forceID; 

  /** Number of permieter points */
  unsigned char numberOfPerimeterPoints; 

  /** type of minefield */
  EntityType *minefieldType; 

  /** how many mine types */
  unsigned short numberOfMineTypes; 

  /** location of minefield in world coords */
  Vector3Double *minefieldLocation; 

  /** orientation of minefield */
  Orientation *minefieldOrientation; 

  /** appearance bitflags */
  unsigned short appearance; 

  /** protocolMode */
  unsigned short protocolMode; 

  /** perimeter points for the minefield */
  NSMutableArray *perimeterPoints; 

  /** Type of mines */
  NSMutableArray *mineType; 

}

@property(readwrite, retain) EntityID* minefieldID; 
@property(readwrite, assign) unsigned short minefieldSequence; 
@property(readwrite, assign) unsigned char forceID; 
@property(readwrite, assign) unsigned char numberOfPerimeterPoints; 
@property(readwrite, retain) EntityType* minefieldType; 
@property(readwrite, assign) unsigned short numberOfMineTypes; 
@property(readwrite, retain) Vector3Double* minefieldLocation; 
@property(readwrite, retain) Orientation* minefieldOrientation; 
@property(readwrite, assign) unsigned short appearance; 
@property(readwrite, assign) unsigned short protocolMode; 
@property(readwrite, retain) NSMutableArray*perimeterPoints; 
@property(readwrite, retain) NSMutableArray*mineType; 

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
