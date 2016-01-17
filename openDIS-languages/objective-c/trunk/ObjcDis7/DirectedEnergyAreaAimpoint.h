#import "BeamAntennaPattern.h"
#import "DirectedEnergyTargetEnergyDeposition.h"
#import <Foundation/Foundation.h>
#import "DataInput.h"
#import "DataOutput.h"


// DE Precision Aimpoint Record. NOT COMPLETE. Section 6.2.21.2

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface  DirectedEnergyAreaAimpoint: NSObject
{
  /** Type of Record */
  unsigned int recordType; 

  /** Length of Record */
  unsigned short recordLength; 

  /** Padding */
  unsigned short padding; 

  /** Number of beam antenna pattern records */
  unsigned short beamAntennaPatternRecordCount; 

  /** Number of DE target energy depositon records */
  unsigned short directedEnergyTargetEnergyDepositionRecordCount; 

  /** list of beam antenna records. See 6.2.9.2 */
  NSMutableArray *beamAntennaParameterList; 

  /** list of DE target deposition records. See 6.2.21.4 */
  NSMutableArray *directedEnergyTargetEnergyDepositionRecordList; 

}

@property(readwrite, assign) unsigned int recordType; 
@property(readwrite, assign) unsigned short recordLength; 
@property(readwrite, assign) unsigned short padding; 
@property(readwrite, assign) unsigned short beamAntennaPatternRecordCount; 
@property(readwrite, assign) unsigned short directedEnergyTargetEnergyDepositionRecordCount; 
@property(readwrite, retain) NSMutableArray*beamAntennaParameterList; 
@property(readwrite, retain) NSMutableArray*directedEnergyTargetEnergyDepositionRecordList; 

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
