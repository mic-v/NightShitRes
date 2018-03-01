#include "CPlayer.h"
#include "GameCamera.h"
#include "Bullet.h"
#include "InputHandler.h"
#include "DisplayHandler.h"

CPlayer::CPlayer()
{
	spr = nullptr;
	attachedScene = nullptr;
	attachedLayer = nullptr;
	cWeapNum = 0;
	speed = 0;
}

CPlayer::CPlayer(Scene * attachedScene_)
{
	attachedScene = attachedScene_;

	/*SET UP ANIMATIONS*/
	FileUtils::getInstance()->addSearchResolutionsOrder("HDR");
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/HDR/player.plist");


	spr = Sprite::createWithSpriteFrameName("idle.png");
	position = Vec2(1792.0f / 2, 1008.0f / 2);
	spr->setPosition(position);

	Vector<SpriteFrame*> frames;
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
	idleR = Animate::create(idleanim);
	idleR->retain();
	spr->runAction(RepeatForever::create(idleR));

	/* SETUP GUN */
	Weapon * gun = new Weapon("silencedGun.png");
	spr->addChild(gun->getAttachedSprite(), 1032);
	gun->getAttachedSprite()->setPosition(Vec2(spr->getContentSize().width * 0.5f, spr->getContentSize().height * 0.5f + 10));
	gun->getAttachedSprite()->setAnchorPoint(Point(-0.65, 0.5));
	weapons.push_back(gun);

	/* SETUP PHYSICS BODY */
	body = PhysicsBody::createBox(spr->getContentSize());
	body->setDynamic(false);
	body->setRotationEnable(false);
	spr->setPhysicsBody(body);


	cWeapNum = 0;
	speed = 0;
	isMoving = false;
	isSprinting = false;

	attachedScene_->addChild(spr, 1031);

}

CPlayer::CPlayer(Layer * attachedLayer_)
{
	attachedLayer = attachedLayer_;

	/*SET UP ANIMATIONS*/
	FileUtils::getInstance()->addSearchResolutionsOrder("HDR");
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/HDR/player.plist");


	spr = Sprite::createWithSpriteFrameName("idle.png");
	position = Vec2(1792.0f / 2, 1008.0f / 2);
	spr->setPosition(position);

	Vector<SpriteFrame*> frames;
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
	animation = Animation::createWithSpriteFrames(framesRight, 0.09f);
	animR = Animate::create(animation);
	animR->retain();

	Vector<SpriteFrame*> framesRunRight;
	for (int i = 0; i < 4; i++)
	{
		stringstream ss;
		ss << "rframe-r-00" << i + 1 << ".png";
		framesRunRight.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	animation = Animation::createWithSpriteFrames(framesRunRight, 0.09f);
	runAnimR = Animate::create(animation);
	runAnimR->retain();

	Vector<SpriteFrame*> framesRunLeft;
	for (int i = 0; i < 8; i++)
	{
		stringstream ss;
		ss << "runframe-l-00" << i + 1 << ".png";
		framesRunLeft.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	animation = Animation::createWithSpriteFrames(framesRunLeft, 0.09f);
	runAnimL = Animate::create(animation);
	runAnimL->retain();

	Vector<SpriteFrame*> idleright;
	for (int i = 0; i < 1; i++)
	{
		stringstream ss;
		ss << "idle.png";
		idleright.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	animation = Animation::createWithSpriteFrames(idleright, 0.09f);
	idleR = Animate::create(animation);
	idleR->retain();
	//spr->runAction(RepeatForever::create(idleR));



	Vector<SpriteFrame*> idleleft;
	for (int i = 0; i < 1; i++)
	{
		stringstream ss;
		ss << "idleleft.png";
		idleleft.pushBack(spritecache->getSpriteFrameByName(ss.str()));
	}
	animation = Animation::createWithSpriteFrames(idleleft, 0.09f);
	idleL = Animate::create(animation);
	idleL->retain();
	spr->runAction(RepeatForever::create(idleL));

	/* SETUP GUN */
	Weapon * gun = new Weapon(attachedLayer, "silencedGun.png");
	spr->addChild(gun->getAttachedSprite(), 2);
	gun->getAttachedSprite()->setPosition(Vec2(spr->getContentSize().width * 0.5f, spr->getContentSize().height * 0.5f + 10));
	gun->getAttachedSprite()->setAnchorPoint(Point(-0.57, 0.5));
	weapons.push_back(gun);

	/* SETUP PHYSICS BODY */
	body = PhysicsBody::createBox(spr->getContentSize());
	body->setDynamic(false);
	body->setRotationEnable(false);
	spr->setPhysicsBody(body);


	cWeapNum = 0;
	speed = 0;
	velocity = Vec2(0, 0);
	isMoving = false;

	attachedLayer_->addChild(spr, 1);
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
	updatePlayerAnim(delta);
	weapons[cWeapNum]->update(delta);
}

void CPlayer::handleInput(float delta)
{

	velocity = Vec2(0, 0);
	isMoving = false;
	isSprinting = false;


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
		if (INPUTS->getKey(KeyCode::KEY_SHIFT))
		{
			isSprinting = true;
		}
	}


	if (isMoving)
	{
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

		if (speed > MAXACCEL && !isSprinting)
		{
			speed -= 20.f;
		}
		else if (isSprinting && speed < MAXRUNACCEL)
		{
			speed += 20.f;
		}
		else if(speed < MAXACCEL)
		{
			speed += 20.f;
		}
		lastVel = velocity;
		
	}

	if (!isMoving)
	{
		if (speed > 0)
		{
			speed -= 20.f;
		}
		else
		{
			speed = 0.f;
			lastVel = Vec2(0, 0);
		}
	}


	position = position + speed * velocity.getNormalized() * delta;
	if (!isMoving)
	{
		position = position + speed * lastVel.getNormalized() * delta;
	}
	spr->setPosition(position);

	//DrawNode* node = DrawNode::create();
	//Vec2 test = CAMERA->getCameraTarget()->convertToWorldSpace(weapons[cWeapNum]->getAttachedSprite()->getPosition()) + CAMERA->getOrigin() - (CAMERA->getOrigin() + Vec2(DISPLAY->getWindowSizeAsVec2().x * 0.5f, DISPLAY->getWindowSizeAsVec2().y * 0.5f) - CAMERA->getScreenMouse()) / 4.f;
	//Vec2 direction = CAMERA->getScreenMouse() - (CAMERA->getOrigin() + Vec2(DISPLAY->getWindowSizeAsVec2().x * 0.5f, DISPLAY->getWindowSizeAsVec2().y * 0.5f));
	//test = (CAMERA->getOrigin() + Vec2(DISPLAY->getWindowSizeAsVec2().x * 0.5f, DISPLAY->getWindowSizeAsVec2().y * 0.5f)) + test.getNormalized() + direction.getNormalized() * 50;
	//node->drawLine(Vec2(0, 0), test, Color4F(0.f, 1.f, 0.f, 1.f));
	//attachedLayer->addChild(node);
	//bool pressed = INPUTS->getMouseButtonPress(MouseButton::BUTTON_LEFT);
	//if (pressed)
	//{
	//	Vec2 position_ = spr->convertToWorldSpace(weapons[cWeapNum]->getAttachedSprite()->getPosition()) + CAMERA->getOrigin() - (position - CAMERA->getScreenMouse()) / 4.f ;
	//	Vec2 direction = CAMERA->getScreenMouse() - this->position;
	//	position_ = this->position + position_.getNormalized() + direction.getNormalized() * 100.f;
	//	Bullet bullet(attachedLayer, position_, CAMERA->getScreenMouse() - this->position);
	//}
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

void CPlayer::updatePlayerAnim(float delta)
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
			if (isSprinting)
				spr->runAction(RepeatForever::create(runAnimL));
			else
				spr->runAction(RepeatForever::create(anim));
		}
		else
		{
			spr->stopAllActions();
			spr->runAction(RepeatForever::create(idleL));
		}
	}
	else
	{
		weapons[cWeapNum]->getAttachedSprite()->setScaleX(1.f);
		if (isMoving)
		{
			if (isSprinting)
				spr->runAction(RepeatForever::create(runAnimR));
			else
				spr->runAction(RepeatForever::create(animR));
		}
		else
		{
			spr->stopAllActions();
			spr->runAction(RepeatForever::create(idleR));
		}
	}

	weapons[cWeapNum]->getAttachedSprite()->setRotation(rot_);
}


Vec2 CPlayer::getPosition() const
{
	return position;
}
