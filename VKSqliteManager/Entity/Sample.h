//
//  Sample.h
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef SqliteSample_Sample_
#define SqliteSample_Sample_

#include "VKBaseEntity.h"

static const char *nameKey = "name";
static const char *addressKey = "address";
class Sample : public  VKBaseEntity
{

public:
    virtual ~Sample();
    Sample();
    CREATE_FUNC(Sample);
    
public:
    void setName(cocos2d::CCString *name);
    cocos2d::CCString* getName();
    void setAddress(cocos2d::CCString *address);
    cocos2d::CCString* getAddress();
};

#endif

