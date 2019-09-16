#include "StickFigure.h"
#include "T3DApplication.h"
#include "Capsule.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {
	StickFigure::StickFigure(T3DApplication *app, Material *mat) :GameObject(app) {
		setMesh(new Capsule(.1, .01, 16));
		getTransform()->name = "StickFigure";
		setMaterial(mat);

		base = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
		base->setMesh(new Capsule(.02, .01, 16));
		base->getTransform()->setParent(getTransform()); // attaching this piece to the StickFigure object's transform
		base->getTransform()->setLocalPosition(Vector3(0, 0.02, 0));
		base->getTransform()->name = "Base";
		base->setMaterial(mat);

		std::vector<Vector3> armProfile;
		SweepPath armsp;
		{
			armProfile.push_back(Vector3(0.0f, -0.12f, 0.0f));
			armProfile.push_back(Vector3(0.014f, -0.114f, 0.0f));
			armProfile.push_back(Vector3(0.02f, -0.1f, 0.0f));
			armProfile.push_back(Vector3(0.02f, 0.1f, 0.0f));
			armProfile.push_back(Vector3(0.014f, 0.114f, 0.0f));
			armProfile.push_back(Vector3(0.0f, 0.12f, 0.0f));
			armProfile.push_back(Vector3(-0.014f, 0.114f, 0.0f));
			armProfile.push_back(Vector3(-0.02f, 0.1f, 0.0f));
			armProfile.push_back(Vector3(-0.02f, -0.1f, 0.0f));
			armProfile.push_back(Vector3(-0.014f, -0.114f, 0.0f));

			Transform t;

			t.setLocalPosition(Vector3(-0.01, 0, 0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
			t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
			armsp.addTransform(t);

			//Adjust the scale for the next path instance :
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//Adjust the position and scale for the next path instance :
			t.setLocalPosition(Vector3(-0.0075, 0, 0));
			t.setLocalScale(Vector3(1, 1, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//Adjust the position for the next path instance :
			t.setLocalPosition(Vector3(0.0075, 0, 0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//Adjust the position for the next path instance :
			t.setLocalPosition(Vector3(0.01, 0, 0));
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//Adjust the scale for the final 'cap':
			t.setLocalScale(Vector3(0, 0, 1.0));
			armsp.addTransform(t);
		}

		baseJoint = new GameObject(app);
		baseJoint->getTransform()->setParent(base->getTransform());
		baseJoint->getTransform()->name = "BaseJoint";

		elbowJoint = new GameObject(app);
		elbowJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
		elbowJoint->getTransform()->setParent(baseJoint->getTransform());
		elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0))); // this rotation is just to make a good starting pose
		elbowJoint->getTransform()->name = "ElbowJoint";

		shadeJoint = new GameObject(app);
		shadeJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
		shadeJoint->getTransform()->setParent(elbowJoint->getTransform());
		shadeJoint->getTransform()->name = "ShadeJoint";

		arm1 = new GameObject(app);
		arm1->setMesh(new Sweep(armProfile, armsp, false));
		arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm1->getTransform()->setParent(baseJoint->getTransform());
		arm1->getTransform()->name = "Arm1";
		arm1->setMaterial(mat);

		arm2 = new GameObject(app);
		arm2->setMesh(new Sweep(armProfile, armsp, false));
		arm2->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm2->getTransform()->setParent(elbowJoint->getTransform());
		arm2->getTransform()->name = "Arm2";
		arm2->setMaterial(mat);

		std::vector<Vector3> shadeProfile;
		SweepPath shadesp;
		{
			shadeProfile.push_back(Vector3(0.00f, -0.03f, 0.0f));
			shadeProfile.push_back(Vector3(0.03f, -0.02f, 0.0f));
			shadeProfile.push_back(Vector3(0.032f, 0.03f, 0.0f));
			shadeProfile.push_back(Vector3(0.061f, 0.06f, 0.0f));
			shadeProfile.push_back(Vector3(0.07f, 0.08f, 0.0f));
			shadeProfile.push_back(Vector3(0.07f, 0.08f, 0.0f));
			shadeProfile.push_back(Vector3(0.069f, 0.08f, 0.0f));
			shadeProfile.push_back(Vector3(0.069f, 0.08f, 0.0f));
			shadeProfile.push_back(Vector3(0.059f, 0.06f, 0.0f));
			shadeProfile.push_back(Vector3(0.031f, 0.03f, 0.0f));
			shadeProfile.push_back(Vector3(0.031f, 0.03f, 0.0f));
			shadeProfile.push_back(Vector3(0.0f, 0.03f, 0.0f));

			Transform t;

			shadesp.makeCirclePath(0.0f, 8);
		}

		shadeJoint->setMesh(new Sweep(shadeProfile, shadesp, true));
		shadeJoint->getTransform()->setLocalScale(Vector3(1.6, 1.6, 1.6));
		shadeJoint->setMaterial(mat);
	}

	StickFigure::~StickFigure() {
	}
}