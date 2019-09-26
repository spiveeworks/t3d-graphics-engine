#pragma once
#include "Animation.h"
#include <vector>

namespace T3D {
	class Poses
	{
	public:
		Poses(Animation* _anim) { anim = _anim; }
		~Poses(void) {}

		enum Joint {
			PELVIS, // = 0
			LTHIGH,
			LCALF,
			RTHIGH,
			RCALF,
			COLLAR,
			LUPPERARM,
			LFOREARM,
			RUPPERARM,
			RFOREARM,
			HEAD, // = 10
			// NUMJOINTS = 11,
		};
		static constexpr unsigned NUMJOINTS = 11;

		Animation *anim;
		std::vector<Vector3> positions;
		typedef Vector3 Pose[NUMJOINTS];
		std::vector<Pose> poses;
		std::vector<float> times;

		static const Pose NEUTRAL;
		static const Pose WAVE[2];
	};
}
