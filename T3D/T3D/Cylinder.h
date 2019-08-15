#pragma once

#include "mesh.h"

namespace T3D
{
	class Cylinder :
		public Mesh
	{
	public:
		Cylinder(float radius, float height, int sides);
		virtual ~Cylinder(void);
	};
}
