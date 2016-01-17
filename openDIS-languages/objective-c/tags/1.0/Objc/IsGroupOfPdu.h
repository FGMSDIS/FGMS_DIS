#import "EntityID.h"
#import "VariableDatum.h"
#import <Foundation/Foundation.h>
#import "EntityManagementFamilyPdu.h"
#import "DataInput.h"
#import "DataOutput.h"


// Section 5.3.9.2 Information about a particular group of entities grouped together for the purposes of netowrk bandwidth         reduction or aggregation. Needs manual cleanup. The GED size requires a database lookup. UNFINISHED

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG

@interface IsGroupOfPdu : EntityManagementFamilyPdu
{
  /** ID of aggregated entities */
  EntityID *groupEntityID; 

  /** type of entities constituting the group */
  unsigned char groupedEntityCategory; 

  /** Number of individual entities constituting the group */
  unsigned char numberOfGroupedEntities; 

  /** padding */
  unsigned int pad2; 

  /** latitude */
  double latitude; 

  /** longitude */
  double longitude; 

  /** GED records about each individual entity in the group. ^^^this is wrong--need a database lookup to find the actual size of the list elements */
  NSMutableArray *groupedEntityDescriptions; 

}

@property(readwrite, retain) EntityID* groupEntityID; 
@property(readwrite, assign) unsigned char groupedEntityCategory; 
@property(readwrite, assign) unsigned char numberOfGroupedEntities; 
@property(readwrite, assign) unsigned int pad2; 
@property(readwrite, assign) double latitude; 
@property(readwrite, assign) double longitude; 
@property(readwrite, retain) NSMutableArray*groupedEntityDescriptions; 

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
