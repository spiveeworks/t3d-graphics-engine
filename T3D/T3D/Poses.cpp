#include "StickFigure.h"
#include "T3DApplication.h"
#include "Capsule.h"
#include "Sphere.h"
#include "Animation.h"

namespace T3D {

	const Poses::Pose Poses::NEUTRAL = {
		{ 0, 0, 0 },
		{ 0, 0, 1.6f },
		{ 0, 0, 0.2f },
		{ 0, 0, -1.6f },
		{ 0, 0, -0.2f },
		{ 0, 0, 0 },
		{ 0, 0, 1.6f },
		{ 0, 0, 0.2f },
		{ 0, 0, -1.6f },
		{ 0, 0, -0.2f },
		{ 0, 0, 0 },
	};
	const Poses::Pose Poses::WAVE[2] = {
		{
			{ 0, 0, 0 },
			{ 0, 0, 1.6f },
			{ 0, 0, 0.2f },
			{ 0, 0, -1.6f },
			{ 0, 0, -0.2f },
			{ 0, 0, 0 },
			{ 0, 0, 1.1f },
			{ 0, 0, -0.6f },
			{ 0, 0, -1.6f },
			{ 0, 0, -0.2f },
			{ 0, 0, 0 },
		},
		{
			{ 0, 0, 0 },
			{ 0, 0, 1.6f },
			{ 0, 0, 0.2f },
			{ 0, 0, -1.6f },
			{ 0, 0, -0.2f },
			{ 0, 0, 0 },
			{ 0, 0, 1.1f },
			{ 0, 0, -1.2f },
			{ 0, 0, -1.6f },
			{ 0, 0, -0.2f },
			{ 0, 0, 0 },
		},
	};
}