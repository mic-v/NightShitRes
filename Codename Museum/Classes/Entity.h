/*
* Entity
* Planning to add more virtual functions, item class should be empty from now
*/

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocos2d.h"
#include <string>
using namespace cocos2d;
using namespace std;



class Entity	
{
public:
	Entity() : spr(nullptr), body(nullptr), attachedScene(nullptr), attachedLayer(nullptr) {}
	virtual ~Entity() {}

	virtual Sprite* getAttachedSprite() const = 0;
	virtual Scene* getAttachedScene() const = 0;
	virtual Layer* getAttachedLayer() const = 0;
	virtual void update(float delta) = 0;
protected:
	Sprite* spr;
	PhysicsBody* body;
	Scene* attachedScene;
	Layer* attachedLayer;
};


#endif
