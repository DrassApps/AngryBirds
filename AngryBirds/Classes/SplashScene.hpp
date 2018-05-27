//
//  SplashScene.hpp
//  AngryBirds-mobile
//
//  Created by Andrés on 12/5/18.
//

#ifndef SplashScene_hpp
#define SplashScene_hpp

#include <stdio.h>

using namespace std;
using namespace cocos2d;

class SplashScene : public Scene {
private:
    Sprite* backgroundSprite;
    Sprite* playButton;
    Sprite* achieveButton;
    Sprite* settingsButton;
    
public:
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SplashScene);
};

#endif /* SplashScene_hpp */

