//
//  SampleManager.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "SampleManager.h"
#include "sqlite3.h"
#include "Sample.h"

using namespace cocos2d;

bool SampleManager::init(){
    dbFileName = "new.db";
    tableName = sampleTable;
    if (!VKBaseManager::init()) {
        return false;
    }
    return true;
}

SampleManager::SampleManager()
{
}

SampleManager::~SampleManager()
{
}

bool SampleManager::createTable(){
    CCString *sqlString = CCString::createWithFormat("%s nvarchar(32), %s nvarchar(32)", nameKey, addressKey);
    return createTableWithTableSetting(sqlString -> getCString());
}


CCArray* SampleManager::getSampleGreaterThanId(int idNum){
    CCString *where = CCString::createWithFormat("%s > %d", idKey, idNum);
    return selectWithWhere(where -> getCString());
}