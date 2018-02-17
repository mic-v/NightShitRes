#include "Bullet.h"

Bullet::Bullet(Scene * scene, Vec2 position, Vec2 direction)
{
	spr = Sprite::create("bullet.png");

	spr->setAnchorPoint(Vec2(.5f, .5f));
	spr->setPosition(position);

	scene->addChild(spr);
	//Physiccs
	PhysicsBody* phys = PhysicsBody::createBox(spr->getContentSize());
	phys->setDynamic(true);
	phys->setRotationEnable(false);
	phys->setVelocity(1000 * direction.getNormalized());
	phys->setTag(2);
	phys->setCollisionBitmask(2);
	phys->setContactTestBitmask(true);

	spr->setPhysicsBody(phys);
	spr->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL));
}

Bullet::Bullet(Layer * layer, Vec2 position, Vec2 direction)
{
	spr = Sprite::create("bullet.png");
	
	spr->setAnchorPoint(Vec2(.5f, .5f));
	spr->setPosition(position);

	layer->addChild(spr);
	//Physiccs
	PhysicsBody* phys = PhysicsBody::createBox(spr->getContentSize());
	phys->setDynamic(true);
	phys->setRotationEnable(false);
	phys->setVelocity(1000 * direction.getNormalized());
	phys->setTag(2);
	phys->setCollisionBitmask(2);
	phys->setContactTestBitmask(true);

	spr->setPhysicsBody(phys);
	spr->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL));
}

int Bullet::getTag()
{
	return 1;
}
