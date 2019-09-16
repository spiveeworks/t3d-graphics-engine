#pragma once
#include "gameobject.h"

namespace T3D {
	class CricketBat : public GameObject
	{
	public:
		CricketBat(T3DApplication *app, Material *mat);
		~CricketBat(void);

		GameObject *handle;
		GameObject *blade;
	};
}
