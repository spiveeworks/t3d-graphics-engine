#pragma once
#include "gameobject.h"
#include "Poses.h"

namespace T3D {
	class StickFigure : public GameObject
	{
	public:
		static const char* JOINT_NAMES[Poses::NUMJOINTS];

		StickFigure(T3DApplication *app, Material *mat, Transform *root, float _limbLength = 1.0f, float _limbRadius = 0.15f, float _torsoLength = 2.0f, float _torsoRadius = 0.2f, float _collarWidth = 0.05f, float _pelvisWidth = 0.05f, float _headRadius = 0.5f);

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
