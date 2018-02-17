#ifndef __MAINSCENE_SCENE_H__
#define __MAINSCENE_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
//#include "Item.h"

class MainScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(MainScene);
	// implement the "static create()" method manually
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
private:
	GameLayer* gameLayer;
	Layer* layer;

	static PhysicsWorld* physicsWorld;

	static Scene* sceneHandle;
};

#endif // __HELLOWORLD_SCENE_H__
