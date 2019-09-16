#pragma once
#include "gameobject.h"

namespace T3D {
	class StickFigure : public GameObject
	{
	public:
		StickFigure(T3DApplication *app, float limbLength, float limbRadius, float torsoLength, float torsoRadius, float collarWidth, float pelvisWidth, float headRadius, Material *mat);
		~StickFigure(void);

		GameObject *leftThigh;
		GameObject *leftCalf;
		GameObject *rightThigh;
		GameObject *rightCalf;
		GameObject *collarJoint;
		GameObject *leftUpperArm;
		GameObject *leftForeArm;
		GameObject *rightUpperArm;
		GameObject *rightForeArm;
		GameObject *head;
	};
}
