#import "EntityID.h"
#import "EntityType.h"
#import "Orientation.h"
#import "GridAxisRecord.h"
#import <Foundation/Foundation.h>
#import "SyntheticEnvironmentFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.11.2: Information about globat, spatially varying enviornmental effects. This requires manual cleanup; the grid axis        records are variable sized. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface GriddedDataPdu : SyntheticEnvironmentFamilyPdu
{
  /** environmental simulation application ID */
  EntityID *environmentalSimulationApplicationID; 

  /** unique identifier for each piece of enviornmental data */
  unsigned short fieldNumber; 

  /** sequence number for the total set of PDUS used to transmit the data */
  unsigned short pduNumber; 

  /** Total number of PDUS used to transmit the data */
  unsigned short pduTotal; 

  /** coordinate system of the grid */
  unsigned short coordinateSystem; 

  /** number of grid axes for the environmental data */
  unsigned char numberOfGridAxes; 

  /** are domain grid axes identidal to those of the priveious domain update? */
  unsigned char constantGrid; 

  /** type of environment */
  EntityType *environmentType; 

  /** orientation of the data grid */
  Orientation *orientation; 

  /** valid time of the enviormental data sample, 64 bit unsigned int */
  long sampleTime; 

  /** total number of all data values for all pdus for an environmental sample */
  unsigned int totalValues; 

  /** total number of data values at each grid point. */
  unsigned char vectorDimension; 

  /** padding */
  unsigned short padding1; 

  /** padding */
  unsigned char padding2; 

  /** Grid data ^^^This is wrong */
  NSMutableArray *gridDataList; 

}

@property(readwrite, retain) EntityID* environmentalSimulationApplicationID; 
@property(readwrite, assign) unsigned short fieldNumber; 
@property(readwrite, assign) unsigned short pduNumber; 
@property(readwrite, assign) unsigned short pduTotal; 
@property(readwrite, assign) unsigned short coordinateSystem; 
@property(readwrite, assign) unsigned char numberOfGridAxes; 
@property(readwrite, assign) unsigned char constantGrid; 
@property(readwrite, retain) EntityType* environmentType; 
@property(readwrite, retain) Orientation* orientation; 
@property(readwrite, assign) long sampleTime; 
@property(readwrite, assign) unsigned int totalValues; 
@property(readwrite, assign) unsigned char vectorDimension; 
@property(readwrite, assign) unsigned short padding1; 
@property(readwrite, assign) unsigned char padding2; 
@property(readwrite, retain) NSMutableArray*gridDataList; 

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
