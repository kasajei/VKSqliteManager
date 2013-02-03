//
//  Sample.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "Sample.h"

using namespace cocos2d;

bool Sample::init(){
    return true;
}

Sample::Sample() {

}

Sample::~Sample()
{

}


void Sample::setId(int idNum){
    CCString *string = CCString::createWithFormat("%d",idNum);
    this -> setObject(string, idKey);
}

int Sample::getId(){
    CCString *string = (CCString *)this -> objectForKey(idKey);
    return string -> intValue();
}


void Sample::setName(CCString *name){
    this -> setObject(name, nameKey);
}

CCString* Sample::getName(){
    return (CCString *)this -> objectForKey(nameKey);
}