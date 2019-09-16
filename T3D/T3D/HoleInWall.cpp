#include "HoleInWall.h"
#include "Math.h"

namespace T3D
{
	HoleInWall::HoleInWall(Vector3 wallSize, //length, height, thickness of wall
		float holeX,      // the x position of the centre of the hole
		float holeY,       // the y position of the centre of the hole
		float radius,     // the radius of the hole
		int density        // the density of the hole
	) {
		// Init vertex and index arrays
		initArrays(3 * 8 + 4 * density,	// num vertices
			       8 + 2 * density,		// num tris (front and back)
			       4 + density);		// num quads (sides and hole)
		
		// corner vertices
		int c = 0;
		for (int k = -1; k <= 1; k += 2) {
			for (int j = -1; j <= 1; j += 2) {
				for (int i = -1; i <= 1; i += 2) {
					setVertex(c, i*wallSize.x, j*wallSize.y, k*wallSize.z);
					setVertex(8 + c, i*wallSize.x, j*wallSize.y, k*wallSize.z);
					setVertex(16 + c, i*wallSize.x, j*wallSize.y, k*wallSize.z);
					c++;  // nice
				}
			}
		}
		
		// hole vertices
		for (int i = 0; i < density; i++) {
			float theta = Math::TWO_PI * float(i) / float(density);
			float x = holeX + radius * cos(theta);
			float y = holeY + radius * sin(theta);
			setVertex(24 + i, x, y, -wallSize.z);
			setVertex(24 + density + i, x, y, wallSize.z);
			setVertex(24 + 2 * density + i, x, y, -wallSize.z);
			setVertex(24 + 3 * density + i, x, y, wallSize.z);
		}

		// front/back tris
		int prevk = 1;
		for (int i = 0; i < density; i++) {
			int j = (i + 1) % density;
			float theta = Math::TWO_PI * (float(i) + 0.5f) / float(density);
			int k;
			if (theta < Math::HALF_PI) {
				k = 3;
			}
			else if (theta < 2 * Math::HALF_PI) {
				k = 2;
			}
			else if (theta < 3 * Math::HALF_PI) {
				k = 0;
			}
			else {
				k = 1;
			}
			setFace(i, 24 + i, 24 + j, k);
			setFace(density + i, 24 + density + j, 24 + density + i, 4 + k);
			
			if (prevk != k) {
				setFace(2 * density + k, 24 + i, k, prevk);
				setFace(2 * density + 4 + k, 24 + density + i, 4 + prevk, 4 + k);
				prevk = k;
			}
		}

		//left
		setFace(0, 8 + 2, 8 + 0, 8 + 4, 8 + 6);
		//right
		setFace(1, 8 + 1, 8 + 3, 8 + 7, 8 + 5);
		//bottom
		setFace(2, 16 + 0, 16 + 1, 16 + 5, 16 + 4);
		//top
		setFace(3, 16 + 3, 16 + 2, 16 + 6, 16 + 7);

		// inner quads
		for (int i = 0; i < density; i++) {
			int j = (i + 1) % density;
			setFace(4 + i, 24 + 2 * density + j, 24 + 2 * density + i, 24 + 3 * density + i, 24 + 3 * density + j);
		}
		
		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
	}


	HoleInWall::~HoleInWall(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
