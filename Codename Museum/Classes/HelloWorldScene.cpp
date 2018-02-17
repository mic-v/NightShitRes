#include "HelloWorldScene.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include "GameCamera.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	HelloWorld* layer = HelloWorld::create();


	//scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto bg = LayerColor::create(Color4B(200, 190, 150, 255));
	this->addChild(bg);


	player = new CPlayer(this);

	CAMERA->getCameraTarget()->setPosition(player->getPosition());
	this->addChild(CAMERA->getCameraTarget());
	
	spr = Sprite::create("silencedGun.png");
	spr->setPosition(Vec2(500, 500));
	spr->setRotation(15.f);
	this->addChild(spr);

	////Sprite* sprit = Sprite::create("Player.png");
	////PhysicsBody * body = PhysicsBody::createBox(spr->getContentSize());
	////body->setGravityEnable(true);
	////sprit->setPhysicsBody(body);
	//////sp
	//this->addChild(sprit);

	//Follow* camera = Follow::create(spr, Rect::ZERO);
	//this->runAction(camera);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
	this->runAction(CAMERA->getCamera());

	Enemy enemy1 = Enemy(this, Vec2(1200, 300), 10);
	enemies.push_back(enemy1);
	Enemy enemy2 = Enemy(this, Vec2(1200, 500), 10);
	enemies.push_back(enemy2);
	Enemy enemy3 = Enemy(this, Vec2(1200, 700), 10);
	enemies.push_back(enemy3);

	this->scheduleUpdate();
    return true;
}

void HelloWorld::update(float dt)
{
	player->update(dt);
	updateEnemies(dt);
	//auto catBask = 0x0001;
}

void HelloWorld::initCollisionCallback()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign the callback function
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBeginCallback, this);

	//Add the contact listener to the event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void HelloWorld::updateEnemies(float deltaTime)
{
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		//If the enemy should be dead, kill it
		if (enemies[i].getIfDead())
		{
			//Kill the enemy
			enemies[i].kill();

			//Erase the enemy from the vector
			enemies.erase(enemies.begin() + i);

			//Decrement the counter
			i--;
		}
	}
}

void HelloWorld::findAndHurtEnemy(Node * enemyNode)
{
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		//Compare the enemy's sprite node to the node passed in
		if (enemies[i].getAttachedSprite() == enemyNode)
		{
			//If we found the right enemy, call its damage function
			enemies[i].damage();
			cout << enemies[i].getHealth() << endl;

			//Leave this function immediately so we don't check the rest of the enemies and waste time
			return;
		}
	}
}

bool HelloWorld::onContactBeginCallback(PhysicsContact & contact)
{
	//Get the two nodes that took part in the collision
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	//Get the collision tags from the nodes
	int tagA = nodeA->getPhysicsBody()->getTag();
	int tagB = nodeB->getPhysicsBody()->getTag();

	//Check to ensure both nodes actually exist, just in case. If they didn't just return false
	if (nodeA && nodeB)
	{
		//Depending on which object was a enemy, if any, perform the required logic
		if (nodeA->getPhysicsBody()->getCollisionBitmask() == 1 && nodeB->getPhysicsBody()->getCollisionBitmask() == 2)
		{
			nodeB->runAction(RemoveSelf::create());
			findAndHurtEnemy(nodeA);
			return true;
		}
		else if (nodeB->getPhysicsBody()->getCollisionBitmask() == 1 && nodeA->getPhysicsBody()->getCollisionBitmask() == 2)
		{
			nodeA->runAction(RemoveSelf::create());
			findAndHurtEnemy(nodeB);
			return true;
		}
		else
		{
			return false;
		}
		//if (tagA == Enemy::getTag())
		//{
		//	//If the first object was an enemy and the second was an arrow
		//	if (tagB == Bullet::getTag())
		//	{
		//		//Delete the arrow immediately
		//		nodeB->runAction(RemoveSelf::create());

		//		//Figure out which enemy was hit, using the first object in the collision as reference, and hurt that enemy correctly
		//		findAndHurtEnemy(nodeA);

		//		//Return true since the collision was correct and we want these two objects to collide
		//		return true;
		//	}
		//}
		//else if (tagB == Enemy::getTag())
		//{
		//	//If the second object was an enemy and the first an arrow
		//	if (tagA == Bullet::getTag())
		//	{
		//		//Delete the arrow immediately
		//		nodeA->runAction(RemoveSelf::create());

		//		//Figure out which enemy was hit, using the second object in the collision as reference, and hurt that enemy correctly
		//		findAndHurtEnemy(nodeB);

		//		//Return true since the collision was correct and we want these two objects to collide
		//		return true;
		//	}
		//}
		//else
		//{
		//	//If it was another form of collision, just return false
		//	return false;
		//}
	}
	else
		return false; //If the nodes don't exist, just return false
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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
