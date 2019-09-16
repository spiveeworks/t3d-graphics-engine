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

	class Assignment1 :
		public WinGLApplication
	{
	public:
		Assignment1(void);
		~Assignment1(void);

		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}

