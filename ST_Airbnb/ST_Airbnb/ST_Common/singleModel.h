//
//  singleModel.h
//  GCDMessage
//
//  Created by 仇寻 on 17/4/10.
//  Copyright © 2017年 shootingTime. All rights reserved.
//  a define for singleModel.

#define singleH(name) +(instancetype)default##name;

//condition compiler
//1.if------judge
#if __has_feature(objc_arc)
//when ARC
#define singleM(name) static id _SMARC;\
+(instancetype)allocWithZone:(struct _NSZone *)zone{\
static dispatch_once_t onceToken;\
dispatch_once(&onceToken, ^{\
_SMARC = [super allocWithZone:zone];\
});\
return _SMARC;\
}\
\
+(instancetype)default##name{\
return [[self alloc]init];\
}\
\
-(id)copyWithZone:(NSZone *)zone{\
return _SMARC;\
}\
\
-(id)mutableCopyWithZone:(NSZone *)zone{\
return _SMARC;\
}
//2.else----do sth if there is no sense in the condition(when MRC).
#else
#define singleM(name) static id _SMARC;\
+(instancetype)allocWithZone:(struct _NSZone *)zone{\
static dispatch_once_t onceToken;\
dispatch_once(&onceToken, ^{\
_SMARC = [super allocWithZone:zone];\
});\
return _SMARC;\
}\
\
+(instancetype)default##name{\
return [[self alloc]init];\
}\
\
-(id)copyWithZone:(NSZone *)zone{\
return _SMARC;\
}\
\
-(id)mutableCopyWithZone:(NSZone *)zone{\
return _SMARC;\
}\
-(oneway void)release{\
\
}\
\
-(instancetype)retain{\
    return _SMARC;\
}\
-(NSUInteger)retainCount{\
    return MAXFLOAT;\
}
//3.endif---to end this condition compiler.
#endif
