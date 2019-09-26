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
		void keyDownResolve(float dt);
		void keyUpResolve(float dt);
		void mouseMoveResolve();

	private:
		float keySensitivity;
		float mouseSensitivity;
		std::vector<StickFigure*> *figures;
	};

}

