// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Tutorial1.cpp
//
// Base application for tutorial 1.  Used in conjunction with DrawTask, a task for drawing onto a 2D texture.

#include "Assignment2.h"
#include "Camera.h"
#include "keyboardcontroller.h"
#include "KeyboardEditor.h"
#include "Scene.h"

namespace T3D{

	Assignment2::Assignment2(void)
	{
		drawArea = new Texture(1024,640,false);
		drawArea->clear(Colour(255,255,255,255));
	}


	Assignment2::~Assignment2(void)
	{
	}

	bool Assignment2::init() {
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
		renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1f, 500.0f, 45.0f, 1.6f);
		camObj->getTransform()->setLocalPosition(Vector3(0, 0.5, 3));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		camObj->addComponent(new KeyboardController());

		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8f, 0.8f, 0.8f, 1);
		Scene*scene = new Scene(this);
		KeyboardEditor *editor = new KeyboardEditor(&scene->figures, this, grey, root);
		scene->addComponent(editor);
		editor->loadPoses();

		return true;
	}
}
