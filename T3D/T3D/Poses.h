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

		static const Pose REFERENCE, CONJUGATOR, ZEROES, NEUTRAL;

		static Pose reflect(Pose base) {
			Pose result;
			result[LTHIGH] = base[RTHIGH];
			result[LCALF] = base[RCALF];
			result[RTHIGH] = base[LTHIGH];
			result[RCALF] = base[LCALF];
			result[COLLAR] = base[COLLAR];
			result[COLLAR].z *= -1;
			result[LUPPERARM] = base[RUPPERARM];
			result[LFOREARM] = base[RFOREARM];
			result[RUPPERARM] = base[LUPPERARM];
			result[RFOREARM] = base[LFOREARM];
			result[HEAD] = base[HEAD];
			result[HEAD].z *= -1;
			return result;
		}
	};
}
