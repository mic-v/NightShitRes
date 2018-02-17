#include "MainMenu.h"

using namespace cocos2d;

cocos2d::Scene* MainMenu::createScene()
{
	//Create a scene without physics (we're implementing our own!)
	Scene* scene = Scene::create();

	//Create the main layer that is attached to the scene
	MainMenu* layer = MainMenu::create();

	//Add the layer to the scene
	scene->addChild(layer);

	//Return the newly built scene
	return scene;

}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

