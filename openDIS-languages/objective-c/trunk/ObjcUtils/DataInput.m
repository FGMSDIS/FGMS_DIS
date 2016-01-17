#import "DataInput.h"

#import "DataOutput.h"


@implementation DataInput

-(id)initWithData:(NSData*) data
{
    self = [super init];
    if(self)
    {
        readStream = [[NSInputStream alloc] initWithData:data];
        [readStream open];
    }
    
    return self;
}

-(char)readByte
{
    char data = 0;
    [readStream read:(UInt8*)&data maxLength:1];
    return data;
}

-(unsigned char)readUnsignedByte
{
    unsigned char data = 0;
    [readStream read:(UInt8*)&data maxLength:1];
    return data;
}

-(short)readShort
{
    short data = 0;
    [readStream read:(UInt8*)&data maxLength:2];
    data = NSSwapBigShortToHost(data);
    return data;
}

-(unsigned short)readUnsignedShort
{
    unsigned short data = 0;
    [readStream read:(UInt8*)&data maxLength:2];
    data = NSSwapBigShortToHost(data);
    return data;
}

-(int)readInt
{
    int data = 0;
     [readStream read:(UInt8*)&data maxLength:4];
    data = NSSwapBigIntToHost(data);
    return data;    
}
-(unsigned int)readUnsignedInt
{
    unsigned int data = 0;
   [readStream read:(UInt8*)&data maxLength:4];
    data = NSSwapBigIntToHost(data);
    return data;  
}

-(long)readLong
{
    long data = 0;
     [readStream read:(UInt8*)&data maxLength:8];
    data = NSSwapBigLongToHost(data);
    return data;  
}

-(float)readFloat
{
    NSSwappedFloat bigEndianFloat;
    float hostFloat;
    [readStream read:(UInt8*)&bigEndianFloat maxLength:4];
    hostFloat = NSSwapBigFloatToHost(bigEndianFloat);
    
    return hostFloat;
}
-(double)readDouble
{
    NSSwappedDouble bigEndianDouble;
    double hostDouble;
    [readStream read:(UInt8*)&bigEndianDouble maxLength:8];
    hostDouble = NSSwapBigDoubleToHost(bigEndianDouble);
    return hostDouble; 
}

-(void)test
{
    
}

@end
