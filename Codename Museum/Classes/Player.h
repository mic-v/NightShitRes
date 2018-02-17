/*
 * This was just a test for player, will replace in the future different from the Entity Hierarchy
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "DisplayHandler.h"
#include "InputHandler.h"
#include <iostream>
using namespace cocos2d;
using namespace std;
class Player
{
public:
	Player();
	Player(Scene*);
	Player(Layer*);
	virtual ~Player();
	void handleInput(float delta);
	Vec2 getPosition();
private:
	Sprite *spr;
	DrawNode * node;
	Vec2 position;
	Vec2 velocity;
	const Vec2 UP;
	const Vec2 DOWN;
	const Vec2 LEFT;
	const Vec2 RIGHT;
	int maxSpeed;
	int speed;
};
#endif
