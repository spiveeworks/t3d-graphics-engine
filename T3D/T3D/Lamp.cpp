#include "Lamp.h"
#include "T3DApplication.h"
#include "Cylinder.h"

namespace T3D {
	Lamp::Lamp(T3DApplication *app) :GameObject(app) {
		setMesh(new Cylinder(.1, .01, 16));
		getTransform()->name = "Lamp";

		base = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
		base->setMesh(new Cylinder(.02, .01, 16));
		base->getTransform()->setParent(getTransform()); // attaching this piece to the Lamp object's transform
		base->getTransform()->setLocalPosition(Vector3(0, 0.02, 0));
		base->getTransform()->name = "Base";
	}

	Lamp::~Lamp() {
	}
}