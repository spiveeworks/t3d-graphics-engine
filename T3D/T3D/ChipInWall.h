#pragma once

#include "mesh.h"

namespace T3D
{
	class ChipInWall :
		public Mesh
	{
	public:
		ChipInWall::ChipInWall(Vector3 wallSize, //length, height, thickness of wall
			float ChipX,      // the x position of the centre of the Chip
			float ChipY,       // the y position of the centre of the Chip
			float radius,     // the radius of the Chip
			float depth,     // the radius of the Chip
			int density        // the density of the Chip
		);
		virtual ~ChipInWall(void);
	};
}


