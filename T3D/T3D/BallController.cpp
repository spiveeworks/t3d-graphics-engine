
#include "BallController.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Transform.h"
#include "Math.h"

namespace T3D
{
	void BallController::update(float dt){
		time += dt;

		float time0 = 8.15f, time1 = 8.5f, time2 = 9.6f, time3 = 20.5f;
		Vector3 pos0 = Vector3(5, 5, 30), pos1 = Vector3(-2, 2, 0), pos2 = Vector3(-21.5, -2, -21.5);
		if (time < time0 || time > time3) {
			gameObject->getTransform()->setParent(bowler->joints[Poses::RFOREARM]->getTransform());
			gameObject->getTransform()->setLocalPosition(Vector3(0, 1, 0));
		}
		else if (time < time1) {
			gameObject->getTransform()->setParent(root);
			gameObject->getTransform()->setLocalPosition(pos0 + (pos1 - pos0) * (time - time0) / (time1 - time0));
		}
		else if (time < time2) {
			gameObject->getTransform()->setParent(root);
			gameObject->getTransform()->setLocalPosition(pos1 + (pos2 - pos1) * (time - time1) / (time2 - time1));
		}
		else {
			gameObject->getTransform()->setParent(root);
			gameObject->getTransform()->setLocalPosition(pos2);
		}
	}
}
