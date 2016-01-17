//
//  DataOutput.m
//  StreamMac
//
//  Created by Donald McGregor on 8/4/09.
//  Copyright 2009 NPS. All rights reserved.
//

#import "DataOutput.h"
#import "DataInput.h"


@implementation DataOutput

-(id)init
{
    [super init];
    outputStream = [NSOutputStream outputStreamToMemory];
    [outputStream open];
        
    return self;
}

-(void)writeByte:(char)data
{
    [outputStream write:(const UInt8*)&data maxLength:1];
}

-(void)writeUnsignedByte:(unsigned char)data
{
    [outputStream write:(const UInt8*)&data maxLength:1];
}

-(void)writeShort:(SInt16)data
{
    SInt16 swapped = NSSwapHostShortToBig(data);
    [outputStream write:(const UInt8*)&swapped maxLength:2];
}

-(void)writeUnsignedShort:(UInt16)data
{
    UInt16 swapped = NSSwapHostShortToBig(data);
    [outputStream write:(const UInt8*)&swapped maxLength:2];
}

-(void)writeInt:(SInt32)data
{
    SInt32 swapped = NSSwapHostIntToBig(data);
    [outputStream write:(const UInt8*)&swapped maxLength:4];
}

-(void)writeUnsignedInt:(UInt32)data
{
    UInt32 swapped = NSSwapHostIntToBig(data);
    [outputStream write:(const UInt8*)&swapped maxLength:4];
}

-(void)writeLong:(SInt64)data
{
    SInt64 swapped = NSSwapHostLongToBig(data);
    [outputStream write:(const UInt8*)&swapped maxLength:8];
}

-(void)writeUnsignedLong:(UInt64)data
{
    UInt64 swapped = NSSwapHostLongToBig(data);
    [outputStream write:(const UInt8*)&swapped maxLength:8];
}


-(void)writeFloat:(float)data
{
    NSSwappedFloat swappedFloat = NSSwapHostFloatToBig(data);
    [outputStream write:(const UInt8*)&swappedFloat maxLength:4];
}
-(void)writeDouble:(double)data
{
    NSSwappedDouble swappedDouble = NSSwapHostDoubleToBig(data);
    [outputStream write:(const UInt8*)&swappedDouble maxLength:8];
}

+(void)test
{
    DataOutput *out = [[DataOutput alloc] init];
    NSLog(@"allocated DataOut");
    
    [out writeUnsignedByte:0];
    [out writeUnsignedByte:255];
    [out writeByte:-1];
    
    [out writeShort:0xff];
    [out writeUnsignedShort:0xffff];
    [out writeShort:-1];
    
    [out writeInt:17];
    [out writeUnsignedInt:0xffffffff];
    [out writeInt:-1];
    
    [out writeFloat:17.25];
    [out writeDouble:99.99];
    
    NSData *d = [out data];
    
    DataInput *in = [[DataInput alloc] initWithData:d];
    NSLog(@"data: %i", [in readUnsignedByte]);
    NSLog(@"data: %i", [in readUnsignedByte]);
    NSLog(@"data: %i", [in readByte]);
    
    NSLog(@"data: %i", [in readShort]);
    NSLog(@"data: %i", [in readUnsignedShort]);
    NSLog(@"data: %i", [in readShort]);
    
    NSLog(@"data: %i", [in readInt]);
    NSLog(@"data: %ui", [in readUnsignedInt]);
    NSLog(@"data: %i", [in readInt]);
    
    NSLog(@"data: %g", [in readFloat]);
    NSLog(@"data: %g", [in readDouble]);
    
}

-(NSData*)data
{
    id d = [outputStream propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
    if([d isKindOfClass:[NSData class]])
    {
        NSData *dat = (NSData*)d;
        return dat;
    }
    return nil;
}

-(int)size
{
    NSData *d = [outputStream propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
    return [d length];

}
@end
