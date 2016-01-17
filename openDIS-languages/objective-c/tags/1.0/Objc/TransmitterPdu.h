#import "RadioEntityType.h"
#import "Vector3Double.h"
#import "Vector3Float.h"
#import "ModulationType.h"
#import "Vector3Float.h"
#import "Vector3Float.h"
#import <Foundation/Foundation.h>
#import "RadioCommunicationsFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.8.1. Detailed information about a radio transmitter. This PDU requires manually         written code to complete, since the modulation parameters are of variable length. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface TransmitterPdu : RadioCommunicationsFamilyPdu
{
  /** linear accelleration of entity */
  RadioEntityType *radioEntityType; 

  /** transmit state */
  unsigned char transmitState; 

  /** input source */
  unsigned char inputSource; 

  /** padding */
  unsigned short padding1; 

  /** Location of antenna */
  Vector3Double *antennaLocation; 

  /** relative location of antenna */
  Vector3Float *relativeAntennaLocation; 

  /** antenna pattern type */
  unsigned short antennaPatternType; 

  /** atenna pattern length */
  unsigned short antennaPatternCount; 

  /** frequency */
  long frequency; 

  /** transmit frequency Bandwidth */
  float transmitFrequencyBandwidth; 

  /** transmission power */
  float power; 

  /** modulation */
  ModulationType *modulationType; 

  /** crypto system enumeration */
  unsigned short cryptoSystem; 

  /** crypto system key identifer */
  unsigned short cryptoKeyId; 

  /** how many modulation parameters we have */
  unsigned char modulationParameterCount; 

  /** padding2 */
  unsigned short padding2; 

  /** padding3 */
  unsigned char padding3; 

  /** variable length list of modulation parameters */
  NSMutableArray *modulationParametersList; 

  /** variable length list of antenna pattern records */
  NSMutableArray *antennaPatternList; 

}

@property(readwrite, retain) RadioEntityType* radioEntityType; 
@property(readwrite, assign) unsigned char transmitState; 
@property(readwrite, assign) unsigned char inputSource; 
@property(readwrite, assign) unsigned short padding1; 
@property(readwrite, retain) Vector3Double* antennaLocation; 
@property(readwrite, retain) Vector3Float* relativeAntennaLocation; 
@property(readwrite, assign) unsigned short antennaPatternType; 
@property(readwrite, assign) unsigned short antennaPatternCount; 
@property(readwrite, assign) long frequency; 
@property(readwrite, assign) float transmitFrequencyBandwidth; 
@property(readwrite, assign) float power; 
@property(readwrite, retain) ModulationType* modulationType; 
@property(readwrite, assign) unsigned short cryptoSystem; 
@property(readwrite, assign) unsigned short cryptoKeyId; 
@property(readwrite, assign) unsigned char modulationParameterCount; 
@property(readwrite, assign) unsigned short padding2; 
@property(readwrite, assign) unsigned char padding3; 
@property(readwrite, retain) NSMutableArray*modulationParametersList; 
@property(readwrite, retain) NSMutableArray*antennaPatternList; 

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
