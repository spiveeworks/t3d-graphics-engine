#pragma once
#include "gameobject.h"

namespace T3D {
	class CricketBat : public GameObject
	{
	public:
		CricketBat(T3DApplication *app, Material *mat);
		~CricketBat(void);

		GameObject *base;
		GameObject *arm1;
		GameObject *arm2;
		GameObject *baseJoint;
		GameObject *elbowJoint;
		GameObject *shadeJoint;
	};
}
