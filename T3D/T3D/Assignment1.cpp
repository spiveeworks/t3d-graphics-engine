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
#include "ChipInWall.h"

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
		bat->getTransform()->setLocalPosition(Vector3(-6, 0, 0));
		bat->getTransform()->setLocalScale(Vector3(0.1, 0.1, 0.1));
		bat->getTransform()->setParent(root);

		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8f, 0.8f, 0.8f, 1);
		StickFigure *person = new StickFigure(this, 1, 0.15f, 2, 0.2f, 0.05, 0.05, 0.5, grey);
		person->getTransform()->setLocalPosition(Vector3(-2, 0, 0));
		person->getTransform()->setParent(root);

		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 0.8f, 0, 1);
		GameObject *wall1 = new GameObject(this);
		wall1->setMesh(new HoleInWall(Vector3(2.0f, 2.0f, 0.2f), 0.0f, 0.0f, 1.0f, 27));
		wall1->getTransform()->setLocalPosition(Vector3(2, 0, 0));
		wall1->getTransform()->name = "Hole In The Wall";
		wall1->setMaterial(green);
		wall1->getTransform()->setParent(root);

		green->setDiffuse(0, 0.8f, 0, 1);
		GameObject *wall2 = new GameObject(this);
		wall2->setMesh(new ChipInWall(Vector3(2.0f, 2.0f, 0.2f), 0.0f, 0.0f, 1.0f, 0.07f, 27));
		wall2->getTransform()->setLocalPosition(Vector3(8, 0, 0));
		wall2->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::PI, 0)));
		wall2->getTransform()->name = "Chip In The Wall";
		wall2->setMaterial(green);
		wall2->getTransform()->setParent(root);

		return true;
	}
}
