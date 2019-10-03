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
			LTHIGH,
			LCALF,
			RTHIGH,
			RCALF,
			COLLAR,
			LUPPERARM,
			LFOREARM,
			RUPPERARM,
			RFOREARM,
			HEAD, // = 9
			// NUMJOINTS = 10,
		};
		static constexpr unsigned NUMJOINTS = 10;

		// unused
		Animation *anim = NULL;

		typedef std::array<Vector3, NUMJOINTS> Pose;
		std::vector<Pose> poses;
		std::vector<Vector3> positions;
		std::vector<Vector3> orientations;
		std::vector<float> times;

		static const Pose NEUTRAL;
		static const Pose WAVE[2];
	};
}
