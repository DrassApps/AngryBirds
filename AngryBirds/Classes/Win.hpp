//
//  Win.hpp
//  AngryBirds-mobile
//
//  Created by Andrés on 14/5/18.
//

#ifndef Win_hpp
#define Win_hpp

#include <stdio.h>

using namespace cocos2d;

class Win : public Scene {
private:
    Sprite* backgroundSprite;
    Label* scoreLabel;
    Label* congratulationsLabel;
    
public:
    // Initialize
    static Scene* createScene(int score);
    virtual bool init();
    
    CREATE_FUNC(Win);
};

#endif /* Win_hpp */
