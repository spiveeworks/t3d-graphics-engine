#pragma once
#include "gameobject.h"
#include "Poses.h"

namespace T3D {
	class StickFigure : public GameObject
	{
	public:
		StickFigure(T3DApplication *app, float limbLength, float limbRadius, float torsoLength, float torsoRadius, float collarWidth, float pelvisWidth, float headRadius, Material *mat);
		~StickFigure(void);

		void setPose(Vector3 position, const Poses::Pose);
		void appendPose(Animation *anim, Vector3 position, const Poses::Pose pose, float time);

		// unused I believe
		float limbLength,
			limbRadius,
			torsoLength,
			torsoRadius,
			collarWidth,
			pelvisWidth,
			headRadius;

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
