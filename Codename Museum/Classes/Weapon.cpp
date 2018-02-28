#include "Weapon.h"
#include "Bullet.h"
#include "InputHandler.h"
#include "GameCamera.h"

Weapon::Weapon()
{
	spr = nullptr;
	attachedScene = nullptr;
	attachedLayer = nullptr;
	fired = false;
	shotTimer = 0.f;
}

Weapon::Weapon(string txtFile)
{
	attachedLayer = nullptr;
	attachedScene = nullptr;
	shotTimer = 0.f;
	fired = false;
	spr = Sprite::create(txtFile);
}

Weapon::Weapon(Scene * attachedScene_, string txtFile)
{
	attachedScene = attachedScene_;
	attachedLayer = nullptr;
	shotTimer = 0.f;
	fired = false;
	spr = Sprite::create(txtFile);
}

Weapon::Weapon(Layer * attachedLayer_, string txtFile)
{
	attachedLayer = attachedLayer_;
	attachedScene = nullptr;
	shotTimer = 0.f;
	fired = false;
	spr = Sprite::create(txtFile);
}

Weapon::~Weapon()
{
	delete spr;
	delete attachedLayer;
	delete attachedScene;
}

void Weapon::update(float dt)
{
	bool pressed = INPUTS->getMouseButtonPress(MouseButton::BUTTON_LEFT);
	if (pressed && shotTimer == 0)
	{
		Vec2 position_ = spr->convertToWorldSpace(spr->getPosition()) + CAMERA->getOrigin() - (spr->convertToWorldSpace(spr->getPosition()) - CAMERA->getScreenMouse()) / 4.f;
		Vec2 direction = CAMERA->getScreenMouse() - spr->convertToWorldSpace(spr->getPosition());
		position_ = spr->convertToWorldSpace(spr->getPosition()) + position_.getNormalized() + direction.getNormalized() * 100.f;
		Bullet bullet(attachedLayer, position_, CAMERA->getScreenMouse() - spr->convertToWorldSpace(spr->getPosition()));
		fired = true;
		std::cout << "fire " << std::endl;
	}
	if (fired)
	{
		shotTimer += dt;
	}
	std::cout << shotTimer << std::endl;
	if (shotTimer > 0.5f)
	{
		shotTimer = 0;
		fired = false;
		//fired = false;
	}
}
