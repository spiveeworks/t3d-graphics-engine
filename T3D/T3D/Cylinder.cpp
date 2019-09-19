#include "Cylinder.h"

namespace T3D {

	Cylinder::Cylinder(float radius, float height, int sides)
	{
		// Init vertex and index arrays
		initArrays(4 * sides,	// num vertices
			2 * (sides - 2),		// num tris
			sides);		// num quads

					// Set vertices

		float dtheta = 2 * 3.1415926535 / float(sides);
		setVertex(2 * sides, 0, height, 0);
		setVertex(2 * sides + 1, 0, -height, 0);
		for (int i = 0; i < sides; i++) {
			float theta = dtheta * i;
			float x = radius * cos(theta);
			float z = radius * sin(theta);
			setVertex(0 * sides + i, x,  height, z);
			setVertex(1 * sides + i, x, -height, z);
			setVertex(2 * sides + i, x,  height, z);
			setVertex(3 * sides + i, x, -height, z);
		}

		// Build quads and tris
		for (int i = 0; i < sides; i++) {
			int j = (i + 1) % sides;
			setFace(i, j, sides + j, sides + i, i);
		}
		for (int i = 1; i <= sides - 2; i++) {
			setFace(i         - 1, 2 * sides + 0, 2 * sides + i + 1, 2 * sides + i    );
			setFace(i + sides - 3, 3 * sides + 0, 3 * sides + i,     3 * sides + i + 1);
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