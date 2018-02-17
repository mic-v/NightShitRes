#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "Entity.h"
#include <string>

using std::string;

class Item : public Entity
{
public:
	Item();
	virtual ~Item();
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

	virtual void update()
	{

	}
protected:

};

#endif
