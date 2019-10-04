#include <iostream>
#include <fstream>

#include "KeyboardEditor.h"
#include "Input.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Transform.h"
#include "Math.h"

namespace T3D
{
	//min and max speeds for key and mouse sensitivity
	#define JOINT_SENSITIVITY_MIN 0.1f
	#define JOINT_SENSITIVITY_MAX 1.0f
	#define POSITION_SENSITIVITY_MIN 1.0f
	#define POSITION_SENSITIVITY_MAX 5.0f

	KeyboardEditor::KeyboardEditor(std::vector<StickFigure*>*_figures, T3DApplication * _app, Material *_mat, Transform *_root) : Task(_app)
	{
		jointSensitivity = JOINT_SENSITIVITY_MIN;
		positionSensitivity = POSITION_SENSITIVITY_MIN;
		figures = _figures;
		app = _app;
		mat = _mat;
		root = _root;
	}


	KeyboardEditor::~KeyboardEditor(void)
	{
	}

	void KeyboardEditor::update(float dt){
		bool pose_changed = false;

		if (Input::keyDown[KEY_Z] && !index_keys) {
			int diff = Input::keyDown[KEY_LEFT_SHIFT] ? -1 : +1;
			figure_index = (diff + figure_index + figures->size()) % figures->size();
		}
		if (Input::keyDown[KEY_X] && !index_keys) {
			int diff = Input::keyDown[KEY_LEFT_SHIFT] ? -1 : +1;
			unsigned pose_num = (*figures)[figure_index]->poses.poses.size();
			pose_index = (diff + pose_index + pose_num) % pose_num;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_C] && !index_keys) {
			int diff = Input::keyDown[KEY_LEFT_SHIFT] ? -1 : +1;
			joint_index = (diff + joint_index + Poses::NUMJOINTS + 1) % (Poses::NUMJOINTS + 1);
		}

		if (Input::keyDown[KEY_BACKQUOTE] && !index_keys) {
			savePoses();
			pose_changed = true;
		}
		if (Input::keyDown[KEY_BACKSLASH] && !index_keys) {
			loadPoses();
			pose_changed = true;
		}

		StickFigure *figure = (*figures)[figure_index];

		if (Input::keyDown[KEY_BACKSPACE] && !index_keys) {
			if (joint_index < Poses::NUMJOINTS) {
				figure->poses.poses[pose_index][joint_index] = Input::keyDown[KEY_LEFT_SHIFT] ? Poses::ZEROES[joint_index] : Poses::NEUTRAL[joint_index];
			}
			else {
				figure->poses.orientations[pose_index] = { 0, 0, 0 };
			}
			pose_changed = true;
		}

		if (Input::keyDown[KEY_RETURN] && !index_keys) {
			animated = !animated;
			pose_changed = true;
			if (animated) {
				float time = figure->poses.times[pose_index];
				for (unsigned i = 0; i < figures->size(); i++) {
					(*figures)[i]->startAnimation(time);
				}
			}
			else {
				for (unsigned i = 0; i < figures->size(); i++) {
					(*figures)[i]->anim->pause();
				}
			}
		}
		else if (animated && !figure->anim->getPlaying()) {
			animated = false;
			pose_changed = true;
		}

		{
			Vector3& joint = joint_index < Poses::NUMJOINTS ? figure->poses.poses[pose_index][joint_index] : figure->poses.orientations[pose_index];
			if (Input::keyDown[KEY_INSERT]) {
				joint.x -= dt * jointSensitivity;
				pose_changed = true;
			}
			if (Input::keyDown[KEY_DELETE]) {
				joint.x += dt * jointSensitivity;
				pose_changed = true;
			}
			if (Input::keyDown[KEY_HOME]) {
				joint.y -= dt * jointSensitivity;
				pose_changed = true;
			}
			if (Input::keyDown[KEY_END]) {
				joint.y += dt * jointSensitivity;
				pose_changed = true;
			}
			if (Input::keyDown[KEY_PAGEUP]) {
				joint.z -= dt * jointSensitivity;
				pose_changed = true;
			}
			if (Input::keyDown[KEY_PAGEDOWN]) {
				joint.z += dt * jointSensitivity;
				pose_changed = true;
			}
		}

		if (Input::keyDown[KEY_I]) {
			figure->poses.positions[pose_index].z -= dt * positionSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_K]) {
			figure->poses.positions[pose_index].z += dt * positionSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_J]) {
			figure->poses.positions[pose_index].x -= dt * positionSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_L]) {
			figure->poses.positions[pose_index].x += dt * positionSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_N]) {
			figure->poses.positions[pose_index].y -= dt * positionSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_M]) {
			figure->poses.positions[pose_index].y += dt * positionSensitivity;
			pose_changed = true;
		}

		if (pose_changed) {
			if (animated) {
				// rebuild keyframes and restart at the exact current time
				figure->startAnimation(figure->anim->getTime());
			} else {
				// kind of hacky? surely StickFigure should know how to read its own poses member
				figure->setPose(figure->poses.positions[pose_index], figure->poses.orientations[pose_index], figure->poses.poses[pose_index]);
			}
		}

		index_keys = Input::keyDown[KEY_Z] || Input::keyDown[KEY_X] || Input::keyDown[KEY_C] || Input::keyDown[KEY_BACKSPACE] || Input::keyDown[KEY_RETURN] || Input::keyDown[KEY_BACKQUOTE] || Input::keyDown[KEY_BACKSLASH];

		jointSensitivity = Input::keyDown[KEY_LEFT_SHIFT] ? JOINT_SENSITIVITY_MAX : JOINT_SENSITIVITY_MIN;
		positionSensitivity = Input::keyDown[KEY_LEFT_SHIFT] ? POSITION_SENSITIVITY_MAX : POSITION_SENSITIVITY_MIN;
	}

	void KeyboardEditor::savePoses() {
		// ofstream stuff
		char fname[100];
		std::ios_base::openmode mode = std::ios_base::out | std::ios_base::binary | std::ios_base::trunc;

		sprintf_s(fname, "Resources\\animation\\figures");
		std::ofstream scene_o = std::ofstream(fname, mode);
		unsigned size = figures->size();
		scene_o.write((char*)&size, sizeof(unsigned));
		
		for (unsigned figure = 0; figure < figures->size(); figure++) {
			StickFigure *figure_data = (*figures)[figure];
			scene_o.write((char*)&figure_data->limbLength, sizeof(float));
			scene_o.write((char*)&figure_data->limbRadius, sizeof(float));
			scene_o.write((char*)&figure_data->torsoLength, sizeof(float));
			scene_o.write((char*)&figure_data->torsoRadius, sizeof(float));
			scene_o.write((char*)&figure_data->collarWidth, sizeof(float));
			scene_o.write((char*)&figure_data->pelvisWidth, sizeof(float));
			scene_o.write((char*)&figure_data->headRadius, sizeof(float));

			Poses& poses = (*figures)[figure]->poses;
			sprintf_s(fname, "Resources\\animation\\figure %d - blocking", figure);
			std::ofstream figure_o = std::ofstream(fname, mode);
			unsigned size = poses.poses.size();
			figure_o.write((char*)&size, sizeof(unsigned));

			for (unsigned pose = 0; pose < poses.poses.size(); pose++) {
				sprintf_s(fname, "Resources\\animation\\figure %d - pose %d", figure, pose);
				std::ofstream pose_o = std::ofstream(fname, mode);
				pose_o.write((char*)&poses.poses[pose], sizeof(Poses::Pose));
				pose_o.close();

				figure_o.write((char*)&poses.times[pose], sizeof(float));
				figure_o.write((char*)&poses.positions[pose], sizeof(Vector3));
				figure_o.write((char*)& poses.orientations[pose], sizeof(Vector3));
			}

			figure_o.close();
		}

		scene_o.close();
	}

	void KeyboardEditor::loadPoses() {
		// ifstream stuff
		char fname[100];
		std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary;

		sprintf_s(fname, "Resources\\animation\\figures");
		std::ifstream scene_i = std::ifstream(fname, mode);
		if (!scene_i) {
			printf("Failed to open file!\n");
			return;
		}
		unsigned figure_num;
		scene_i.read((char*)&figure_num, sizeof(unsigned));

		for (unsigned figure = 0; figure < figures->size(); figure++) {
			delete (*figures)[figure]->getTransform();
		}
		figures->clear();
		figures->reserve(figure_num);

		for (unsigned figure = 0; figure < figure_num; figure++) {
			float limbLength,
				limbRadius,
				torsoLength,
				torsoRadius,
				collarWidth,
				pelvisWidth,
				headRadius;
			scene_i.read((char*)&limbLength, sizeof(float));
			scene_i.read((char*)&limbRadius, sizeof(float));
			scene_i.read((char*)&torsoLength, sizeof(float));
			scene_i.read((char*)&torsoRadius, sizeof(float));
			scene_i.read((char*)&collarWidth, sizeof(float));
			scene_i.read((char*)&pelvisWidth, sizeof(float));
			scene_i.read((char*)&headRadius, sizeof(float));
			figures->push_back(new StickFigure(app, limbLength, limbRadius, torsoLength, torsoRadius, collarWidth, pelvisWidth, headRadius, mat, root));

			Poses& poses = (*figures)[figure]->poses;
			sprintf_s(fname, "Resources\\animation\\figure %d - blocking", figure);
			std::ifstream figure_i = std::ifstream(fname, mode);
			unsigned pose_num;
			figure_i.read((char*)&pose_num, sizeof(unsigned));
			poses.poses.resize(pose_num);
			poses.positions.resize(pose_num);
			poses.orientations.resize(pose_num);
			poses.times.resize(pose_num);

			for (unsigned pose = 0; pose < pose_num; pose++) {
				sprintf_s(fname, "Resources\\animation\\figure %d - pose %d", figure, pose);
				std::ifstream pose_i = std::ifstream(fname, mode);

				pose_i.read((char*)& poses.poses[pose], sizeof(Poses::Pose));
				pose_i.close();

				figure_i.read((char*)&poses.times[pose], sizeof(float));
				figure_i.read((char*)&poses.positions[pose], sizeof(Vector3));
				figure_i.read((char*)& poses.orientations[pose], sizeof(Vector3));
			}
			(*figures)[figure]->startAnimation(0.0f);

			figure_i.close();
		}

		scene_i.close();
	}
}
