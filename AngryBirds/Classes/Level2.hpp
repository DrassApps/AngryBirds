//
//  Level2.hpp
//  AngryBirds-mobile
//
//  Created by Andrés on 14/5/18.
//

#ifndef Level2_hpp
#define Level2_hpp

#include <stdio.h>

using namespace cocos2d;

class Level2 : public Scene {
private:
    Sprite* backgroundSprite;
    Sprite* birdOnStopSprite;
    Sprite* birdOnMoveSprite;
    Sprite* birdLife1Sprite;
    Sprite* birdLife2Sprite;
    Sprite* slingshotSprite;
    Sprite* boxMenu;
    Sprite* groundPig1;
    Sprite* firstFloorPig1;
    Sprite* woodElPort1;
    Sprite* woodElPort2;
    Sprite* woodElLand1;
    Sprite* restartButtonSprite;
    Sprite* menuButtonSprite;
    
    Menu* menu;
    Label* highScoreLabel;
    int shoots;
    int score;
    int pigs[3] = {0,0,0};
    
public:
    // Initialize
    static Scene* createScene();
    virtual bool init();
    
    // Methods
    void configureView();
    void update(float f);
    void setBitMaskToSprites();
    void checkUserWin();
    void createMenu();
    void pigContact(Sprite *image, int position);
    void setSpritePositionAndScale(Sprite* image, float scale, float x, float y);
    
    void buildRectangleElement(Sprite* image, int size, int maskCollision, PhysicsMaterial physicsMaterial);
    void buildCircleElement(Sprite* image, int radius, int maskCollision, PhysicsMaterial physicsMaterial);
    void buildFlyingBird(bool last, float angle);
    
    // Actions
    bool onContactBegin(PhysicsContact& contact);
    
    // Callbacks
    void menuRankingCallback(Ref* pSender);
    void menuExitCallback(Ref* pSender);
    
    // Properties
    float initialTouchPos[2];
    float currentTouchPos[2];
    
    bool isTouchDown;
    bool isCorrect;
    bool shooted;
    bool contactOc;
    
    CREATE_FUNC(Level2);
};


#endif /* Level2_hpp */
