#pragma once

#include "Material.h"
#include "GLShader.h"

namespace T3D
{
	class SnowMaterial : public Material
	{
	protected:
		static GLShader* shader;
	public:
		SnowMaterial(float r, float g, float b);
	};
}
