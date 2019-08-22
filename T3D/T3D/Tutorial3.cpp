// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Tutorial1.cpp
//
// Base application for tutorial 1.  Used in conjunction with DrawTask, a task for drawing onto a 2D texture.

#include "Tutorial3.h"
#include "Camera.h"
#include "keyboardcontroller.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Lamp.h"

namespace T3D{

	Tutorial3::Tutorial3(void)
	{
		drawArea = new Texture(1024,640,false);
		drawArea->clear(Colour(255,255,255,255));
	}


	Tutorial3::~Tutorial3(void)
	{
	}

	bool Tutorial3::init() {
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

		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 1, 0, 1);

		GameObject *pyramid = new GameObject(this);
		pyramid->setMesh(new Pyramid(1, 1));
		pyramid->setMaterial(green);
		pyramid->getTransform()->setLocalPosition(Vector3(-2, 0, 0));
		pyramid->getTransform()->setParent(root);
		pyramid->getTransform()->name = "Pyramid";

		GameObject *cylinder = new GameObject(this);
		cylinder->setMesh(new Cylinder(1, 1, 50));
		cylinder->setMaterial(green);
		cylinder->getTransform()->setLocalPosition(Vector3(2, 0, 0));
		cylinder->getTransform()->setParent(root);
		cylinder->getTransform()->name = "Pyramid";

		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8, 0.8, 0.9, 1);
		Lamp *lamp = new Lamp(this);
		lamp->setMaterial(grey);
		lamp->base->setMaterial(grey);
		lamp->arm1->setMaterial(grey);
		lamp->arm2->setMaterial(grey);
		lamp->shadeJoint->setMaterial(grey);
		lamp->getTransform()->setLocalPosition(Vector3(4, 0, 0));
		lamp->getTransform()->setParent(root);

		lamp->baseJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 10, Math::PI / 4, 0)));
		lamp->shadeJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0)));

		return true;
	}
}
