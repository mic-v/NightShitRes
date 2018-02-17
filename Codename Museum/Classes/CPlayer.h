#ifndef _CPLAYER_H_
#define _CPLAYER_H_


#include "Character.h"
#include "Definitions.h"
#include "cocos2d.h"

using namespace cocos2d;

class CPlayer : public Character
{
public:
	CPlayer();
	CPlayer(Scene*);
	CPlayer(Layer*);
	virtual ~CPlayer();

	virtual Sprite* getAttachedSprite() const
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

	virtual void update(float delta);

	void handleInput(float);
	void updateCamera(float);
	void updateGunPosition();

	Vec2 getPosition() const;
protected:
	Vec2 position;
	Vec2 velocity;
	int speed;
	int counter = 0;
	bool isMoving;
	Animate* anim;
	Animate* animR;
	Animate* idle;
	Vector<SpriteFrame*> frames;
};


#endif
