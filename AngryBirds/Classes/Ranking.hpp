//
//  Ranking.hpp
//  AngryBirds-mobile
//
//  Created by Andrés on 27/5/18.
//

#ifndef Ranking_hpp
#define Ranking_hpp

#include <stdio.h>
#include "network/HttpClient.h"
#include <vector>
#include <string.h>

using namespace std;
using namespace cocos2d;
using namespace network;

class Ranking : public Scene {
private:
    Sprite* backgroundSprite;
    Sprite* settingsButton;
    Label* highScoreLabel1;
    Label* highScoreLabel2;
    
public:
    // Initialize
    static Scene* createScene();
    virtual bool init();
    
    vector<string> makesplit(string main, string separator);
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    CREATE_FUNC(Ranking);
};

#endif /* Ranking_hpp */
