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
    // setting to database's path
    std::string dbPath = CCFileUtils::sharedFileUtils()->getWriteablePath();
    dbPath.append(dbFileName);
    
    //  get database's connection
    int result = sqlite3_open(dbPath.c_str(),&pDB);
    if (result != SQLITE_OK){
        CCLOG("OPENING WRONG, %d, MSG:%s",result);
        return false;
    }else{
        return true;
    }
}

void VKBaseManager::closeDB(){
    sqlite3_close(pDB);
}

bool VKBaseManager::sqlExec(const char *sql, int (*callback)(void *, int, char **, char**)){
    if (!connectDB()) { // connect to database
        return false; // failure to connect database
    }
    
    CCLOG("sqlExec %s",sql);
    char* errMsg = NULL;
    int result = sqlite3_exec( pDB, sql ,callback, NULL, &errMsg );
    
    if(result != SQLITE_OK ){
        CCLOG( "Failure　:%d ，becouse :%s\n" , result, errMsg );
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
                const char* text =  (const char*)sqlite3_column_text(stmt, i);
                if (!text) text = ""; // if column is null , text set "".
                CCString* string = CCString::create(text);
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

bool VKBaseManager::createTableWithTableSetting(const char *tableSetting){
    CCString *sqlString = CCString::createWithFormat("create table %s ( %s integer primary key autoincrement, %s )", tableName,idKey, tableSetting);
    return sqlExec(sqlString -> getCString());
}

bool VKBaseManager::addColumn(){
    return true;
}

bool VKBaseManager::addColumnWithArray(CCArray *columnAry){
    CCObject *string;
    CCARRAY_FOREACH(columnAry, string){
        CCString *sqlString = CCString::createWithFormat("alter table %s add column %s", tableName, ((CCString *)string)->getCString());
        sqlExec(sqlString -> getCString());
    }
    return true;
}

bool VKBaseManager::deleteTable(){
    CCString *string = CCString::createWithFormat("DROP TABLE '%s'",tableName);
    CCLog("%s", string->getCString());
    return sqlExec(string->getCString());
}




VKBaseEntity* VKBaseManager::save(VKBaseEntity *entity)
{
    if (entity == NULL) {
        return NULL;
    }
    // Frist, try to save entity.
    CCDictElement *element = NULL;
    CCString *keys = CCString::create("");
    CCString *values = CCString::create("");
    CCString *updates = CCString::create("");
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
        
        if (updates -> isEqual(CCString::create(""))) {
            updates = CCString::createWithFormat(" %s = '%s' ", element->getStrKey(), value->getCString());
        }else{
            updates = CCString::createWithFormat("%s, %s = '%s' ", updates->getCString(), element->getStrKey(), value->getCString());
        }
    }
    CCString *insertString = CCString::createWithFormat("insert into %s ( %s ) values ( %s ) ", tableName, keys->getCString(), values->getCString());
    
    bool result  = sqlExec(insertString->getCString());

    // if entity cannot save, this entity should be saved or has properties more than old entity's definition.
    if (!result) {
        if (entity->getId()) { // if entity has id, this entity already exist, so this entity should be saved
            CCString *updateString = CCString::createWithFormat("update %s set %s where id = %d",tableName, updates->getCString(), entity->getId());
            result = sqlExec(updateString->getCString());
        }else{
            // TODO : 
            // this failure maybe have more properties than old entity's definition, so alter table.
            addColumn(); // change table
            save(entity); // Re-save entity
        }
    }else{
        CCArray *array = select(entity);
        entity = (VKBaseEntity *)array->lastObject();
    }
    return entity;
    
}



CCArray* VKBaseManager::select(VKBaseEntity *entity)
{
    if (entity == NULL) {
        return NULL;
    }
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
    CCString *sqlString = CCString::createWithFormat("select * from %s where %s ", tableName, where);
    return sqlPrepare(sqlString->getCString());
    
}





