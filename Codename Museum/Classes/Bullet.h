#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"

using namespace cocos2d;

class Bullet : public Entity
{
public:
	Bullet(Scene*, Vec2, Vec2);
	Bullet(Layer*, Vec2, Vec2);
	virtual Sprite* getAttachedSprite() const
	{
		return spr;
	}
	virtual Scene* getAttachedScene() const
	{
		return attachedScene;
	}
	virtual Layer* getAttachedLayer() const
	{
		return attachedLayer;
	}
	virtual void update(float delta)
	{

	}

	static int getTag();
private:
	
};

#endif // !_BULLET_H_

