#pragma once
#include "gameobject.h"
#include "Poses.h"

namespace T3D {
	class StickFigure : public GameObject
	{
	public:
		static const char* JOINT_NAMES[Poses::NUMJOINTS];

		StickFigure(T3DApplication *app, float limbLength, float limbRadius, float torsoLength, float torsoRadius, float collarWidth, float pelvisWidth, float headRadius, Material *mat, Transform *root);

		void setPose(Vector3 position, Vector3 orientation, const Poses::Pose pose);
		void appendPose(Animation *anim, Vector3 position, Vector3 orientation, const Poses::Pose pose, float time);
		void startAnimation(float time);

		float limbLength,
			limbRadius,
			torsoLength,
			torsoRadius,
			collarWidth,
			pelvisWidth,
			headRadius;

		GameObject *joints[Poses::NUMJOINTS];

		Animation *anim;
		Poses poses;
	};
}
