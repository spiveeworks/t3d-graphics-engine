#pragma once
#include "gameobject.h"
#include "Poses.h"

namespace T3D {
	class StickFigure : public GameObject
	{
	public:
		StickFigure(T3DApplication *app, float limbLength, float limbRadius, float torsoLength, float torsoRadius, float collarWidth, float pelvisWidth, float headRadius, Material *mat, Transform *root);

		void setPose(Vector3 position, const Poses::Pose);
		void appendPose(Animation *anim, Vector3 position, const Poses::Pose pose, float time);
		void startAnimation(float time);

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

		Animation *anim;
		Poses poses;
	};
}
