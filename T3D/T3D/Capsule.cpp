#include "Capsule.h"

namespace T3D {
	std::vector<Vector3> Capsule::CapsuleProfile(float radius, float length, int sides) {
		std::vector<Vector3> result;

		int rows = sides / 4;
		for (int i = 0; i < rows; i++) {
			float theta = Math::HALF_PI * float(i) / float(rows);
			result.push_back(Vector3(radius * sin(theta), -radius * cos(theta), 0));
		}
		result.push_back(Vector3(radius, 0, 0));
		result.push_back(Vector3(radius, length, 0));
		for (int i = rows - 1; i >= 0; i--) {
			float theta = Math::HALF_PI * float(i) / float(rows);
			result.push_back(Vector3(radius * sin(theta), length + radius * cos(theta), 0));
		}

		return result;
	}

	SweepPath Capsule::CapsulePath(float radius, float height, int sides) {
		SweepPath result;
		result.makeCirclePath(0, sides);
		return result;
	}
}