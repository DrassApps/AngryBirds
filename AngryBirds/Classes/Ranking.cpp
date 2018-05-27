//
//  Achievements.cpp
//  AngryBirds-mobile
//
//  Created by Andrés on 14/5/18.
//

#include "Ranking.hpp"
#include "SplashScene.hpp"
#include "network/HttpClient.h"
#include <vector>
#include <string.h>

using namespace cocos2d;
using namespace std;
using namespace network;

USING_NS_CC;

Scene* Ranking::createScene() {
    return Ranking::create();
}

bool Ranking::init() {
    
    if (!Scene::init()) { return false; }
    Director::getInstance()->setDisplayStats(false);
    
    // Dimens
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get user ranking
    HttpRequest* request = new (nothrow) HttpRequest();
    request->setUrl("http://www.drassapps.es/public/user1");
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2 (Ranking::onHttpRequestCompleted, this));
    
    HttpClient::getInstance()->sendImmediate(request);
    
    request->release();
    
    auto boxFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("boxitem.png");
    backgroundSprite = Sprite::createWithSpriteFrame(boxFrame);
    backgroundSprite->setPosition(Vec2(visibleSize.width/2,(visibleSize.height/2)+10));
    backgroundSprite->setScale(5);
    
    auto menuFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu.png");
    settingsButton = Sprite::createWithSpriteFrame(menuFrame);
    settingsButton->setScale(0.5);
    settingsButton->setPosition(Vec2(40,45));
    
    this->addChild(backgroundSprite);
    this->addChild(settingsButton);
    
    // Touch screen for play
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        // Replace scene
        auto scene = SplashScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
        
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void Ranking::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response )
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (response && response->getResponseCode() == 200 && response->getResponseData()) {
        vector<char> *data = response->getResponseData();
        string ret(&(data->front()), data->size());
       // CCLOG("%s", ("Response message: " + ret).c_str());
        
        stringstream test(ret);
        string segment;
        vector<string> seglist;
        
        while(getline(test, segment, '-')) { seglist.push_back(segment); }
        
        CCLOG("%s",seglist[0].c_str());
        CCLOG("%s",seglist[1].c_str());
        
        highScoreLabel1 = Label::createWithTTF(seglist[0], "fonts/angrybirds.ttf", 12);
        highScoreLabel1->setColor(Color3B::WHITE);
        highScoreLabel1->setPosition(Vec2(visibleSize.width/2,(visibleSize.height/2)+50));
        highScoreLabel1->enableBold();
        
        highScoreLabel2 = Label::createWithTTF(seglist[1], "fonts/angrybirds.ttf", 12);
        highScoreLabel2->setColor(Color3B::WHITE);
        highScoreLabel2->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        highScoreLabel2->enableBold();
        
        this->addChild(highScoreLabel1);
        this->addChild(highScoreLabel2);
    }
}
