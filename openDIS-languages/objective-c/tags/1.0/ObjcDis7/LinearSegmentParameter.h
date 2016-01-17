#import "Vector3Double.h"
#import "EulerAngles.h"
#import <Foundation/Foundation.h>
#import "DataInput.h"
#import "DataOutput.h"


// The specification of an individual segment of a linear segment synthetic environment object in a Linear Object State PDU Section 6.2.53

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface  LinearSegmentParameter: NSObject
{
  /** the individual segment of the linear segment  */
  unsigned char segmentNumber; 

  /**  whether a modification has been made to the point object’s location or orientation */
  unsigned char segmentModification; 

  /** general dynamic appearance attributes of the segment. This record shall be defined as a 16-bit record of enumerations. The values defined for this record are included in Section 12 of SISO-REF-010. */
  unsigned short generalSegmentAppearance; 

  /** This field shall specify specific dynamic appearance attributes of the segment. This record shall be defined as a 32-bit record of enumerations. */
  unsigned short specificSegmentAppearance; 

  /** This field shall specify the location of the linear segment in the simulated world and shall be represented by a World Coordinates record  */
  Vector3Double *segmentLocation; 

  /** orientation of the linear segment about the segment location and shall be represented by a Euler Angles record  */
  EulerAngles *segmentOrientation; 

  /** length of the linear segment, in meters, extending in the positive X direction */
  unsigned short segmentLength; 

  /** The total width of the linear segment, in meters, shall be specified by a 16-bit unsigned integer. One-half of the width shall extend in the positive Y direction, and one-half of the width shall extend in the negative Y direction. */
  unsigned short segmentWidth; 

  /** The height of the linear segment, in meters, above ground shall be specified by a 16-bit unsigned integer. */
  unsigned short segmentHeight; 

  /** The depth of the linear segment, in meters, below ground level  */
  unsigned short segmentDepth; 

}

@property(readwrite, assign) unsigned char segmentNumber; 
@property(readwrite, assign) unsigned char segmentModification; 
@property(readwrite, assign) unsigned short generalSegmentAppearance; 
@property(readwrite, assign) unsigned short specificSegmentAppearance; 
@property(readwrite, retain) Vector3Double* segmentLocation; 
@property(readwrite, retain) EulerAngles* segmentOrientation; 
@property(readwrite, assign) unsigned short segmentLength; 
@property(readwrite, assign) unsigned short segmentWidth; 
@property(readwrite, assign) unsigned short segmentHeight; 
@property(readwrite, assign) unsigned short segmentDepth; 

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
