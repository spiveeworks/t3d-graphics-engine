#pragma once

#include "mesh.h"

namespace T3D
{
	class Pyramid :
		public Mesh
	{
	public:
		Pyramid(float base, float height);
		virtual ~Pyramid(void);
	};
}
