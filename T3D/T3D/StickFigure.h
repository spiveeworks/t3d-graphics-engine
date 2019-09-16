#pragma once
#include "gameobject.h"

namespace T3D {
	class StickFigure : public GameObject
	{
	public:
		StickFigure(T3DApplication *app, Material *mat);
		~StickFigure(void);

		GameObject *base;
		GameObject *arm1;
		GameObject *arm2;
		GameObject *baseJoint;
		GameObject *elbowJoint;
		GameObject *shadeJoint;
	};
}
