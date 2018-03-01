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

	void update(float delta);

	void handleInput(float);
	void updateCamera(float);
	void updatePlayerAnim(float);

	Vec2 getPosition() const;
protected:
	Vec2 position;
	Vec2 velocity;
	Vec2 lastVel;
	int speed;
	int counter = 0;
	bool isMoving;
	bool isSprinting;
	Animate* anim;
	Animate* animR;
	Animate* runAnimR;
	Animate* runAnimL;
	Animate* idleR;
	Animate* idleL;

};


#endif
