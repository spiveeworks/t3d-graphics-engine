// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Jarvis Carroll
//
// Tutorial3.cpp
//
//

#pragma once
#include "winglapplication.h"
#include "Texture.h"
#include "DrawTask.h"

namespace T3D{

	class Assignment2 :
		public WinGLApplication
	{
	public:
		Assignment2(void);
		~Assignment2(void);

		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}

