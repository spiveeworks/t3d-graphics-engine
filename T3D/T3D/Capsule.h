#pragma once

#include "mesh.h"

namespace T3D
{
	class Capsule :
		public Mesh
	{
	public:
		Capsule(float radius, float height, int sides);
		virtual ~Capsule(void);
	};
}
