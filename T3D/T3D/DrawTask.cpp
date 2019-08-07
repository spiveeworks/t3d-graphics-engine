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
		float triheight = sqrtf(1.0f * 1.0f - 0.5f * 0.5f);
		poly = {
			Vector3(1.0f, 0.0f, 1.0f),
			Vector3(0.5f, triheight, 1.0f),
			Vector3(-0.5f, triheight, 1.0f),
			Vector3(-1.0f, 0.0f, 1.0f),
			Vector3(-0.5f, -triheight, 1.0f),
			Vector3(0.5f, -triheight, 1.0f),
		};
		time = 0.0f;
		init();
	}


	DrawTask::~DrawTask(void)
	{
	}

	void DrawTask::init(){		
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
		for (float theta = 0.0; theta < 3.1415926535 / 4.0; theta += dtheta) {
			int dx = int(r * cosf(theta));
			int dy = int(r * sinf(theta));
			drawArea->plotPixel(x0 + dx, y0 + dy, c);
			drawArea->plotPixel(x0 + dy, y0 + dx, c);
			drawArea->plotPixel(x0 + dx, y0 - dy, c);
			drawArea->plotPixel(x0 + dy, y0 - dx, c);
			drawArea->plotPixel(x0 - dx, y0 + dy, c);
			drawArea->plotPixel(x0 - dy, y0 + dx, c);
			drawArea->plotPixel(x0 - dx, y0 - dy, c);
			drawArea->plotPixel(x0 - dy, y0 - dx, c);
		}
	}

	void DrawTask::drawCirclePythag(int x0, int y0, int r, Colour c) {
		float dtheta = 1.0 / r;
		int dy = r;
		for (int dx = 0; dx < dy; dx++) {
			dy = int(sqrt(r*r - dx * dx));
			drawArea->plotPixel(x0 + dx, y0 + dy, c);
			drawArea->plotPixel(x0 + dy, y0 + dx, c);
			drawArea->plotPixel(x0 + dx, y0 - dy, c);
			drawArea->plotPixel(x0 + dy, y0 - dx, c);
			drawArea->plotPixel(x0 - dx, y0 + dy, c);
			drawArea->plotPixel(x0 - dy, y0 + dx, c);
			drawArea->plotPixel(x0 - dx, y0 - dy, c);
			drawArea->plotPixel(x0 - dy, y0 - dx, c);
		}
	}

	void DrawTask::drawCircleBres(int x0, int y0, int r, Colour c) {
		float dtheta = 1.0 / r;
		int dy = r;
		for (int dx = 0; dx < dy; dx++) {
			if (dx*dx + dy * dy > r*r) {
				dy -= 1;
			}
			drawArea->plotPixel(x0 + dx, y0 + dy, c);
			drawArea->plotPixel(x0 + dy, y0 + dx, c);
			drawArea->plotPixel(x0 + dx, y0 - dy, c);
			drawArea->plotPixel(x0 + dy, y0 - dx, c);
			drawArea->plotPixel(x0 - dx, y0 + dy, c);
			drawArea->plotPixel(x0 - dy, y0 + dx, c);
			drawArea->plotPixel(x0 - dx, y0 - dy, c);
			drawArea->plotPixel(x0 - dy, y0 - dx, c);
		}
	}

	void DrawTask::drawTriFan(vector<Vector3> points, Vector3 offset) {
		Vector3 c = offset + points[0];
		Vector3 p1 = offset + points[1];
		drawBresLine(c.x, c.y, p1.x, p1.y, Colour(0, 0, 0, 255));
		for (int i = 1; i < poly.size(); i++) {
			Vector3 p2 = offset + points[i];
			drawBresLine(c.x, c.y, p2.x, p2.y, Colour(0, 0, 0, 255));
			drawBresLine(p1.x, p1.y, p2.x, p2.y, Colour(0, 0, 0, 255));
			p1 = p2;
		}
	}

	void DrawTask::drawPie(int cx, int cy, int r, float theta) {

	}

	void DrawTask::update(float dt){
		drawArea->clear(Colour(255, 255, 255, 255));

		time += dt;
		float rotate = time;
		Matrix3x3 rotateMat = Matrix3x3(
			cosf(rotate), -sinf(rotate), 0.0f,
			sinf(rotate), cosf(rotate), 0.0f,
			0.0f, 0.0f, 1.0f
		);
		Matrix3x3 scaleMat = Matrix3x3(
			100.0f, 0.0f, 0.0f,
			0.0f, 100.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);
		Matrix3x3 animation = scaleMat * rotateMat;

		alloc.clear();
		for (auto each : poly) {
			alloc.push_back(animation * each);
		}
		drawTriFan(alloc, Vector3(400.0, 300.0, 1.0));

		app->getRenderer()->reloadTexture(drawArea);
	}

}
