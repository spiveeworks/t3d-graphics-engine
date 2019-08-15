#include "Cylinder.h"

namespace T3D {

	Cylinder::Cylinder(float radius, float height, int sides)
	{
		// Init vertex and index arrays
		initArrays(2 + 2 * sides,	// num vertices
			2 * sides,		// num tris
			sides);		// num quads

					// Set vertices

		float dtheta = 2 * 3.1415926535 / float(sides);
		setVertex(2 * sides, 0, height, 0);
		setVertex(2 * sides + 1, 0, -height, 0);
		for (int i = 0; i < sides; i++) {
			float theta = dtheta * i;
			float x = radius * cos(theta);
			float z = radius * sin(theta);
			setVertex(i, x, height, z);
			setVertex(sides + i, x, -height, z);
		}

		// Build quads and tris
		for (int i = 0, j = sides-1; i < sides; j = i++) {
			// int j = (i - 1) % sides;
			setFace(i, i, sides + i, sides + j, j);

			setFace(i, 2 * sides, i, j);
			setFace(sides + i, 2 * sides + 1, sides + j, sides + i);
		}


		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
	}


	Cylinder::~Cylinder()
	{
	}

}