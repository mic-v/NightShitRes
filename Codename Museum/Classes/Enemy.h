#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"
#include "cocos2d.h"

using namespace cocos2d;

class Enemy : public Character
{
public:
	Enemy();
	Enemy(Scene*, Vec2, int);
	Enemy(Layer*, Vec2, int);
	virtual ~Enemy();

	virtual Sprite * getAttachedSprite() const
	{
		return spr;
	}
	virtual Scene * getAttachedScene() const
	{
		return attachedScene;
	}

	virtual Layer * getAttachedLayer() const
	{
		return attachedLayer;
	}

	virtual void update(float delta)
	{

	}
	void damage();
	void kill();
	static int getTag();
	int getHealth();
	bool getIfDead();
private:

};

#endif // !_ENEMY_H_

