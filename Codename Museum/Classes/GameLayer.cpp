#include "GameLayer.h"
#include "GameCamera.h"
#include "DisplayHandler.h"
#include "InputHandler.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

cocos2d::Scene * GameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();
	// add layer as a child to scene
	scene->addChild(layer,50);

	// return the scene
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	director = Director::getInstance();
	auto bg = LayerColor::create(Color4B(200, 190, 150, 255));
	this->addChild(bg);
	//this->setColor(Color3B(200.f, 190.f, 156.f));
	//director->setClearColor(Color4F(10.f, 190.f, 156.f, 1.f));

	cplayer = new CPlayer(this);

	CAMERA->getCameraTarget()->setPosition(cplayer->getPosition());
	this->addChild(CAMERA->getCameraTarget());
	
	//cameraTarget = Sprite::create();
	//cameraTarget->setPositionX(cplayer->getPosition().x);
	//cameraTarget->setPositionY(cplayer->getPosition().y);
	//cameraTarget->retain();
	//this->addChild(cameraTarget);

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));
		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	//node = DrawNode::create();
	//node->drawLine(Vec2(0, 0), cplayer->getPosition(), Color4F(66.f, 66.f, 0.f, 1.f));
	//this->addChild(node);

	this->runAction(CAMERA->getCamera());
	//Follow* camera = Follow::create(cameraTarget, Rect::ZERO);
	//this->runAction(camera);

	this->scheduleUpdate();
	return true;
}

void GameLayer::update(float dt)
{
	cplayer->handleInput(dt);
	//CAMERA->updateCamera(cplayer);
	//camera->updateCamera(cplayer);
	//updateCamera(dt);
//	node->clear();
}

void GameLayer::updateCamera(float dt)
{
	//Vec2 origin(0, 0);
	//origin = cplayer->getPosition() - Vec2(1792 * 0.5f, 1008 * 0.5f);
	//Vec2 screenMos = origin + INPUTS->getMousePosition();
	//Vec2 cameraPos = cplayer->getPosition() - (cplayer->getPosition() - screenMos) / 4.f;
	//screenMos -= (cplayer->getPosition() - screenMos) / 4.f;
	//Vec2 angleVec = screenMos - cplayer->getPosition();
	////float agle = Vec2::angle(Vec2(1, 0), angleVec.getNormalized()) * (180.f / M_PI) - 90.0f;
	//float agle = Vec2::angle(Vec2(1, 0), INPUTS->getMousePosition()) * (180.f / M_PI);
	//cout << agle << endl;
	//cplayer->updateGunPosition(agle);
	//cameraTarget->setPosition(cameraPos);
}

void GameLayer::menuCloseCallback(cocos2d::Ref * pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}
