#pragma once
#include "gameobject.h"
#include "T3DApplication.h"
#include "StickFigure.h"

namespace T3D {
	class Scene : public GameObject
	{
	public:
		Scene(T3DApplication * app): GameObject(app) {}
		virtual ~Scene(void) {}

		std::vector<StickFigure*> figures;
	};
}
