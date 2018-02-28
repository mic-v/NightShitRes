#ifndef _CHARACTER_H_
#define _CHARACTER_H_

/*
 * Character
 * Planning to make two more derived classes from Character: Player and Enemies, let me know what you think
*/

#include "Entity.h"
#include "Weapon.h"
using namespace cocos2d;
using std::string;

class Character : public Entity
{
public:
	Character();
	virtual ~Character();

	Sprite * getAttachedSprite() const
	{
		return spr;
	}
	Scene * getAttachedScene() const
	{
		return attachedScene;
	}

	Layer * getAttachedLayer() const
	{
		return attachedLayer;
	}

	virtual void update(float delta)
	{

	}

protected:
	int health;
	vector<Weapon*> weapons;

	//This is used as the parent, we will add the gun
	Sprite* gunHolder;

	//Current Weapon Num
	unsigned int cWeapNum;
};

#endif