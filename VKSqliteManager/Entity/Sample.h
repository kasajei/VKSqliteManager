//
//  Sample.h
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef SqliteSample_Sample_
#define SqliteSample_Sample_

#include "cocos2d.h"

static const char *idKey = "id";
static const char *nameKey = "name";
class Sample : public cocos2d::CCDictionary
{

public:
    virtual bool init();
    virtual ~Sample();
    Sample();
    CREATE_FUNC(Sample);
    
public:
    void setId(int idNum);
    int getId();
    void setName(cocos2d::CCString *name);
    cocos2d::CCString* getName();
};

#endif

