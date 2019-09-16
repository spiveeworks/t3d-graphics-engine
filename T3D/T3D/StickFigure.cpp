#include "StickFigure.h"
#include "T3DApplication.h"
#include "Capsule.h"
#include "Sphere.h"

namespace T3D {
	StickFigure::StickFigure(T3DApplication *app, float limbLength, float limbRadius, float torsoLength, float torsoRadius, float collarWidth, float pelvisWidth, float headRadius, Material *mat) :GameObject(app) {
		setMesh(new Capsule(torsoRadius, torsoLength, 16));
		getTransform()->name = "StickFigure";
		setMaterial(mat);

		leftThigh = new GameObject(app);
		leftThigh->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftThigh->getTransform()->setParent(getTransform());
		leftThigh->getTransform()->setLocalPosition(Vector3(-pelvisWidth, 0, 0));
		leftThigh->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, 0.8f * Math::PI)));
		leftThigh->getTransform()->name = "Left Thigh";
		leftThigh->setMaterial(mat);

		leftCalf = new GameObject(app);
		leftCalf->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftCalf->getTransform()->setParent(leftThigh->getTransform());
		leftCalf->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		leftCalf->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, 0.1f * Math::PI)));
		leftCalf->getTransform()->name = "Left Calf";
		leftCalf->setMaterial(mat);

		rightThigh = new GameObject(app);
		rightThigh->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightThigh->getTransform()->setParent(getTransform());
		rightThigh->getTransform()->setLocalPosition(Vector3(pelvisWidth, 0, 0));
		rightThigh->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -0.8f * Math::PI)));
		rightThigh->getTransform()->name = "Right Thigh";
		rightThigh->setMaterial(mat);

		rightCalf = new GameObject(app);
		rightCalf->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightCalf->getTransform()->setParent(rightThigh->getTransform());
		rightCalf->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		rightCalf->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -0.1f * Math::PI)));
		rightCalf->getTransform()->name = "Right Calf";
		rightCalf->setMaterial(mat);

		collarJoint = new GameObject(app);
		collarJoint->getTransform()->setParent(getTransform());
		collarJoint->getTransform()->setLocalPosition(Vector3(0, torsoLength, 0));
		rightCalf->getTransform()->name = "Collar Joint";

		leftUpperArm = new GameObject(app);
		leftUpperArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftUpperArm->getTransform()->setParent(collarJoint->getTransform());
		leftUpperArm->getTransform()->setLocalPosition(Vector3(-collarWidth, 0, 0));
		leftUpperArm->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, 0.8f * Math::PI)));
		leftUpperArm->getTransform()->name = "Left UpperArm";
		leftUpperArm->setMaterial(mat);

		leftForeArm = new GameObject(app);
		leftForeArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftForeArm->getTransform()->setParent(leftUpperArm->getTransform());
		leftForeArm->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		leftForeArm->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, 0.1f * Math::PI)));
		leftForeArm->getTransform()->name = "Left ForeArm";
		leftForeArm->setMaterial(mat);

		rightUpperArm = new GameObject(app);
		rightUpperArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightUpperArm->getTransform()->setParent(collarJoint->getTransform());
		rightUpperArm->getTransform()->setLocalPosition(Vector3(collarWidth, 0, 0));
		rightUpperArm->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -0.8f * Math::PI)));
		rightUpperArm->getTransform()->name = "Right UpperArm";
		rightUpperArm->setMaterial(mat);

		rightForeArm = new GameObject(app);
		rightForeArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightForeArm->getTransform()->setParent(rightUpperArm->getTransform());
		rightForeArm->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		rightForeArm->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -0.1f * Math::PI)));
		rightForeArm->getTransform()->name = "Right ForeArm";
		rightForeArm->setMaterial(mat);

		head = new GameObject(app);
		head->setMesh(new Sphere(headRadius, 16));
		// planning on fight poses, in which a stable head position should look best
		head->getTransform()->setParent(getTransform());
		head->getTransform()->setLocalPosition(Vector3(0, torsoLength + headRadius, 0));
		head->getTransform()->name = "Head";
		head->setMaterial(mat);
	}

	StickFigure::~StickFigure() {
	}
}