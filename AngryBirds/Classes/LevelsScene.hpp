//
//  LevelsScene.hpp
//  AngryBirds-mobile
//
//  Created by Andrés on 12/5/18.
//

#ifndef LevelsScene_hpp
#define LevelsScene_hpp

#include <stdio.h>

using namespace cocos2d;

class LevelsScene : public Scene {
private:
    Sprite* backgroundSprite;
    
public:
    // Initialize
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(LevelsScene);
};

#endif /* LevelsScene_hpp */
