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

void Sample::setAddress(CCString *address){
    this -> setObject(address, addressKey);
}

CCString* Sample::getAddress(){
    return (CCString *)this -> objectForKey(addressKey);
}

void Sample::setPhone(CCString *phone){
    this -> setObject(phone, phoneKey);
}

CCString* Sample::getPhone(){
    return (CCString *)this -> objectForKey(phoneKey);
}