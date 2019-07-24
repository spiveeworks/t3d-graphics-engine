// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GameObject.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#include <math.h>
#include "DrawTask.h"

namespace T3D {

	DrawTask::DrawTask(T3DApplication *app, Texture* tex) : Task(app)
	{
		drawArea = tex;
		init();
	}


	DrawTask::~DrawTask(void)
	{
	}

	void DrawTask::init(){		
		drawArea->clear(Colour(255,255,255,255));
		drawBresLine(400, 300, 400+100, 300, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400+100, 300+50, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400+100, 300+100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400+50, 300 + 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400, 300 + 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400-50, 300 + 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400-100, 300 + 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 - 100, 300 + 50, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 - 100, 300, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 - 100, 300 - 50, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 - 100, 300 - 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 - 50, 300 - 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400, 300 - 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 + 50, 300 - 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 + 100, 300 - 100, Colour(0, 0, 0, 255));
		drawBresLine(400, 300, 400 + 100, 300 - 50, Colour(0, 0, 0, 255));
	}

	void DrawTask::drawDDALine(int x1, int y1, int x2, int y2,Colour c){
		float ystep = float(y2-y1)/(x2-x1);
		if (abs(ystep) <= 1.0) {
			if (x2 < x1) {
				swap(x1, x2);
				swap(y1, y2);
			}
			float y = y1;
			for (int x = x1; x < x2; x++) {
				drawArea->plotPixel(x, int(y), c);
				y += ystep;
			}
		} else {
			float xstep = 1.0 / ystep;
			if (y2 < y1) {
				swap(x1, x2);
				swap(y1, y2);
			}
			float x = x1;
			for (int y = y1; y < y2; y++) {
				drawArea->plotPixel(x, int(y), c);
				x += xstep;
			}
		}
	}
		
	void DrawTask::drawBresLine(int x1, int y1, int x2, int y2,Colour c){
		int dy = y2 - y1;
		int dx = x2 - x1;
		if (dy <= 0 || dx <= 0) {
			return;
		}
		int err = 0;
		int x = x1;
		int y = y1;
		while (x < x2) {
			drawArea->plotPixel(x, int(y), c);
			if (err > dx) {
				y++;
				err -= dx;
			}
			else {
				x++;
				err += dy;
			}
		}
	}

	void DrawTask::update(float dt){
		//drawArea->clear(Colour(255,255,255,255));

		app->getRenderer()->reloadTexture(drawArea);
	}

}
