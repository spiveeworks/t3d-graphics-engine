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

	KeyboardEditor::KeyboardEditor(std::vector<StickFigure*> *_figures)
	{
		jointSensitivity = JOINT_SENSITIVITY_MIN;
		positionSensitivity = POSITION_SENSITIVITY_MIN;
		figures = _figures;
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
			joint_index = (diff + joint_index + Poses::NUMJOINTS) % Poses::NUMJOINTS;
		}

		StickFigure *figure = (*figures)[figure_index];

		if (Input::keyDown[KEY_BACKSPACE] && !index_keys) {
			figure->poses.poses[pose_index][joint_index] = Poses::NEUTRAL[joint_index];
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

		if (Input::keyDown[KEY_BACKQUOTE] && !index_keys) {
			savePoses();
			pose_changed = true;
		}
		if (Input::keyDown[KEY_BACKSLASH] && !index_keys) {
			loadPoses();
			pose_changed = true;
		}

		if (Input::keyDown[KEY_INSERT]) {
			figure->poses.poses[pose_index][joint_index].x -= dt * jointSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_DELETE]) {
			figure->poses.poses[pose_index][joint_index].x += dt * jointSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_HOME]) {
			figure->poses.poses[pose_index][joint_index].y -= dt * jointSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_END]) {
			figure->poses.poses[pose_index][joint_index].y += dt * jointSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_PAGEUP]) {
			figure->poses.poses[pose_index][joint_index].z -= dt * jointSensitivity;
			pose_changed = true;
		}
		if (Input::keyDown[KEY_PAGEDOWN]) {
			figure->poses.poses[pose_index][joint_index].z += dt * jointSensitivity;
			pose_changed = true;
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
				figure->setPose(figure->poses.positions[pose_index], figure->poses.poses[pose_index]);
			}
		}

		index_keys = Input::keyDown[KEY_Z] || Input::keyDown[KEY_X] || Input::keyDown[KEY_C] || Input::keyDown[KEY_BACKSPACE] || Input::keyDown[KEY_RETURN] || Input::keyDown[KEY_BACKQUOTE] || Input::keyDown[KEY_BACKSLASH];

		jointSensitivity = Input::keyDown[KEY_LEFT_SHIFT] ? JOINT_SENSITIVITY_MAX : JOINT_SENSITIVITY_MIN;
		positionSensitivity = Input::keyDown[KEY_LEFT_SHIFT] ? POSITION_SENSITIVITY_MAX : POSITION_SENSITIVITY_MIN;
	}

	void KeyboardEditor::savePoses() {
		for (unsigned figure = 0; figure < figures->size(); figure++) {
			Poses& poses = (*figures)[figure]->poses;
			for (unsigned pose = 0; pose < poses.poses.size(); pose++) {
				char fname[100];
				sprintf_s(fname, "Resources\\animation\\figure %d - pose %d", figure, pose);
				std::ofstream pose_o = std::ofstream(fname, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
				pose_o.write((char*)&poses.poses[pose], sizeof(Poses::Pose));
				pose_o.close();
			}
		}
	}

	void KeyboardEditor::loadPoses() {
		printf("Attempted to load poses!\n");
	}
}
