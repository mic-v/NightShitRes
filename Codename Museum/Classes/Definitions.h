#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_s

#include "cocos2d.h"
using namespace cocos2d;

#define UP Vec2(0,1);
#define DOWN Vec2(0,-1);
#define LEFT Vec2(-1,0);
#define RIGHT Vec2(1,0);

#define MAXACCEL 400
#define MAXRUNACCEL 600

#define PLAYERMASK 0x0001
#define ENEMYMASK 0x0002
#define PLAYERBULLETS 0x0004
#define ENEMYBULLETS 0x0008
#define BOUNDARY 0x0016


#endif   // !1

