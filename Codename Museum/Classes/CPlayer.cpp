#include "CPlayer.h"
#include "GameCamera.h"
#include "Bullet.h"
#include "InputHandler.h"

CPlayer::CPlayer()
{
	spr = nullptr;
	attachedScene = nullptr;
	attachedLayer = nullptr;
	cWeapNum = 0;
}

CPlayer::CPlayer(Scene * attachedScene_)
{
	attachedLayer = nullptr;
	attachedScene = attachedScene_;

	FileUtils::getInstance()->addSearchResolutionsOrder("HDR");

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("PlayerAnim/HDR/.plist");


	spr = Sprite::createWithSpriteFrameName("idle.png");
	position = Vec2(1792.0f / 2, 1008.0f / 2);
	spr->setPosition(position);


	for (int i = 0; i < 8; i++)
	{
		stringstream ss;
		ss << "frame-l-00" << i + 1 << ".png";
		frames.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	auto animation = Animation::createWithSpriteFrames(frames, 0.09f);
	anim = Animate::create(animation);
	anim->retain();

	Vector<SpriteFrame*> framesRight;
	for (int i = 0; i < 8; i++)
	{
		stringstream ss;
		ss << "frame-r-00" << i + 1 << ".png";
		framesRight.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	auto animationR = Animation::createWithSpriteFrames(framesRight, 0.09f);
	animR = Animate::create(animationR);
	animR->retain();

	Vector<SpriteFrame*> idleframes;
	for (int i = 0; i < 1; i++)
	{
		stringstream ss;
		ss << "idle.png";
		idleframes.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	auto idleanim = Animation::createWithSpriteFrames(idleframes, 0.09f);
	idle = Animate::create(idleanim);
	idle->retain();
	spr->runAction(RepeatForever::create(idle));

	PhysicsBody* spr_body = PhysicsBody::createBox(spr->getContentSize());
	spr_body->setDynamic(false);
	spr_body->setRotationEnable(false);
	spr->setPhysicsBody(spr_body);

	Weapon * gun = new Weapon("silencedGun.png");
	spr->addChild(gun->getAttachedSprite(), 1032);
	gun->getAttachedSprite()->setPosition(Vec2(spr->getContentSize().width * 0.5f, spr->getContentSize().height * 0.5f + 10));
	gun->getAttachedSprite()->setAnchorPoint(Point(-0.65, 0.5));
	weapons.push_back(gun);

	cWeapNum = 0;
	isMoving = false;

	attachedScene_->addChild(spr, 1031);

}

CPlayer::CPlayer(Layer * attachedLayer_)
{
	attachedLayer = attachedLayer_;
	attachedScene = nullptr;

	FileUtils::getInstance()->addSearchResolutionsOrder("HDR");

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("PlayerAnim/HDR/.plist");


	spr = Sprite::createWithSpriteFrameName("idle.png");
	position = Vec2(1792.0f / 2, 1008.0f / 2);
	spr->setPosition(position);


	for (int i = 0; i < 8; i++)
	{
		stringstream ss;
		ss << "frame-l-00" << i + 1 << ".png";
		frames.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	auto animation = Animation::createWithSpriteFrames(frames, 0.09f);
	anim = Animate::create(animation);
	anim->retain();

	Vector<SpriteFrame*> framesRight;
	for (int i = 0; i < 8; i++)
	{
		stringstream ss;
		ss << "frame-r-00" << i + 1 << ".png";
		framesRight.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	auto animationR = Animation::createWithSpriteFrames(framesRight, 0.09f);
	animR = Animate::create(animationR);
	animR->retain();

	Vector<SpriteFrame*> idleframes;
	for (int i = 0; i < 1; i++)
	{
		stringstream ss;
		ss << "idle.png";
		idleframes.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	auto idleanim = Animation::createWithSpriteFrames(idleframes, 0.09f);
	idle = Animate::create(idleanim);
	idle->retain();
	spr->runAction(RepeatForever::create(idle));

	PhysicsBody* spr_body = PhysicsBody::createBox(spr->getContentSize());
	spr_body->setDynamic(false);
	spr_body->setRotationEnable(false);
	spr->setPhysicsBody(spr_body);

	Weapon * gun = new Weapon("silencedGun.png");
	spr->addChild(gun->getAttachedSprite(), 1032);
	gun->getAttachedSprite()->setPosition(Vec2(spr->getContentSize().width * 0.5f, spr->getContentSize().height * 0.5f + 10));
	gun->getAttachedSprite()->setAnchorPoint(Point(-0.65, 0.5));
	weapons.push_back(gun);

	cWeapNum = 0;
	isMoving = false;

	attachedLayer_->addChild(spr, 1031);
}

CPlayer::~CPlayer()
{
	for (int i = 0; i < weapons.size(); ++i)
	{
		delete weapons[i];
	}
	weapons.clear();

	CC_SAFE_RELEASE(anim);
}

void CPlayer::update(float delta)
{
	handleInput(delta);
	updateCamera(delta);
	updateGunPosition();
}

void CPlayer::handleInput(float delta)
{
	//if (INPUTS->getKey(KeyCode::KEY_A))
	//{
	//	velocity += LEFT;
	//	isMoving = true;
	//}
	//if (INPUTS->getKey(KeyCode::KEY_D))
	//{
	//	velocity += RIGHT;
	//	isMoving = true;
	//}
	//if (INPUTS->getKey(KeyCode::KEY_W))
	//{
	//	velocity += UP;
	//	isMoving = true;
	//}
	//if (INPUTS->getKey(KeyCode::KEY_S))
	//{
	//	velocity += DOWN;
	//	isMoving = true;
	//}
	//if (isMoving = true)
	//{
	//	speed = MAXACCEL;
	//	spr->stopAllActions();
	//	spr->runAction(RepeatForever::create(anim));
	//}
	//if (isMoving = false)
	//{
	//	speed = 0;
	//	spr->stopAllActions();
	//	spr->runAction(RepeatForever::create(idle));
	//}
	//if (INPUTS->getKey(KeyCode::KEY_A) || INPUTS->getKey(KeyCode::KEY_D) || INPUTS->getKey(KeyCode::KEY_W) || INPUTS->getKey(KeyCode::KEY_S))
	//{
	//	isMoving = true;
	//}
	//

	//if (INPUTS->getKey(KeyCode::KEY_A) || INPUTS->getKey(KeyCode::KEY_D) || INPUTS->getKey(KeyCode::KEY_W) || INPUTS->getKey(KeyCode::KEY_S))
	//{
	//	isMoving = true;
	//	if (INPUTS->getKey(KeyCode::KEY_A))
	//	{
	//		velocity += LEFT;
	//	}
	//	if (INPUTS->getKey(KeyCode::KEY_D))
	//	{
	//		velocity += RIGHT;
	//	}
	//	if (INPUTS->getKey(KeyCode::KEY_W))
	//	{
	//		velocity += UP;
	//	}
	//	if (INPUTS->getKey(KeyCode::KEY_S))
	//	{
	//		velocity += DOWN;
	//	}
	//}
	//else
	//{
	//	isMoving = false;
	//}


	velocity = Vec2(0, 0);
	isMoving = false;

	if (INPUTS->getKey(KeyCode::KEY_A) || INPUTS->getKey(KeyCode::KEY_D) || INPUTS->getKey(KeyCode::KEY_W) || INPUTS->getKey(KeyCode::KEY_S))
	{
		isMoving = true;
		if (INPUTS->getKey(KeyCode::KEY_A) && INPUTS->getKey(KeyCode::KEY_D))
		{
			isMoving = false;
		}
		if (INPUTS->getKey(KeyCode::KEY_W) && INPUTS->getKey(KeyCode::KEY_S))
		{
			isMoving = false;
		}
	}

	if (isMoving)
	{
		speed = MAXACCEL;
		if (INPUTS->getKey(KeyCode::KEY_A))
		{
			velocity += LEFT;
		}
		if (INPUTS->getKey(KeyCode::KEY_D))
		{
			velocity += RIGHT;
		}
		if (INPUTS->getKey(KeyCode::KEY_W))
		{
			velocity += UP;
		}
		if (INPUTS->getKey(KeyCode::KEY_S))
		{
			velocity += DOWN;
		}
		/*spr->stopAllActions();
		spr->runAction(RepeatForever::create(anim));*/
	}
	else
	{
		speed = 0.f;
		spr->stopAllActions();
		spr->runAction(RepeatForever::create(idle));
	}

	//if (velocity.x == 0 && velocity.y)
	//{
	//	speed = 0.f;
	//	spr->stopAllActions();
	//	spr->runAction(RepeatForever::create(idle));
	//	isMoving = false;
	//}
	position = position + speed * velocity.getNormalized() * delta;
	spr->setPosition(position);

	bool pressed = INPUTS->getMouseButtonPress(MouseButton::BUTTON_LEFT);
	//cout << weapons[cWeapNum]->getAttachedSprite()->getPosition().x << " " << weapons[cWeapNum]->getAttachedSprite()->getPosition().y << endl;
	//cout << spr->getPosition().x  << " " << spr->getPosition().y << endl;
	//cout << spr->convertToWorldSpace(weapons[cWeapNum]->getAttachedSprite()->getPosition()).x + CAMERA->getOrigin().x - (position.x - CAMERA->getScreenMouse().x) /4.f << " " << spr->convertToWorldSpace(weapons[cWeapNum]->getAttachedSprite()->getPosition()).y + CAMERA->getOrigin().y + 0.5f * (spr->getContentSize().height * 0.5f) << endl;
	if (pressed)
	{
		//Vec2 position_ = attachedLayer->convertToWorldSpace(weapons[cWeapNum]->getAttachedSprite()->getPosition());
		Vec2 position_ = spr->convertToWorldSpace(weapons[cWeapNum]->getAttachedSprite()->getPosition()) + CAMERA->getOrigin() - (position - CAMERA->getScreenMouse()) / 4.f ;
		Bullet bullet(attachedLayer, position_, CAMERA->getScreenMouse() - this->position);
	}
}

void CPlayer::updateCamera(float delta)
{
	Vec2 origin = this->position - Vec2(1792 * 0.5f, 1008 * 0.5f);
	Vec2 screenMos = origin + INPUTS->getMousePosition();
	Vec2 camPos = this->position - (this->position - screenMos) / 4.f;
	screenMos -= (this->position - screenMos) / 4.f;

	//float lerp = 0.1f;
	//camPos.x += (this->position.x - camPos.x) / 100.f;
	//camPos.y += (this->position.y - camPos.y) / 100.f;

	CAMERA->setOrigin(origin);
	CAMERA->setScreenMouse(screenMos);
	CAMERA->setCameraPosition(camPos);
	CAMERA->getCameraTarget()->setPosition(camPos);
}

void CPlayer::updateGunPosition()
{
	Vec2 angleVec = CAMERA->getScreenMouse() - position;
	float rot_ = Vec2::angle(Vec2(0, 1), angleVec.getNormalized()) * (180.f / M_PI) - 90.f;
	
	//cout << velocity.x << " " << velocity.y << endl;

	if (CAMERA->getScreenMouse().x < position.x)
	{
		weapons[cWeapNum]->getAttachedSprite()->setScaleX(-1.f);
		rot_ = 360 - rot_;
		if (isMoving)
		{
			spr->runAction(RepeatForever::create(anim));
		}
	}
	else
	{
		weapons[cWeapNum]->getAttachedSprite()->setScaleX(1.f);
		if (isMoving)
		{
			spr->runAction(RepeatForever::create(animR));
		}
	}

	weapons[cWeapNum]->getAttachedSprite()->setRotation(rot_);
}


Vec2 CPlayer::getPosition() const
{
	return position;
}
