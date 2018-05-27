//
//  Level3.cpp
//  AngryBirds-mobile
//
//  Created by Andrés on 27/5/18.
//

#include "Level3.hpp"
#include "Ranking.hpp"
#include "Win.hpp"
#include "LevelsScene.hpp"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

Scene* Level3::createScene() {
    return Level3::create();
}

bool Level3::init() {
    
    if (!Scene::initWithPhysics()) { return false; }
    
    //getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // Configure images of sprites
    configureView();
    
    // Add sprites to scene
    this->addChild(backgroundSprite);
    this->addChild(slingshotSprite);
    this->addChild(birdOnStopSprite);
    this->addChild(woodElPort1);
    this->addChild(woodElPort2);
    this->addChild(woodElPort3);
    this->addChild(woodElPort4);
    this->addChild(woodElLand1);
    this->addChild(firstFloorPig1);
    this->addChild(restartButtonSprite);
    this->addChild(menuButtonSprite);
    this->addChild(highScoreLabel);
    this->addChild(birdLife1Sprite);
    this->addChild(birdLife2Sprite);
    
    // Initialize properties
    isTouchDown = false;
    isCorrect = false;
    shooted = false;
    contactOc = false;
    score = 0;
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    // Touchlistener for game logic
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        
        // When user touch slingshot element
        if (touch->getLocation().x < 100 && touch->getLocation().y < 140) {
            // Update position for animate the joystick
            initialTouchPos[0] = touch->getLocation().x;
            currentTouchPos[0] = touch->getLocation().x;
            initialTouchPos[1] = touch->getLocation().y;
            currentTouchPos[1] = touch->getLocation().y;
            isTouchDown = true;
            
        } else if (touch->getLocation().x < 40 && touch->getLocation().y > 250 ) {
            // Restart level button
            auto scene = Level3::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
            
        } else if (touch->getLocation().x > 60 && touch->getLocation().x < 80 && touch->getLocation().y > 250 ) {
            // Menu button
            createMenu();
        }
        return true;
    };
    
    // Touch and move action
    touchListener->onTouchMoved = [=] (Touch* touch, Event* event) {
        
        currentTouchPos[0] = touch->getLocation().x;
        currentTouchPos[1] = touch->getLocation().y;
    };
    
    touchListener->onTouchEnded = [=](Touch* touch, Event* event){
        
        // Reset and release
        isTouchDown = false;
        
        CCLOG("%f",touch->getLocation().y);
        
        if (isCorrect){
            switch (shoots) {
                case 3:
                    
                    // Add bird
                    buildFlyingBird(false,touch->getLocation().y);
                    shoots = 2;
                    break;
                    
                case 2:
                    
                    // Update birds components
                    this->removeChild(birdOnMoveSprite);
                    this->removeChild(birdLife2Sprite);
                    
                    // Add bird
                    buildFlyingBird(false,touch->getLocation().y);
                    shoots = 1;
                    break;
                    
                case 1:
                    
                    // Update birds components
                    this->removeChild(birdOnMoveSprite);
                    this->removeChild(birdLife1Sprite);
                    
                    // Add bird
                    buildFlyingBird(true,touch->getLocation().y);
                    shoots = 0;
                    break;
                    
                default:
                    break;
            }
        }
    };
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level3::onContactBegin, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // Update scene
    this->scheduleUpdate();
    
    return true;
}

// Configure and initialize view
void Level3::configureView() {
    
    // Get properties of view
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1.0f, 1.0f, 1.0f), 4);
    edgeBody->setCollisionBitmask(5);
    edgeBody->setContactTestBitmask(true);
    auto edgeNode = Node::create();
    
    // Retrieve elements of spritesheet and asign it to frames
    auto restartFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("restart.png");
    auto menuFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu.png");
    auto redBirdFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("bird_yellow.png");
    auto slingshotFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ele_slingshot.png");
    auto woodElPortFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ele_wood1portrait.png");
    auto woodElPort1Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ele_wood1.png");
    auto firstPigFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("pic_king.png");
    
    // Configure images of sprite
    backgroundSprite = Sprite::create("background1.png");
    restartButtonSprite = Sprite::createWithSpriteFrame(restartFrame);
    menuButtonSprite = Sprite::createWithSpriteFrame(menuFrame);
    birdOnStopSprite = Sprite::createWithSpriteFrame(redBirdFrame);
    birdLife1Sprite = Sprite::createWithSpriteFrame(redBirdFrame);
    birdLife2Sprite = Sprite::createWithSpriteFrame(redBirdFrame);
    slingshotSprite = Sprite::createWithSpriteFrame(slingshotFrame);
    woodElPort1 = Sprite::createWithSpriteFrame(woodElPortFrame);
    woodElPort2 = Sprite::createWithSpriteFrame(woodElPortFrame);
    woodElPort3 = Sprite::createWithSpriteFrame(woodElPortFrame);
    woodElPort4 = Sprite::createWithSpriteFrame(woodElPortFrame);
    woodElLand1 = Sprite::createWithSpriteFrame(woodElPort1Frame);
    firstFloorPig1 = Sprite::createWithSpriteFrame(firstPigFrame);
    
    // Configure size and element positions of level
    backgroundSprite->setScale(0.5);
    backgroundSprite->setAnchorPoint(Vec2(0,0));
    
    woodElLand1->setScale(0.5, 0.5);
    woodElLand1->setPosition(370,115);
    
    setSpritePositionAndScale(restartButtonSprite,0.5,30,270);
    setSpritePositionAndScale(menuButtonSprite,0.5,70,270);
    setSpritePositionAndScale(birdOnStopSprite,0.60,70,108);
    setSpritePositionAndScale(slingshotSprite,0.8,80,83);
    setSpritePositionAndScale(birdLife1Sprite,0.3,20,50);
    setSpritePositionAndScale(birdLife2Sprite,0.3,40,50);
    setSpritePositionAndScale(woodElPort1,0.45,400,80);
    setSpritePositionAndScale(woodElPort2,0.45,250,80);
    setSpritePositionAndScale(woodElPort3,0.45,250,145);
    setSpritePositionAndScale(woodElPort4,0.45,345,80);
    setSpritePositionAndScale(firstFloorPig1,1,370,140);
    
    // Add physics body to sprites
    buildRectangleElement(woodElPort1, 7, 2, PhysicsMaterial(0.3f, 0.3f, 0.5f));
    buildRectangleElement(woodElPort2, 7, 2, PhysicsMaterial(0.3f, 0.3f, 0.5f));
    buildRectangleElement(woodElPort3, 7, 2, PhysicsMaterial(0.3f, 0.3f, 0.5f));
    buildRectangleElement(woodElPort4, 7, 2, PhysicsMaterial(0.3f, 0.3f, 0.5f));
    buildRectangleElement(woodElLand1, 7, 2, PhysicsMaterial(0.05f, 0.01f, 0.1f));
    
    buildRectangleElement(firstFloorPig1, 5, 5, PhysicsMaterial(1.0f, 1.0f, 0.5f));
    
    // Add edge box to screen
    edgeNode->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 20));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    // High score label
    highScoreLabel = Label::createWithTTF("Puntuación: 0", "fonts/angrybirds.ttf", 12);
    highScoreLabel->setColor(Color3B::WHITE);
    highScoreLabel->setPosition(Vec2(420,280));
    highScoreLabel->enableBold();
    
    // Shoots alloweds
    shoots = 3;
}

// Assign position and scale to sprites
void Level3::setSpritePositionAndScale(Sprite* image, float scale, float x, float y) {
    image->setScale(scale);
    image->setPosition(x,y);
}

// Custom physics for rectangle elements of scene, and add custom density for each one
void Level3::buildRectangleElement(Sprite* image, int size, int maskCollision, PhysicsMaterial physicsMaterial) {
    auto imageEdge = PhysicsBody::createBox(image->getContentSize()-Size(size,size),physicsMaterial);
    imageEdge->setCollisionBitmask(maskCollision);
    imageEdge->setContactTestBitmask(true);
    imageEdge->setDynamic(true);
    image->addComponent(imageEdge);
    image->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
}

// Custom physics for circle elements of scene
void Level3::buildCircleElement(Sprite* image, int radius, int maskCollision, PhysicsMaterial physicsMaterial) {
    auto imageEdge = PhysicsBody::createCircle(radius,physicsMaterial);
    imageEdge->setCollisionBitmask(maskCollision);
    imageEdge->setContactTestBitmask(true);
    imageEdge->setDynamic(true);
    image->addComponent(imageEdge);
    image->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
}

// Custom physics for flying bird
void Level3::buildFlyingBird(bool last, float angle) {
    // Create components
    auto redBirdFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("bird_yellow.png");
    auto birdEdge = PhysicsBody::createCircle(9,PhysicsMaterial(1.0f, 1.0f, 1.0f));
    
    // Create bird
    birdOnMoveSprite = Sprite::createWithSpriteFrame(redBirdFrame);
    birdOnMoveSprite->setScale(0.60);
    birdOnMoveSprite->setPosition(Vec2(70, 110));
    
    // Add impulse to bird
    if (angle > 100 && angle < 120){ birdEdge->setVelocity(Vec2(300, angle/2)); }
    else if (angle > 120) { birdEdge->setVelocity(Vec2(300, angle/6));}
    else { birdEdge->setVelocity(Vec2(300, angle*2)); }
    birdEdge->setDynamic(true);
    birdEdge->setCollisionBitmask(1);
    birdEdge->setContactTestBitmask(true);
    birdOnMoveSprite->addComponent(birdEdge);
    
    // Reset main position and add flying bird
    birdOnStopSprite->setPosition(Vec2(70, 110));
    this->addChild(birdOnMoveSprite);
    if (last) { this->removeChild(birdOnStopSprite); }
    isCorrect = false;
    shooted = true;
    contactOc = false;
    
    auto audio = SimpleAudioEngine::getInstance();
    audio->playEffect("fly.mp3", false, 1.0f, 1.0f, 1.0f);
}

// Create and display menu options
void Level3::createMenu() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto boxFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("boxitem.png");
    boxMenu = Sprite::createWithSpriteFrame(boxFrame);
    boxMenu->setPosition(Vec2(visibleSize.width/2,(visibleSize.height/2)+10));
    boxMenu->setScale(1);
    
    auto menuItem1 = MenuItemFont::create("Clasificación", CC_CALLBACK_1(Level3::menuRankingCallback, this));
    auto menuItem2 = MenuItemFont::create("Salir", CC_CALLBACK_1(Level3::menuExitCallback, this));
    
    menuItem1->setScale(0.8);
    menuItem2->setScale(0.8);
    menuItem1->setPosition(Point(visibleSize.width/2,(visibleSize.height/2)+35));
    menuItem2->setPosition(Point(visibleSize.width/2,(visibleSize.height/2)-3));
    
    menu = Menu::create(menuItem1,menuItem2,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(boxMenu);
    this->addChild(menu);
    
    // Touchlistener for game logic
    auto menuListener = EventListenerTouchOneByOne::create();
    menuListener->onTouchBegan = [this](Touch* touch, Event* event){
        this->removeChild(menu);
        this->removeChild(boxMenu);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(menuListener, this);
}

// Menu Callbacks

void Level3::menuExitCallback(Ref* pSender) {
    auto scene = LevelsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}

void Level3::menuRankingCallback(Ref* pSender) {
    auto scene = Ranking::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}

// Method for listener and logic of game
bool Level3::onContactBegin(PhysicsContact& contact){
    /**
     1: Bird flying
     2: Wood objets
     3: Pigs 1
     4: Pigs 2
     5: BigPig
     6: Floor
     **/
    
    PhysicsBody *object1 = contact.getShapeA()->getBody();
    PhysicsBody *object2 = contact.getShapeB()->getBody();
    
    if (shooted) {
        if (score < 100) {
            if ((5 == object1->getCollisionBitmask() && 2 == object2->getCollisionBitmask()) ||
                (2 == object1->getCollisionBitmask() && 5 == object2->getCollisionBitmask())) {
                // Big pig contact
                if (score < 100 && pigs[2] == 0) { pigContact(firstFloorPig1,2); }
                highScoreLabel->setString("Puntuación: "+ to_string(score));
            }
        } else {
            auto scene = Win::createScene(score);
            Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
        }
    }
    return true;
}

// When pig contact with wood element or ground
void Level3::pigContact(Sprite* image, int position) {
    // Create anim and update score
    auto smoke = ParticleSmoke::create();
    smoke->setPosition(image->getPosition());
    smoke->setDuration(0.1);
    score = score + 100;
    pigs[position] = 1;
    
    this->addChild(smoke);
    this->removeChild(image);
    
    auto audio = SimpleAudioEngine::getInstance();
    audio->playEffect("destroy.mp3", false, 1.0f, 1.0f, 1.0f);
}

// Method for update
void Level3::update(float f) {
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (isTouchDown) {
        
        // Recognize end position
        if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05){
            CCLOG("LEFT");
            
            auto moveTo = MoveTo::create(0.3, Vec2(currentTouchPos[0],currentTouchPos[1]));
            birdOnStopSprite->runAction(moveTo);
            
            isTouchDown = false;
            isCorrect = true;
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - visibleSize.width * 0.05){
            CCLOG("RIGHT");
            isTouchDown = false;
            isCorrect = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05){
            CCLOG("DOWN");
            isTouchDown = false;
            isCorrect = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05){
            CCLOG("UP");
            isTouchDown = false;
            isCorrect = false;
        }
    }
}
