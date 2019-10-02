#pragma once

#include "Task.h"
#include "StickFigure.h"
#include <vector>

namespace T3D
{

	class KeyboardEditor :
		public Task
	{
	public:
		KeyboardEditor(std::vector<StickFigure*>*_figures, T3DApplication * _app, Material *_mat, Transform *_root);
		virtual ~KeyboardEditor(void);

		virtual void update(float dt);
		// violates Single Responsibility Principle but modular code is only useful if it has plans to be extended
		void savePoses();
		void loadPoses();

	private:
		// this stuff could be in other places, app in ancestors, mat and root in scene?
		T3DApplication * app;
		Material *mat;
		Transform *root;

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

