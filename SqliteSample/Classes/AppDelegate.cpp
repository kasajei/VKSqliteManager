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
    
    
    
    // Sample
    Sample *sample = Sample::create();
    sample->setName(CCString::create("test2"));
    sample-> setAddress(CCString::create("testAddress"));
    sample->setPhone(CCString::create("08011212312"));
 
    // SampleManager
    SampleManager *sampleManager = SampleManager::create();
    sampleManager->deleteTable(); // delete table
    // reCreateTable
    sampleManager = SampleManager::create();
    
    sampleManager->save(sample);
    
    CCArray* allArray = sampleManager->selectAll();
    CCObject *object = NULL;
    CCARRAY_FOREACH(allArray, object) {
        CCLOG("select all");
        Sample *sample = (Sample *)object;
        CCLog("%s",sample->toString());
    }
    
    sampleManager->deleteWithEntity(sample);
    allArray = sampleManager->selectAll();
    object = NULL;
    CCARRAY_FOREACH(allArray, object) {
        Sample *sample = (Sample *)object;
        CCLog("%s",sample->toString());
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
