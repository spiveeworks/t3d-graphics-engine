// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Animation.cpp
//
// A component for controlling skeletal animation.

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include <iostream>
#include "component.h"
#include "Transform.h"
#include "Vector3.h"
#include "Bone.h"

namespace T3D
{
	typedef std::pair<std::string,Bone*> BoneEntry;
	typedef std::map<std::string,Bone*> BoneMap;

	class Animation :
		public Component
	{
	public:
		Animation(float duration);
		virtual ~Animation();
		
		virtual void update(float dt);

		void addBone(std::string n);
		void addKey(std::string n, float time, Quaternion rot, Vector3 pos);
		void clearKeys();

		void play(float _time){ time = _time; playing = true; }
		float getTime() { return time; };
		void pause(){ playing = false; }
		bool getPlaying() { return playing; }
		void loop(bool loop){ looping = loop; } 

		void printFrames()
        {
            std::cout << "Animation:\n";
			BoneMap::iterator it;
			for (it = bones.begin(); it!= bones.end(); it++){
				std::cout << "bone: " << it->first << "\n";
				Bone *b = it->second;
				b->printFrames();
			}
        }

		void printKeyFrames()
        {
            std::cout << "Animation:\n";
			BoneMap::iterator it;
			for (it = bones.begin(); it!= bones.end(); it++){
				std::cout << "bone: " << it->first << "\n";
				Bone *b = it->second;
				b->printKeyFrames();
			}
        }

	protected:
		BoneMap bones;
		float duration;
		int frames;

		float time;
		bool playing;
		bool looping;
	};
}

#endif

