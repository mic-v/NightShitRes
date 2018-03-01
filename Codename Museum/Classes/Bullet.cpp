#include "Bullet.h"

Bullet::Bullet(Scene * scene, Vec2 position, Vec2 direction)
{
	Sprite* sprite = Sprite::create("bullet.png");

	sprite->setAnchorPoint(Vec2(.5f, .5f));
	sprite->setPosition(position);

	//Physiccs
	body = PhysicsBody::createBox(spr->getContentSize());
	body->setDynamic(true);
	body->setRotationEnable(false);
	body->setGravityEnable(false);
	body->setVelocity(100 * direction.getNormalized());
	body->setTag(2);
	//body->setCollisionBitmask(2);
	body->setContactTestBitmask(true);
	sprite->setPhysicsBody(body);

	sprite->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL));

	scene->addChild(sprite);

	spr = sprite;
}

Bullet::Bullet(Layer * layer, Vec2 position, Vec2 direction)
{
	Sprite* sprite = Sprite::create("0305Bullet.png");
	float rot_ = Vec2::angle(Vec2(0, 1), direction.getNormalized()) * (180.f / M_PI) - 90.f;
	sprite->setRotation(rot_);
	sprite->setAnchorPoint(Vec2(.5f, .5f));
	sprite->setPosition(position);

	layer->addChild(sprite, 2);
	//Physiccs
	body = PhysicsBody::createBox(sprite->getContentSize());
	body->setDynamic(true);
	body->setRotationEnable(true);
	//body->setCollisionBitmask(2);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setVelocity(1000 * direction.getNormalized());
	body->setTag(2);
	sprite->setPhysicsBody(body);

	sprite->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL));
	spr = sprite;
}

int Bullet::getTag()
{
	return 1;
}
