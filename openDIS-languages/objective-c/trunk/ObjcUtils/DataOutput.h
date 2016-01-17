//
//  DataOutput.h
//  StreamMac
//
//  Created by Donald McGregor on 8/4/09.
//  Copyright 2009 NPS. All rights reserved.
//

//#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
//#import <CoreServices/CoreServices.h>


#define BUFFER_SIZE 2048

@interface DataOutput : NSObject 
{
    NSOutputStream    *outputStream;
}

-(id)init;
-(void)writeByte:(char)data;
-(void)writeUnsignedByte:(unsigned char)data;

-(void)writeShort:(SInt16)data;
-(void)writeUnsignedShort:(UInt16)data;


-(void)writeInt:(SInt32)data;
-(void)writeUnsignedInt:(UInt32)data;

-(void)writeLong:(SInt64)data;
-(void)writeUnsignedLong:(UInt64)data;

-(void)writeFloat:(float)data;
-(void)writeDouble:(double)data;

-(NSData*)data;

+(void)test;



@end
