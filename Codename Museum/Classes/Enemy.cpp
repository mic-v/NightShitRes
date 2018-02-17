#include "Enemy.h"

Enemy::Enemy()
{
	spr = nullptr;
}

Enemy::Enemy(Scene * attachedScene_, Vec2 postion_, int health_)
{
	health = health_;
	attachedScene = attachedScene_;
	spr = Sprite::create("enemy1.png");
	spr->setPosition(postion_);
	spr->setAnchorPoint(Vec2(0.5f, 0.5f));

	PhysicsBody* phys = PhysicsBody::createBox(spr->getContentSize());
	phys->setDynamic(false);
	phys->setTag(1);
	phys->setCollisionBitmask(1);
	phys->setContactTestBitmask(true);

	spr->setPhysicsBody(phys);
	attachedScene_->addChild(spr, 1031);
}

Enemy::Enemy(Layer * attachedLayer_, Vec2 postion_, int health_)
{
	health = health_;
	attachedLayer = attachedLayer_;
	spr = Sprite::create("enemy1.png");
	spr->setPosition(postion_);
	spr->setAnchorPoint(Vec2(0.5f, 0.5f));

	PhysicsBody* phys = PhysicsBody::createBox(spr->getContentSize());
	phys->setDynamic(false);
	phys->setTag(1);
	phys->setCollisionBitmask(1);
	phys->setContactTestBitmask(true);

	spr->setPhysicsBody(phys);
	attachedLayer_->addChild(spr, 1031);

}

Enemy::~Enemy()
{
	attachedScene = nullptr;
	attachedLayer = nullptr;
	spr = nullptr;
}

void Enemy::damage()
{
	health--;
}

void Enemy::kill()
{
	spr->runAction(RemoveSelf::create());
}

int Enemy::getTag()
{
	return 0;
}

int Enemy::getHealth()
{
	return health;
}

bool Enemy::getIfDead()
{
	return (health <= 0);
}
