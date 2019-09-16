#pragma once
#include "gameobject.h"

namespace T3D {
	class CricketBat : public GameObject
	{
	public:
		CricketBat(T3DApplication *app, Material *blade, Material *handle);
		~CricketBat(void);

		GameObject *handle;
		GameObject *blade;
	};
}
