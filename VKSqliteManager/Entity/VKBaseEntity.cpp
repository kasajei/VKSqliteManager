//
//  VKBaseEntity.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "VKBaseEntity.h"

using namespace cocos2d;

bool VKBaseEntity::init(){
    return true;
}

VKBaseEntity::VKBaseEntity()
{
}

VKBaseEntity::~VKBaseEntity()
{
}





void VKBaseEntity::setId(int idNum){
    CCString *string = CCString::createWithFormat("%d",idNum);
    this -> setObject(string, idKey);
}

int VKBaseEntity::getId(){
    CCString *string = (CCString *)this -> objectForKey(idKey);
    if (string) {
        return string -> intValue();
    }else{
        return 0;
    }
    
}