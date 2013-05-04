//
//  SampleManager.h
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef SqliteSample_SampleManager_
#define SqliteSample_SampleManager_

#include "cocos2d.h"
#include "VKBaseManager.h"

static const char *sampleTable = "Sample";
class SampleManager : public VKBaseManager
{

public:
    bool init();
	SampleManager();
	virtual ~SampleManager();
    virtual bool createTable();
    virtual bool runAfterCreateTableOnce();
    virtual bool addColumn();
    CREATE_FUNC(SampleManager);
    
public:
    cocos2d::CCArray* getSampleGreaterThanId(int idNum);
};

#endif