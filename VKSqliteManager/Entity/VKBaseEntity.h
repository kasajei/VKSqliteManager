//
//  VKBaseEntity.h
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef SqliteSample_VKBaseEntity_
#define SqliteSample_VKBaseEntity_

#include "cocos2d.h"

static const char *idKey = "id";
class VKBaseEntity : public cocos2d::CCDictionary
{

public:
    virtual bool init();
	VKBaseEntity();
	virtual ~VKBaseEntity();
     CREATE_FUNC(VKBaseEntity);
    
public:
    void setId(int idNum);
    int getId();
};

#endif