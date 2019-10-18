#include <iostream>

#include "TimingCamera.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Transform.h"
#include "Math.h"

namespace T3D
{
	void TimingCamera::update(float dt){
		time += dt;

		if (time < 6.5f) {
			gameObject->getTransform()->setLocalPosition(Vector3(0, 4, 75));
		}
		else if (time < 15.0f) {
			gameObject->getTransform()->setLocalPosition(Vector3(50, 15, 15));
			gameObject->getTransform()->setLocalRotation(Quaternion(Vector3(-0.2, 1, 0) * Math::HALF_PI));
		}
		else {
			gameObject->getTransform()->setLocalPosition(Vector3(-40, 15, -40));
			gameObject->getTransform()->setLocalRotation(Quaternion(Vector3(-0.2f, -1.5f, 0) * Math::HALF_PI));
		}
	}
}
