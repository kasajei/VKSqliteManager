//
//  VKBaseManager.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "VKBaseManager.h"


using namespace cocos2d;
using namespace std;


bool VKBaseManager::init(){
    if (!checkTable()) {
        createTable();
    }
    return true;
}



VKBaseManager::VKBaseManager()
{
}

VKBaseManager::~VKBaseManager()
{
}

bool VKBaseManager::connectDB(){
    // DBのパスを指定
    std::string dbPath = CCFileUtils::sharedFileUtils()->getWriteablePath();
    dbPath.append(dbFileName);
//    CCLOG("sqlConect Path %s",dbPath.c_str());
    
    // DBを取得
    int result = sqlite3_open(dbPath.c_str(),&pDB);
    if (result != SQLITE_OK){
        CCLOG("OPENING WRONG, %d, MSG:%s",result);
        return false;
    }else{
//        CCLOG("sqlConnect OK! %d, %s",result);
        return true;
    }
}

void VKBaseManager::closeDB(){
    sqlite3_close(pDB);
}

bool VKBaseManager::sqlExec(const char *sql, int (*callback)(void *, int, char **, char**)){
    if (!connectDB()) { // DBへの接続
        return false; // 接続失敗
    }
    
    CCLOG("sqlExec %s",sql);
    char* errMsg = NULL;
    int result = sqlite3_exec( pDB, sql ,callback, NULL, &errMsg );
    
    if(result != SQLITE_OK ){
        CCLOG( "失敗　:%d ，原因:%s\n" , result, errMsg );
        closeDB();
        return false;
    }else{
        closeDB();
        return true;
    }
    
    
}


CCArray* VKBaseManager::sqlPrepare(const char *sql){
    CCArray *resultArray = CCArray::create();
    
    if (!connectDB()) {
        return resultArray;
    }
    
    CCLOG("sqlPrepare %s",sql);
    sqlite3_stmt *stmt = NULL;
    if(sqlite3_prepare_v2(pDB, sql, -1, &stmt, NULL) == SQLITE_OK){
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            CCDictionary *dic = CCDictionary::create();
            int columnNum = sqlite3_column_count(stmt);
            for (int i = 0; i < columnNum; i++) {
                CCString* string = CCString::create((const char*)sqlite3_column_text(stmt, i));
                const char *key = sqlite3_column_name(stmt, i);
                dic->setObject(string, key);
            }
            resultArray->addObject(dic);
        }
    }else{
        CCLOG("not SQLLITE_OK");
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    
    closeDB();
    return resultArray;
}




bool VKBaseManager::checkTable(){
    CCString *string = CCString::createWithFormat("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%s'",tableName);
    CCArray *array = sqlPrepare(string -> getCString());
    CCDictionary *dic =  (CCDictionary *)array->objectAtIndex(0);
    CCString *countString = (CCString*)dic->objectForKey("count(*)");
    return countString->intValue();
}




bool VKBaseManager::createTable(){
    return true;
}


bool VKBaseManager::deleteTable(){
    CCString *string = CCString::createWithFormat("DROP TABLE '%s'",tableName);
    CCLog("%s", string->getCString());
    return sqlExec(string->getCString());
}


bool VKBaseManager::save(CCDictionary *entity)
{
    // keyに設定されているものをすべて
    CCDictElement *element = NULL;
    CCString *keys = CCString::create("");
    CCString *values = CCString::create("");
    CCDICT_FOREACH(entity, element){
        if (keys -> isEqual(CCString::create(""))) {
            keys = CCString::createWithFormat("%s",element->getStrKey());
        }else{
            keys = CCString::createWithFormat("%s, %s",keys->getCString(), element->getStrKey());
        }
        
        CCString *value = (CCString *)element -> getObject();
        if (values -> isEqual(CCString::create(""))) {
            values = CCString::createWithFormat("'%s'",value->getCString());
        }else{
            values = CCString::createWithFormat("%s, '%s'", values->getCString(), value->getCString());
        }
        
    }
    CCString *sqlString = CCString::createWithFormat("insert into %s ( %s ) values ( %s ) ", tableName, keys->getCString(), values->getCString());
    
    
    return sqlPrepare(sqlString->getCString());
    
}



CCArray* VKBaseManager::select(CCDictionary *entity)
{
    // keyに設定されているものをすべて
    CCDictElement *element = NULL;
    CCString *where = CCString::create("");
    CCDICT_FOREACH(entity, element){
        if (where -> isEqual(CCString::create(""))) {
            CCString *value = (CCString *)element -> getObject();
            where = CCString::createWithFormat(" %s = '%s' ",element->getStrKey(),value->getCString());
        }else{
            CCString *value = (CCString *)element -> getObject();
            where = CCString::createWithFormat(" %s AND %s = '%s' ",where->getCString(), element->getStrKey(), value->getCString());
        }
    }
    return selectWithWhere(where->getCString());
    
}


CCArray* VKBaseManager::selectWithWhere(const char *where)
{
    CCString *sqlString = CCString::createWithFormat("select * from %s where %s ", tableName,where);
    return sqlPrepare(sqlString->getCString());
    
}




