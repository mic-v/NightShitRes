#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;

class Game : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void update(float deltaTime);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    

    // implement the "static create()" method manually
    CREATE_FUNC(Game);
private:
	Player * player;
	Sprite * spr;
	Camera * cam;
	DrawNode * line1;
	DrawNode * line2;
	Vec2 position;
	Vec2 mosPos;
	Vec2 origin;
};

#endif // __HELLOWORLD_SCENE_H__
