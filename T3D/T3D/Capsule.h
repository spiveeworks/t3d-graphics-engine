#pragma once

#include "Sweep.h"

namespace T3D
{
	class Capsule :
		public Sweep
	{
	public:
		static std::vector<Vector3> CapsuleProfile(float radius, float length, int sides);
		static SweepPath CapsulePath(float radius, float length, int sides);
		Capsule(float radius, float length, int sides) : Sweep(CapsuleProfile(radius, length, sides), CapsulePath(radius, length, sides), true) {
		}
		virtual ~Capsule(void) {
		}
	};
}
