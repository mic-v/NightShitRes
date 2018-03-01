#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Item.h"
#include "cocos2d.h"
#include <string>

using std::string;
using namespace cocos2d;

class Weapon : public Item
{
public:
	Weapon();
	Weapon(string);
	Weapon(Scene*, string);
	Weapon(Layer*, string);
	virtual ~Weapon();
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
	void update(float);

private:
	float shotTimer;
	bool fired;
};

#endif
