/**
 * Reads data from an input stream.
 *
 * @author DMcG
 */

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
//#import <CoreServices/CoreServices.h>


@interface DataInput : NSObject 
{
     NSInputStream   *readStream;
}

-(id)initWithData:(NSData*)data;

-(char)readByte;
-(unsigned char)readUnsignedByte;

-(short)readShort;
-(unsigned short)readUnsignedShort;

-(int)readInt;
-(unsigned int)readUnsignedInt;

-(long)readLong;

-(float)readFloat;
-(double)readDouble;

@end
