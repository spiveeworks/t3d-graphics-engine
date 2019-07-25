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
		drawCircleTrig(400, 300, 100.0, Colour(0, 0, 0, 255));
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
		int dx = x2 - x1;
		int dy = y2 - y1;
		if (abs(dx) >= abs(dy)) {
			if (x2 < x1) {
				swap(x1, x2);
				dx *= -1;
				swap(y1, y2);
				dy *= -1;
			}
			int sy = 1;
			if (dy < 0) {
				sy = -1;
				dy *= -1;
			}
			int y = y1;
			int err = dx / 2;
			for (int x = x1; x < x2; x++) {
				drawArea->plotPixel(x, y, c);
				err += dy;
				if (err > dx) {
					y += sy;
					err -= dx;
				}
			}
		}
		else {
			if (y2 < y1) {
				swap(x1, x2);
				dx *= -1;
				swap(y1, y2);
				dy *= -1;
			}
			int sx = 1;
			if (dx < 0) {
				sx = -1;
				dx *= -1;
			}
			int x = x1;
			int err = dy / 2;
			for (int y = y1; y < y2; y++) {
				drawArea->plotPixel(x, y, c);
				err += dx;
				if (err > dy) {
					x += sx;
					err -= dy;
				}
			}
		}
	}

	void DrawTask::drawCircleTrig(int x0, int y0, float r, Colour c) {
		float dtheta = 1.0 / r;
		for (float theta = 0.0; theta < 2 * 3.1415926535; theta += dtheta) {
			drawArea->plotPixel(x0 + int(r * cosf(theta)), y0 + int(r * sinf(theta)), c);
		}
	}

	void DrawTask::update(float dt){
		//drawArea->clear(Colour(255,255,255,255));

		app->getRenderer()->reloadTexture(drawArea);
	}

}
