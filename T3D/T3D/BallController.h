#pragma once

#include "component.h"
#include "StickFigure.h"

namespace T3D
{

	class BallController :
		public Component
	{
	public:
		BallController(StickFigure*bowler, Transform *root) : bowler(bowler), root(root) {}
		virtual ~BallController(void) {}

		virtual void update(float dt);

	private:
		float time = 0.0f;
		StickFigure *bowler;
		Transform *root;
	};

}
