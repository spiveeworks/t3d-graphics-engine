#include "Pyramid.h"

namespace T3D {

	Pyramid::Pyramid(float base, float height)
	{
		// Init vertex and index arrays
		initArrays(4 + 3 * 4,	// num vertices
			4,		// num tris
			1);		// num quads

					// Set vertices

		int pos = 0;

		//bottom
		setVertex(pos++, -base, -height, -base);
		setVertex(pos++, -base, -height, base);
		setVertex(pos++, base, -height, base);
		setVertex(pos++, base, -height, -base);
		//front
		setVertex(pos++, -base, -height, -base);
		setVertex(pos++, base, -height, -base);
		setVertex(pos++, 0.0f, height, 0.0f);
		//back
		setVertex(pos++, -base, -height, base);
		setVertex(pos++, base, -height, base);
		setVertex(pos++, 0.0f, height, 0.0f);
		//left
		setVertex(pos++, -base, -height, -base);
		setVertex(pos++, -base, -height, +base);
		setVertex(pos++, 0.0f, height, 0.0f);
		//right
		setVertex(pos++, base, -height, -base);
		setVertex(pos++, base, -height, +base);
		setVertex(pos++, 0.0f, height, 0.0f);

		// Build quads
		pos = 0;
		//bottom
		setFace(pos++, 3, 2, 1, 0);
		// Build tris
		pos = 0;
		//front
		setFace(pos++, 6, 5, 4);
		//back
		setFace(pos++, 7, 8, 9);
		//left
		setFace(pos++, 10, 11, 12);
		//right
		setFace(pos++, 15, 14, 13);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();


	}


	Pyramid::~Pyramid()
	{
	}

}