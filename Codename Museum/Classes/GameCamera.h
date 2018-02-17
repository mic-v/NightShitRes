#ifndef CAMERA_H_
#define CAMERA_H_

#include "cocos2d.h";
#include <iostream>

using namespace cocos2d;
using namespace std;

class GameCamera
{
protected:
	GameCamera();
public:
	~GameCamera();

	//Get the Camera
	static GameCamera* getInstance();

	//Get the target the Camera is following
	Follow* getCamera();

	Sprite* getCameraTarget();

	void init();

	//GETTERS//
	Vec2 getOrigin() const;
	Vec2 getScreenMouse() const;
	Vec2 getCameraPosition() const;

	//SETTERS//
	void setOrigin(Vec2);
	void setScreenMouse(Vec2);
	void setCameraPosition(Vec2);

	//void updateCamera(CPlayer *);

private:
	bool hasBeenInit;

	static GameCamera* inst;
	Follow* camera;
	Sprite* cameraTarget;

	Vec2 origin;
	Vec2 screenMos;
	Vec2 camPos;
};

#define CAMERA GameCamera::getInstance()

#endif