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

	class Tutorial3 :
		public WinGLApplication
	{
	public:
		Tutorial3(void);
		~Tutorial3(void);

		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}

