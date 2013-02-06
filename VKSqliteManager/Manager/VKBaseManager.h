//
//  VKBaseManager.h
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef SqliteSample_VKBaseManager_
#define SqliteSample_VKBaseManager_

#include "cocos2d.h"
#include "sqlite3.h"
#include "VKBaseEntity.h"

class VKBaseManager : public cocos2d::CCObject
{

public:
    virtual bool init();
	VKBaseManager();
	virtual ~VKBaseManager();
    bool connectDB();
    bool sqlExec(const char *sql, int (*callback)(void *, int, char **, char**) = NULL);
    cocos2d::CCArray *sqlPrepare(const char *sql);
    void closeDB();
    CREATE_FUNC(VKBaseManager);
    
protected:
    const char* dbFileName = "default.db";
    const char* tableName = "";
    sqlite3 *pDB = NULL;
    
public:
    virtual bool checkTable();
    virtual bool createTable();
    virtual bool deleteTable();
    virtual VKBaseEntity* save(VKBaseEntity *entity);
    virtual cocos2d::CCArray* select(VKBaseEntity *entity);
    virtual cocos2d::CCArray* selectWithWhere(const char *where);
    
protected:
    virtual bool createTableWithTableSetting(const char *tableSetting);

};



#endif