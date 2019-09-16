#include "ChipInWall.h"
#include "Math.h"

namespace T3D
{
	ChipInWall::ChipInWall(Vector3 wallSize,
		float holeX,
		float holeY,
		float radius,
		float depth,
		int density
	) {
		int layers = (density + 3) / 4;
		// Init vertex and index arrays
		initArrays(3 * 8 + 1 + (layers + 2) * density,	// num vertices
			       4 + 2 * density,		// num tris (front and face of chip)
			       5 + layers * density);		// num quads (sides, back, and chip)
		
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
		for (int j = 0; j < layers + 2; j++) {
			float theta = Math::HALF_PI * float(j > layers ? layers : j) / float(layers);
			float thisRadius = radius - depth + depth * sin(theta);
			float thisDepth = depth * cos(theta);
			for (int i = 0; i < density; i++) {
				float theta = Math::TWO_PI * float(i) / float(density);
				float x = holeX + thisRadius * cos(theta);
				float y = holeY + thisRadius * sin(theta);
				setVertex(25 + j * density + i, x, y, thisDepth-wallSize.z);
			}
		}
		setVertex(24, holeX, holeY, depth - wallSize.z);

		// front tris
		int prevk = 1;
		int lastLayer = 3 * 8 + 1 + (layers + 1) * density;
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
			setFace(i, lastLayer + i, lastLayer + j, k);
			
			if (prevk != k) {
				setFace(2 * density + k, lastLayer + i, k, prevk);
				prevk = k;
			}
		}

		//back
		setFace(0, 8 + 4, 8 + 5, 8 + 7, 8 + 6);
		//left
		setFace(1, 8 + 2, 8 + 0, 8 + 4, 8 + 6);
		//right
		setFace(2, 8 + 1, 8 + 3, 8 + 7, 8 + 5);
		//bottom
		setFace(3, 16 + 0, 16 + 1, 16 + 5, 16 + 4);
		//top
		setFace(4, 16 + 3, 16 + 2, 16 + 6, 16 + 7);

		// inner tris
		for (int i = 0; i < density; i++) {
			int j = (i + 1) % density;
			setFace(density + i, 24, 25 + j, 25 + i);
		}

		// inner quads
		for (int i = 0; i < density; i++) {
			int j = (i + 1) % density;
			for (int k = 0; k < layers; k++) {
				setFace(5 + k * density + i, 25 + k * density + i, 25 + k * density + j, 25 + (k + 1) * density + j, 25 + (k + 1) * density + i);
			}
		}

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
	}


	ChipInWall::~ChipInWall(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
