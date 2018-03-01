#include "Weapon.h"
#include "Bullet.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
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

	DrawNode* node = DrawNode::create();
	if (pressed && shotTimer == 0)
	{

		Vec2 position_ = CAMERA->getCameraTarget()->convertToWorldSpace(spr->getPosition()) + CAMERA->getOrigin() - (CAMERA->getOrigin() + Vec2(DISPLAY->getWindowSizeAsVec2().x * 0.5f, DISPLAY->getWindowSizeAsVec2().y * 0.5f) - CAMERA->getScreenMouse()) / 4.f;
		Vec2 direction = CAMERA->getScreenMouse() - (CAMERA->getOrigin() + Vec2(DISPLAY->getWindowSizeAsVec2().x * 0.5f, DISPLAY->getWindowSizeAsVec2().y * 0.5f));
		position_ = (CAMERA->getOrigin() + Vec2(DISPLAY->getWindowSizeAsVec2().x * 0.5f, DISPLAY->getWindowSizeAsVec2().y * 0.5f)) + position_.getNormalized() + direction.getNormalized() * 60.f;
		Bullet bullet(attachedLayer, position_, direction);
		fired = true;
	}
	//Vec2 test = CAMERA->getCameraTarget()->convertToWorldSpace(spr->getPosition());
	//node->drawLine(Vec2(0, 0), test, Color4F(1.0f, 0.f, 0.f, 1.f));
	//attachedLayer->addChild(node);

	if (fired)
	{
		shotTimer += dt;
	}
	if (shotTimer > 0.5f)
	{
		shotTimer = 0;
		fired = false;
		//fired = false;
	}
}
