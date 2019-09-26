#pragma once

#include "component.h"
#include "StickFigure.h"
#include <vector>

namespace T3D
{

	class KeyboardEditor :
		public Component
	{
	public:
		KeyboardEditor(std::vector<StickFigure*>*);
		virtual ~KeyboardEditor(void);

		virtual void update(float dt);

	private:
		float jointSensitivity;
		float positionSensitivity;
		float mouseSensitivity;

		std::vector<StickFigure*> *figures;
		unsigned figure_index = 0;
		unsigned joint_index = 0;
		unsigned pose_index = 0;
		bool index_keys = false;
		bool animated = true;
	};

}

