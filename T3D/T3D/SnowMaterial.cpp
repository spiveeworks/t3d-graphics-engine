#include "SnowMaterial.h"

namespace T3D{
	GLShader* SnowMaterial::shader = NULL;
	SnowMaterial::SnowMaterial(float r, float g, float b) : Material(r, g, b, 1.0f) {
		if (!shader) {
			shader = new GLShader("Resources/snowVert.shader", "Resources/snowFrag.shader");
			shader->compileShader();
		}
		setShader(shader);
	}
}
