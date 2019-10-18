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

		if (Input::keyDown[KEY_R] && !index_keys) {
			pose_changed = true;
			Poses::Pose &it = (*figures)[figure_index]->poses.poses[pose_index];
			it = Poses::reflect(it);
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

		index_keys = Input::keyDown[KEY_Z] || Input::keyDown[KEY_X] || Input::keyDown[KEY_C] || Input::keyDown[KEY_BACKSPACE] || Input::keyDown[KEY_RETURN] || Input::keyDown[KEY_BACKQUOTE] || Input::keyDown[KEY_BACKSLASH] || Input::keyDown[KEY_R];

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
			sprintf_s(fname, "Resources\\animation\\figure %02d - blocking", figure);
			std::ofstream figure_o = std::ofstream(fname, mode);
			unsigned size = poses.poses.size();
			figure_o.write((char*)&size, sizeof(unsigned));

			for (unsigned pose = 0; pose < poses.poses.size(); pose++) {
				sprintf_s(fname, "Resources\\animation\\figure %02d - pose %03d", figure, pose);
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

	void append_run_poses(Poses::Pose run[2], Vector3 from, Vector3 to, float start_time, float end_time, Poses &poses) {
		Vector3 velocity = (to - from) / (end_time - start_time);
		float speed = velocity.length();
		Vector3 orientation = Vector3(0, 0, (float)2 + atan2(velocity.x, velocity.z) / Math::HALF_PI);
		for (int i = 0; (float)i / speed < end_time - start_time; i++) {
			Poses::Pose pose = run[i % 2];
			if (i / 2 % 2) {
				pose = Poses::reflect(pose);
			}
			poses.poses.push_back(pose);
			float pos = (float)i + (i % 2 ? 0.2f : 0);
			float time = pos / speed;
			poses.times.push_back(start_time + time);
			poses.orientations.push_back(orientation);
			poses.positions.push_back(from + time * velocity);
		}
	}

	// the timing and pacing on this one is very different to run
	// this procedure won't actually get you close to the end location unless you manually pick it right
	// simply moves 11.2 units in the direction of the end location
	void append_bowl_poses(Poses::Pose run[2], Poses::Pose bowl[7], Vector3 from, Vector3 to, float start_time, float end_time, Poses &poses) {
		Vector3 velocity = (to - from) / (end_time - start_time);
		velocity.normalise();
		Vector3 orientation = Vector3(0, 0, (float)2 + atan2(velocity.x, velocity.z) / Math::HALF_PI);
		for (int i = 0; i < 12; i++) {
			Poses::Pose pose;
			float pos;
			if (3 <= i && i - 3 < 7) {
				pose = bowl[i - 3];
				pos = (float)i + (i % 2 ? 0.2f : 0);
			}
			else {
				pose = run[i % 2];
				pos = (float)i + (i % 2 ? 0.2f : 0);
				if (i / 2 % 2) {
					pose = Poses::reflect(pose);
				}
			}
			poses.poses.push_back(pose);
			float time = end_time - start_time;
			if (i < 7) {
				time *= pos / 16.0f;
			}
			else {
				time *= (7.2f + (pos - 7.2f) * 2.0f) / 16.0f; // move at half speed after the bowl
			}
			poses.times.push_back(start_time + time);
			if (i - 3 == 6) {
				poses.orientations.push_back(orientation + Vector3(0, 0.3f, 0.5f));
			} else {
				poses.orientations.push_back(orientation);
			}
			poses.positions.push_back(from + pos * velocity);
		}
	}
	
	Poses::Pose load_pose(char *fname) {
		Poses::Pose result;
		std::ifstream pose_i = std::ifstream(fname, std::ios_base::in | std::ios_base::binary);
		pose_i.read((char*)& result, sizeof(Poses::Pose));
		pose_i.close();
		return result;
	}
	
	void KeyboardEditor::loadPoses() {
		for (StickFigure* figure : *figures) {
			delete figure->getTransform();
		}
		figures->clear();

		Poses::Pose run[2];
		run[0] = load_pose("Resources\\animation\\run 1");
		run[1] = load_pose("Resources\\animation\\run 2");
		Poses::Pose bowl[7];
		bowl[0] = load_pose("Resources\\animation\\bowl 1");
		bowl[1] = load_pose("Resources\\animation\\bowl 2");
		bowl[2] = load_pose("Resources\\animation\\bowl 3");
		bowl[3] = load_pose("Resources\\animation\\bowl 4");
		bowl[4] = load_pose("Resources\\animation\\bowl 5");
		bowl[5] = load_pose("Resources\\animation\\bowl 6");
		bowl[6] = load_pose("Resources\\animation\\bowl 7");

		StickFigure *batter = new StickFigure(app, mat, root);
		StickFigure *bowler = new StickFigure(app, mat, root);

		figures->push_back(batter);
		figures->push_back(bowler);

		batter->poses.poses.push_back(Poses::NEUTRAL);
		batter->poses.times.push_back(0.0f);
		batter->poses.orientations.push_back(Vector3(0, 0, 2));
		batter->poses.positions.push_back(Vector3(0, 0, 0));

		// run and bowl
		append_run_poses(run, Vector3(5, 0, 70), Vector3(5, 0, 57), 0, 4, bowler->poses);
		append_run_poses(run, Vector3(5, 0, 57), Vector3(5, 0, 41), 4, 7, bowler->poses);
		append_bowl_poses(run, bowl, Vector3(5, 0, 41), Vector3(5, 0, 29), 7, 9, bowler->poses);

		// get a run
		batter->poses.poses.push_back(Poses::NEUTRAL);
		batter->poses.times.push_back(8.0f);
		batter->poses.orientations.push_back(Vector3(0, 0, 2));
		batter->poses.positions.push_back(Vector3(0, 0, 0));
		append_run_poses(run, Vector3(0, 0, 0), Vector3(0, 0, 20), 8.5f, 11.0f, batter->poses);
		append_run_poses(run, Vector3(0, 0, 20), Vector3(0, 0, 0), 11.0f, 13.5f, batter->poses);
		append_run_poses(run, Vector3(0, 0, 0), Vector3(0, 0, 20), 13.5f, 16.0f, batter->poses);
		append_run_poses(run, Vector3(0, 0, 20), Vector3(0, 0, 0), 16.0f, 18.5f, batter->poses);
		batter->poses.poses.push_back(Poses::NEUTRAL);
		batter->poses.times.push_back(19.0f);
		batter->poses.orientations.push_back(Vector3(0, 0, 2));
		batter->poses.positions.push_back(Vector3(0, 0, 0));


		// start running for ball
		append_run_poses(run, Vector3(5, 0, 29), Vector3(5, 0, -5), 9, 12, bowler->poses);
		append_run_poses(run, Vector3(5, 0, -5), Vector3(-30, 0, -30), 12, 16, bowler->poses);
		append_run_poses(run, Vector3(-30, 0, -30), Vector3(0, 0, -5), 16, 20, bowler->poses);
		append_run_poses(run, Vector3(0, 0, -5), Vector3(5, 0, -4), 20, 22, bowler->poses);
		append_run_poses(run, Vector3(5, 0, -4), Vector3(5, 0, 34), 22, 32, bowler->poses);

		batter->startAnimation(0.0f);
		bowler->startAnimation(0.0f);
	}
	/*
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
			figures->push_back(new StickFigure(app, mat, root, limbLength, limbRadius, torsoLength, torsoRadius, collarWidth, pelvisWidth, headRadius));

			Poses& poses = (*figures)[figure]->poses;
			sprintf_s(fname, "Resources\\animation\\figure %02d - blocking", figure);
			std::ifstream figure_i = std::ifstream(fname, mode);
			unsigned pose_num;
			figure_i.read((char*)&pose_num, sizeof(unsigned));
			poses.poses.resize(pose_num);
			poses.positions.resize(pose_num);
			poses.orientations.resize(pose_num);
			poses.times.resize(pose_num);

			for (unsigned pose = 0; pose < pose_num; pose++) {
				sprintf_s(fname, "Resources\\animation\\figure %02d - pose %03d", figure, pose);
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
	}/**/
}
