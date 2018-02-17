	#include "Weapon.h"

Weapon::Weapon()
{
	spr = nullptr;
	attachedScene = nullptr;
	attachedLayer = nullptr;

}

Weapon::Weapon(string txtFile)
{
	attachedLayer = nullptr;
	attachedScene = nullptr;
	spr = Sprite::create(txtFile);
}

Weapon::Weapon(Scene * attachedScene_, string txtFile)
{
	attachedScene = attachedScene_;
	attachedLayer = nullptr;
	spr = Sprite::create(txtFile);
}

Weapon::Weapon(Layer * attachedLayer_, string txtFile)
{
	attachedLayer = attachedLayer_;
	attachedScene = nullptr;
	spr = Sprite::create(txtFile);
}

Weapon::~Weapon()
{
	delete spr;
	delete attachedLayer;
	delete attachedScene;
}
