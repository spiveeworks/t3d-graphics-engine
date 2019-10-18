#pragma once

#include "component.h"

namespace T3D
{

	class TimingCamera :
		public Component
	{
	public:
		TimingCamera(void) {}
		virtual ~TimingCamera(void) {}

		virtual void update(float dt);

	private:
		float time = 0.0f;
	};

}
