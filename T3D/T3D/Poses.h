#pragma once
#include "Animation.h"
#include <vector>
#include <array>

namespace T3D {
	class Poses
	{
	public:
		Poses() {}
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

		// unused
		Animation *anim = NULL;

		typedef std::array<Vector3, NUMJOINTS> Pose;
		std::vector<Pose> poses;
		std::vector<Vector3> positions;
		std::vector<float> times;

		static const Pose NEUTRAL;
		static const Pose WAVE[2];
	};
}
