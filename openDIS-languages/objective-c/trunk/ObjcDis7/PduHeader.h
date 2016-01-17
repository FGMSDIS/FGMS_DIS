#import <Foundation/Foundation.h>
#import "DataInput.h"
#import "DataOutput.h"


// Not used. The PDU Header Record is directly incoroporated into the PDU class. Here for completness only. Section 6.2.66

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface  PduHeader: NSObject
{
  /** The version of the protocol. 5=DIS-1995, 6=DIS-1998, 7=DIS-2009. */
  unsigned char protocolVersion; 

  /** Exercise ID */
  unsigned char exerciseID; 

  /** Type of pdu, unique for each PDU class */
  unsigned char pduType; 

  /** value that refers to the protocol family, eg SimulationManagement, etc */
  unsigned char protocolFamily; 

  /** Timestamp value */
  unsigned int timestamp; 

  /** Length, in bytes, of the PDU. Changed name from length to avoid use of Hibernate QL reserved word. */
  unsigned char pduLength; 

  /** PDU Status Record. Described in 6.2.67. This field is not present in earlier DIS versions  */
  unsigned short pduStatus; 

  /** zero filled array of padding */
  unsigned char padding; 

}

@property(readwrite, assign) unsigned char protocolVersion; 
@property(readwrite, assign) unsigned char exerciseID; 
@property(readwrite, assign) unsigned char pduType; 
@property(readwrite, assign) unsigned char protocolFamily; 
@property(readwrite, assign) unsigned int timestamp; 
@property(readwrite, assign) unsigned char pduLength; 
@property(readwrite, assign) unsigned short pduStatus; 
@property(readwrite, assign) unsigned char padding; 

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
