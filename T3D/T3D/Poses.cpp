#include "StickFigure.h"
#include "T3DApplication.h"
#include "Capsule.h"
#include "Sphere.h"
#include "Animation.h"

namespace T3D {

	// double braces to initialize std::array for some reason
	const Poses::Pose Poses::REFERENCE = { {
		{ -1, 0, 1 },
		{ 0, 0, 0 },
		{ -1, 0, -1 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 2, 1 },
		{ 0, 0, 0 },
		{ 0, 0, -1 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
	} };
	const Poses::Pose Poses::CONJUGATOR = { {
		{ 1, 0, -1 },
		{ 1, 0, 1 },
		{ -1, 0, 1 },
		{ -1, 0, -1 },
		{ 0, 1, 1 },
		{ -1, 0, -1 },
		{ 0, 0, -1 },
		{ -1, 0, 1 },
		{ 0, 0, 1 },
		{ 0, 1, 1 },
	} };
	const Poses::Pose Poses::ZEROES = { {
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
	} };
	const Poses::Pose Poses::NEUTRAL = { {
		{ -0.4f, 0.9f, -0.5f },
		{ 0, 0.2f, 0 },
		{ -0.4f, 0.9f, -0.5f },
		{ 0, 0.2f, 0 },
		{ 0, 0, 0 },
		{ -1, 0.8f, 0 },
		{ 0, 0.2f, 0 },
		{ -1, 0.8f, 0 },
		{ 0, 0.2f, 0 },
		{ 0, 0, 0 },
	} };
	const Poses::Pose NEUTRAL_OLD = { {
		{ -0.1f, 0, 1.8f },
		{ 0, 0, 0.15f },
		{ 0.1f, 0, -1.8f },
		{ 0, 0, 0.15f },
		{ 0, 0, 0 },
		{ 0, 0, 1.8f },
		{ 0, 0, 0.2f },
		{ 0, 2, -1.8f },
		{ 0, 0, 0.2f },
		{ 0, 0, 0 },
	} };
}