
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

Scene* Game::createScene()
{
	Scene* scene = Scene::createWithPhysics();
	Game* layer = Game::create();
	scene->addChild(layer);
	return scene;
	//return Game::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();	
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));

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

    // add "Game" splash screen"
    auto sprite = Sprite::create("Game.png");
    if (sprite == nullptr)
    {
        problemLoading("'Game.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
	spr = Sprite::create("Player.png");
	this->addChild(spr);
	
	player = new Player(this);
	
	cam = Camera::createPerspective(60, Director::getInstance()->getWinSizeInPixels().width / Director::getInstance()->getWinSizeInPixels().height, -5000, 5000);
	cam->setPosition(Vec2(500, 500));
	cam->setCameraFlag(CameraFlag::USER1);
	this->addChild(cam);


	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	line1 = DrawNode::create();
	origin = player->getPosition();
	position = Vec2(0, 0);
	line1->drawLine(Vec2(0, 0), position, Color4F(50.0, 0.f, 0.f, 1.f));
	this->addChild(line1,5000);
	this->scheduleUpdate();

    return true;
}

void Game::menuCloseCallback(Ref* pSender)
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

void Game::update(float deltaTime)
{
	player->handleInput(deltaTime);
	origin = player->getPosition() - Vec2(1792*0.5f, 1008 * 0.5f);
	//mouse.y -= 1008.f;
	Vec2 screenMos = origin + INPUTS->getMousePosition();
	//line1->drawLine(Vec2(0,0), screenMos, Color4F(1.f, 0.f, 0.f, 1.f));
	Vec2 cameraPos = player->getPosition() - (player->getPosition() - screenMos) / 4.f;
	screenMos -= (player->getPosition() - screenMos) / 4.f;
	line1->drawLine(Vec2(0, 0), screenMos, Color4F(1.f, 0.f, 0.f, 1.f));
	cam->setPosition(cameraPos);
	//if (inputs->getkeypress(keycode::key_x))
	//{
	//	cam->setposition(player->getposition());
	//}

	//Vec2 mosPos = INPUTS->getMousePosition() + (INPUTS->getMousePosition() - player->getPosition()) / 2;
	//Vec2 mosPos = INPUTS->getMousePosition() /2 ;
	//Vec2 mosPos = Vec2((player->getPosition().x + INPUTS->getMousePosition().x) / 2, (player->getPosition().y + INPUTS->getMousePosition().y) / 2);
	
	//Vec2 mosPos;
	//Vec2 mosPos2 = cam->convertToWorldSpace(INPUTS->getMousePosition());
	//mosPos.x = player->getPosition().x + (mosPos2.x - player->getPosition().x) / 4;
	//mosPos.y = player->getPosition().y + (mosPos2.y - player->getPosition().y) / 4;
	/*float x = (INPUTS->getMousePosition().x + player->getPosition().x + player->getPosition().x + player->getPosition().x) / 4.f;
	float y = (INPUTS->getMousePosition().y + player->getPosition().y + player->getPosition().y + player->getPosition().y) / 4.f;
	Vec2 mosPos(x, y);*/
	//Vec2 vec = player->getPosition();
	//Vec2 vec2 = cam->convertToWorldSpace(INPUTS->getMousePosition());
	//float x = (vec.x + vec.x + vec.x + vec2.x) / 4.f;
	//	float y = (vec.y + vec.y + vec.y + vec2.y) / 4.f;
	//Vec2 mosPos(x, y);
	//Vec2 mosPos;
	//Vec2 vec2 = cam->convertToWorldSpace(INPUTS->getMousePosition());
	//mosPos.x = player->getPosition().x - ((player->getPosition().x - vec2.x) / 4);
	//mosPos.y = player->getPosition().y - ((player->getPosition().y - vec2.y) / 4);

	//cam->converto
	//mosPos.x = (player->getPosition().x * 5 + INPUTS->getMousePosition().x * 2) / 7;
	//mosPos.y = (player->getPosition().y * 5 + INPUTS->getMousePosition().y * 2) / 7;
	//float maxScreenPoint = 0.8f;
	//Vec3 screenSize(DISPLAY->getWindowSizeAsVec2().x, DISPLAY->getWindowSizeAsVec2().y, 0.0f);
	//Vec3 mousePos(INPUTS->getMousePosition().x, INPUTS->getMousePosition().y, 0.0f);
	//Vec3 mosPos = mousePos * maxScreenPoint + screenSize * ((1. - maxScreenPoint) * 0.5f);
	//Vec2 convert = cam->convertToWorldSpace(Vec2(mosPos.x,mosPos.y));
	//Vec3 convert3(convert.x, convert.y, 0.0f);
	//Vec3 playerPosition = (player->getPosition().x, player->getPosition().y, 0);
	//Vec3 position = (playerPosition + convert3) / 2;
	//cout << INPUTS->getMousePosition().x << " " << INPUTS->getMousePosition().y << endl;

	//1/31/2018
	/*Vec2 mosPos = cam->convertToWorldSpace(INPUTS->getMousePosition());
	Vec2 pos;
*/
	//float maxScreenPoint = 0.8f;
	//Vec2 mosPos = INPUTS->getMousePosition() * maxScreenPoint + DISPLAY->getWindowSizeAsVec2() * ((1.f - maxScreenPoint) * 0.5f);

	//line1->clear();

}
