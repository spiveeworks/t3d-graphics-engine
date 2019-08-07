// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// DrawTask.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#pragma once
#include "task.h"
#include "T3DApplication.h"
#include "Texture.h"

namespace T3D{

	class DrawTask :
		public Task
	{
	public:
		DrawTask(T3DApplication *app, Texture* tex);
		~DrawTask(void);

		void init();
		void drawDDALine(int x1, int y1, int x2, int y2, Colour c);
		void drawBresLine(int x1, int y1, int x2, int y2, Colour c);
		void drawCircleTrig(int x0, int y0, float r, Colour c);
		void drawCirclePythag(int x0, int y0, int r, Colour c);
		void drawCircleBres(int x0, int y0, int r, Colour c);
		void drawTriFan(vector<Vector3> points, Vector3 offset);
		void drawPie(int cx, int cy, int r, float theta);

		virtual void update(float dt);

	private:
		Texture *drawArea;
		vector<Vector3> poly;
		vector<Vector3> alloc;
		float scale, time;
	};

}

