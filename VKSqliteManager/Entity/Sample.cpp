//
//  Sample.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "Sample.h"

using namespace cocos2d;


Sample::Sample() {

}

Sample::~Sample()
{

}



void Sample::setName(CCString *name){
    this -> setObject(name, nameKey);
}

CCString* Sample::getName(){
    return (CCString *)this -> objectForKey(nameKey);
}