//
//  SplashScene.cpp
//  AngryBirds-mobile
//
//  Created by Andrés on 12/5/18.
//

#include "SplashScene.hpp"
#include "LevelsScene.hpp"
#include "Ranking.hpp"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

Scene* SplashScene::createScene() {
    return SplashScene::create();
}

bool SplashScene::init() {
    
    if (!Scene::init()) { return false; }
    Director::getInstance()->setDisplayStats(false);    
    
    // Load spritesheet on cache
    auto angryBirdSpriteSheet = SpriteFrameCache::getInstance();
    angryBirdSpriteSheet->addSpriteFramesWithFile("angry_birds.plist");
    
    // Dimens
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto screenWidth = visibleSize.width;
    auto screenHeight = visibleSize.height;
    
    auto playFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ele_play.png");
    auto settingsFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ele_settings.png");
    auto rankingFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ele_achieve.png");

    // Background Sprite
    backgroundSprite = Sprite::create("backgroundintro.png");
    backgroundSprite->setScale(0.7);
    backgroundSprite->setPosition(Vec2(screenWidth/2,screenHeight/2));
    
    playButton = Sprite::createWithSpriteFrame(playFrame);
    playButton->setScale(0.4,0.35);
    playButton->setPosition(Vec2(screenWidth/2,45));
    
    settingsButton = Sprite::createWithSpriteFrame(settingsFrame);
    settingsButton->setScale(0.8);
    settingsButton->setPosition(Vec2(40,45));
    
    achieveButton = Sprite::createWithSpriteFrame(rankingFrame);
    achieveButton->setScale(0.8);
    achieveButton->setPosition(Vec2(screenWidth-40,45));
    
    // Add nodes to scene
    this->addChild(backgroundSprite);
    this->addChild(playButton);
    this->addChild(settingsButton);
    this->addChild(achieveButton);
    
    auto audio = SimpleAudioEngine::getInstance();
    audio->playEffect("game.mp3", false, 1.0f, 1.0f, 1.0f);
 
    // Touchlistener for levels
    auto touchListener3 = EventListenerTouchOneByOne::create();
    touchListener3->onTouchBegan = [=](Touch* touch, Event* event){
        
        auto audio = SimpleAudioEngine::getInstance();
        audio->stopAllEffects();
        
        CCLOG("%f",touch->getLocation().x);
        
        if (touch->getLocation().x > 410) {
            // Rnking
            auto scene = Ranking::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
            
        } else {
            // Levels
            auto scene = LevelsScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
        }
        
        return true;
    };
 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener3, this);
    
    return true;
}
