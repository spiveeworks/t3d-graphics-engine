// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Tutorial1.cpp
//
// Base application for tutorial 1.  Used in conjunction with DrawTask, a task for drawing onto a 2D texture.

#include "Assignment1.h"
#include "Camera.h"
#include "keyboardcontroller.h"
#include "CricketBat.h"
#include "StickFigure.h"
#include "HoleInWall.h"

namespace T3D{

	Assignment1::Assignment1(void)
	{
		drawArea = new Texture(1024,640,false);
		drawArea->clear(Colour(255,255,255,255));
	}


	Assignment1::~Assignment1(void)
	{
	}

	bool Assignment1::init() {
		WinGLApplication::init();
		
		GameObject *lightObj = new GameObject(this);
		Light *light = new Light(Light::DIRECTIONAL);
		light->setAmbient(1, 1, 1);
		light->setDiffuse(1, 1, 1);
		light->setSpecular(1, 1, 1);
		lightObj->setLight(light);
		lightObj->getTransform()->
			setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
		lightObj->getTransform()->setParent(root);

		//add a camera to the scene
		//This camera is super fast... you have been warned
		GameObject *camObj = new GameObject(this);
		renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(0, 0.5, 3));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		camObj->addComponent(new KeyboardController());

		Material *wood = renderer->createMaterial(Renderer::PR_OPAQUE);
		wood->setDiffuse(0.9f, 0.8f, 0.7f, 1);
		Material *carbonfibre = renderer->createMaterial(Renderer::PR_OPAQUE);
		carbonfibre->setDiffuse(0.2, 0.2, 0.2, 1);
		carbonfibre->setShininess(10);
		carbonfibre->setSpecular(0.1f, 0.1f, 0.1f, 1.0f);
		CricketBat *bat = new CricketBat(this, wood, carbonfibre);
		bat->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		bat->getTransform()->setLocalScale(Vector3(0.1, 0.1, 0.1));
		bat->getTransform()->setParent(root);

		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8f, 0.8f, 0.8f, 1);
		StickFigure *person = new StickFigure(this, 1, 0.15f, 2, 0.2f, 0.05, 0.05, 0.5, grey);
		person->getTransform()->setLocalPosition(Vector3(4, 0, 0));
		person->getTransform()->setParent(root);

		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 0.8f, 0, 1);
		GameObject *wall = new GameObject(this);
		wall->setMesh(new HoleInWall(Vector3(), 0.0f, 0.0f, 1.0f, 27));
		wall->getTransform()->setLocalPosition(Vector3(8, 0, 0));
		wall->getTransform()->name = "Hole In The Wall";
		wall->setMaterial(green);
		wall->getTransform()->setParent(root);

		return true;
	}
}
