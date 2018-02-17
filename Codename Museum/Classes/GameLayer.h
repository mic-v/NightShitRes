#ifndef __GAMELAYER_SCENE_H__
#define __GAMELAYER_SCENE_H__

#include "cocos2d.h"
#include "CPlayer.h"

class GameLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameLayer);
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float dt);
	void updateCamera(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
private:
	//Caocos Stuff
	Director * director;
	//
	CPlayer* cplayer;
};

#endif

