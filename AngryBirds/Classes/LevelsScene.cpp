//
//  LevelsScene.cpp
//  AngryBirds-mobile
//
//  Created by Andrés on 12/5/18.
//

#include "LevelsScene.hpp"
#include "Level1.hpp"
#include "Level2.hpp"
#include "Level3.hpp"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

Scene* LevelsScene::createScene() {
    return LevelsScene::create();
}

bool LevelsScene::init() {

    if (!Scene::init()) { return false; }
   
    Director::getInstance()->setDisplayStats(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    backgroundSprite = Sprite::create("level.png");
    backgroundSprite->setScale(0.78,0.75);
    backgroundSprite->setPosition(Vec2(visibleSize.width/2,(visibleSize.height/2)+30));
    
    this->addChild(backgroundSprite);
    
    // Touchlistener for levels
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        
        auto audio = SimpleAudioEngine::getInstance();
        audio->stopAllEffects();
        
        if (touch->getLocation().x < 50 && touch->getLocation().y > 250) {
            // Level 1
            auto scene = Level1::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
            
        } else if (touch->getLocation().x > 80 && touch->getLocation().x < 130 && touch->getLocation().y > 250 ) {
            // Level 2
            auto scene = Level2::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
        
        } else if (touch->getLocation().x > 155 && touch->getLocation().x < 200 && touch->getLocation().y > 250 ) {
            // Level 3
            auto scene = Level3::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
        }
        
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
