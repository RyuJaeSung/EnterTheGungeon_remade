#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__


namespace OBJ
{
	enum ID { DOOR , PLAYER, BULLET, GUN, MONSTER, MONSTERBULLET, MOUSE, ID_END};
	enum DEAD_OR_ALIVE { DEAD, ALIVE, END};
}	

namespace SCENE
{
	enum ID { SCENE_LOGO, SCENE_MENU, SCENE_STAGE, SCENE_ENDING, SCENE_END };
}

namespace STATE
{
	enum NOW { IDLE, WALK, ATTACK, TUMBLING, DEAD , END};
}

namespace GUN
{
	enum GUNSTATE { IDLE, RELORD, SHOT ,END};
}

namespace MONSTER
{
	enum POS { LEFT, RIGHT, IDLE, DEAD, END};
}

#endif // __ENUM_H__
