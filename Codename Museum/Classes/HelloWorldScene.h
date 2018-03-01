#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CPlayer.h"
#include "Bullet.h"
#include "Enemy.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
    static cocos2d::Scene* createScene();

    virtual bool init();

	void update(float dt);

	void initCollisionCallback();
	void updateEnemies(float deltaTime);
	void findAndHurtEnemy(Node* enemyNode); //Find which enemy matches the node returned by the collision callback. Hurt that enemy

	bool onContactBegin(PhysicsContact& contact);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	Point tileCoordForPosition(Point position)
	{
		int x = position.x / map->getTileSize().width;
		int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
		return Point(x, y);
	}
	Point PostionForTileCoord(Point position)
	{
		int x = position.x * map->getTileSize().width;
		int y = (map->getMapSize().height * map->getTileSize().height) - position.y * map->getTileSize().height;
		return Point(x, y);
	}
private:
	Sprite* spr;
	CPlayer* player;
	vector<Enemy> enemies;
	TMXTiledMap* map;
};

#endif // __HELLOWORLD_SCENE_H__
