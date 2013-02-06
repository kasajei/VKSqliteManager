//
//  SqliteSampleAppDelegate.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Sample.h"
#include "SampleManager.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
    
    
    
    // サンプル
    Sample *sample = Sample::create();
    sample->setName(CCString::create("test2"));
 
    SampleManager *sampleManager = SampleManager::create();
//    sampleManager->deleteTable();
//    sampleManager->createTable();
    
    sample = (Sample *)sampleManager->save(sample); // insert した結果が返ってくる
    
    CCArray* resultArray =  sampleManager->select(sample);
    CCObject *object = NULL;
    Sample *lastsample = NULL;
    CCARRAY_FOREACH(resultArray, object){
        Sample *sample = (Sample *)object;
        CCLog("%d,%s",sample->getId(),((CCString *)sample->getName())->getCString());
        lastsample = (Sample *)object;
    }
    
    CCArray* resultArray2 =  sampleManager->select(lastsample);
    CCARRAY_FOREACH(resultArray2, object){
        Sample *sample = (Sample *)object;
        CCLog("%d,%s",sample->getId(),((CCString *)sample->getName())->getCString());
    }
    
    // insertした結果を書き換える
    sample->setName(CCString::createWithFormat("test5"));
    sampleManager->save(sample);
    
    CCArray* resultArray3 =  sampleManager->getSampleGreaterThanId(1);
    CCARRAY_FOREACH(resultArray3, object){
        Sample *sample = (Sample *)object;
        CCLog("%d,%s",sample->getId(),((CCString *)sample->getName())->getCString());
    }
    

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
