#include "Player.h"

Player::Player() : UP(0.f, 1.f), DOWN(0.f, -1.f), LEFT(-1.f, 0.f), RIGHT(1.f, 0.f)
{
	position = Vec2(100, 100);
	speed = 0;
	maxSpeed = 400;
	velocity = 0;
}

Player::Player(Scene * scene) : UP(0.f,1.f), DOWN(0.f,-1.f), LEFT(-1.f,0.f), RIGHT(1.f,0.f)
{
	/*node = DrawNode::create();
	node->drawSolidRect(Vec2(0, 0), Vec2(100, 100), Color4F(0.f, 50.f, 0.f, 1.f));*/
	//node->setPosition(position);

	//spr->
	spr = Sprite::create("player1.png");

	position = Vec2(1792.0f / 2 , 1008.0f / 2);
	speed = 0;
	maxSpeed = 400;
	scene->addChild(spr,1020);
}

Player::Player(Layer * layer) : UP(0.f, 1.f), DOWN(0.f, -1.f), LEFT(-1.f, 0.f), RIGHT(1.f, 0.f)
{
	spr = Sprite::create("player1.png");

	position = Vec2(1792.0f / 2, 1008.0f / 2);
	speed = 0;
	maxSpeed = 400;
	layer->addChild(spr, 1020);
}

Player::~Player()
{
}

void Player::handleInput(float delta)
{
	bool isMoving = false;
	if (INPUTS->getKey(KeyCode::KEY_A) || INPUTS->getKey(KeyCode::KEY_D) || INPUTS->getKey(KeyCode::KEY_W) || INPUTS->getKey(KeyCode::KEY_S))
	{
		isMoving = true;
	}

	velocity = Vec2(0, 0);

	if (isMoving)
	{
		speed = maxSpeed;
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
	}
	else
		speed = 0;
	//cout << velocity.x << " " << velocity.y << endl;
	position = position + speed * velocity.getNormalized() * delta;


	//node->setPosition(position);
	spr->setPosition(position);
}

Vec2 Player::getPosition()
{
	return position;
}
