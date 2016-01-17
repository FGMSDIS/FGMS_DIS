//
//  PduFactory.m
//  ObjcDis
//
//  Created by Donald McGregor on 8/27/09.
//  Copyright 2009 NPS. All rights reserved.
//

#import "PduFactory.h"
#import "EntityStatePdu.h"
#import "Pdu.h"
#import "DataInput.h"


@implementation PduFactory

-(id)init
{
    self = [super init];
    if(self)
    {
        
    }
    return self;
}

-(Pdu*)pduForData:(NSData*)data
{
    char pduType;
    unsigned char buf[3];
    DataInput* inputStream = [[DataInput alloc] initWithData:data];
    
    [data getBytes:&buf[0] length:3];
    pduType = buf[2];
    NSLog(@"PDU type is %i", pduType);
    
    switch(pduType)
    {
        case 1:
            NSLog(@"in switch statement for espdu");
            EntityStatePdu* espdu = [[EntityStatePdu alloc] init];
            [espdu unmarshalUsingStream:inputStream];
            EntityID* eid = [espdu entityID];
            Vector3Double* location = [espdu entityLocation];
            Orientation* orientation = [espdu entityOrientation];
            
            NSLog(@"Entity type, unmarshalled:%i, EID=%i, %i, %i", [espdu pduType], [eid site], [eid application], [eid entity]);
            
            NSLog(@"Position:%f, %f, %f", [location x], [location y], [location z]);
            NSLog(@"Orientation:%f, %f, %f", [orientation theta], [orientation phi], [orientation psi]);
            return espdu;
            break;
            
        default:
            NSLog(@"Pdu type %i is not yet handled", pduType);
    }
    
    return nil;
    
    
}


@end
