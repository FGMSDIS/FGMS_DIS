
#import <Foundation/foundation.h>
#import "Pdu.h"

@interface PduFactory : NSObject 
{

}

-(id)init;
-(Pdu*)pduForData:(NSData*)data;

@end
