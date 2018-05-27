//
//  Win.cpp
//  AngryBirds-mobile
//
//  Created by Andrés on 14/5/18.
//

#include "Win.hpp"
#include "LevelsScene.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace std;

int levelScore;

Scene* Win::createScene(int score) {
    levelScore = score;
    return Win::create();
}

bool Win::init() {
    
    if (!Scene::init()) { return false; }
    
    Director::getInstance()->setDisplayStats(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
   
    backgroundSprite = Sprite::create("win.png");
    backgroundSprite->setScale(0.9);
    backgroundSprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    scoreLabel = Label::createWithTTF(to_string(levelScore), "fonts/angrybirds.ttf", 25);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(visibleSize.width/2,(visibleSize.height/2) + 62);
    scoreLabel->enableBold();
    
    congratulationsLabel = Label::createWithTTF("Felicidades", "fonts/angrybirds.ttf", 25);
    congratulationsLabel->setColor(Color3B::WHITE);
    congratulationsLabel->setPosition(visibleSize.width/2,(visibleSize.height/2) + 110);
    congratulationsLabel->enableBold();
    
    this->addChild(backgroundSprite);
    this->addChild(scoreLabel);
    this->addChild(congratulationsLabel);
    
    auto audio = SimpleAudioEngine::getInstance();
    audio->playEffect("levelcomplete.mp3", false, 1.0f, 1.0f, 1.0f);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        // Replace scene
        auto scene = LevelsScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
