#include "StickFigure.h"
#include "T3DApplication.h"
#include "Capsule.h"
#include "Sphere.h"
#include "Animation.h"

namespace T3D {
	StickFigure::StickFigure(T3DApplication *app, float _limbLength, float _limbRadius, float _torsoLength, float _torsoRadius, float _collarWidth, float _pelvisWidth, float _headRadius, Material *mat, Transform *root) :GameObject(app) {
		limbLength = _limbLength;
		limbRadius = _limbRadius;
		torsoLength = _torsoLength;
		torsoRadius = _torsoRadius;
		collarWidth = _collarWidth;
		pelvisWidth = _pelvisWidth;
		headRadius = _headRadius;

		setMesh(new Capsule(torsoRadius, torsoLength, 16));
		getTransform()->setParent(root);
		getTransform()->name = "Stick Figure";
		setMaterial(mat);

		leftThigh = new GameObject(app);
		leftThigh->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftThigh->getTransform()->setParent(getTransform());
		leftThigh->getTransform()->name = "Left Thigh";
		leftThigh->setMaterial(mat);

		leftCalf = new GameObject(app);
		leftCalf->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftCalf->getTransform()->setParent(leftThigh->getTransform());
		leftCalf->getTransform()->name = "Left Calf";
		leftCalf->setMaterial(mat);

		rightThigh = new GameObject(app);
		rightThigh->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightThigh->getTransform()->setParent(getTransform());
		rightThigh->getTransform()->name = "Right Thigh";
		rightThigh->setMaterial(mat);

		rightCalf = new GameObject(app);
		rightCalf->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightCalf->getTransform()->setParent(rightThigh->getTransform());
		rightCalf->getTransform()->name = "Right Calf";
		rightCalf->setMaterial(mat);

		collarJoint = new GameObject(app);
		collarJoint->getTransform()->setParent(getTransform());
		collarJoint->getTransform()->name = "Collar Joint";

		leftUpperArm = new GameObject(app);
		leftUpperArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftUpperArm->getTransform()->setParent(collarJoint->getTransform());
		leftUpperArm->getTransform()->name = "Left UpperArm";
		leftUpperArm->setMaterial(mat);

		leftForeArm = new GameObject(app);
		leftForeArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		leftForeArm->getTransform()->setParent(leftUpperArm->getTransform());
		leftForeArm->getTransform()->name = "Left ForeArm";
		leftForeArm->setMaterial(mat);

		rightUpperArm = new GameObject(app);
		rightUpperArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightUpperArm->getTransform()->setParent(collarJoint->getTransform());
		rightUpperArm->getTransform()->name = "Right UpperArm";
		rightUpperArm->setMaterial(mat);

		rightForeArm = new GameObject(app);
		rightForeArm->setMesh(new Capsule(limbRadius, limbLength, 16));
		rightForeArm->getTransform()->setParent(rightUpperArm->getTransform());
		rightForeArm->getTransform()->name = "Right ForeArm";
		rightForeArm->setMaterial(mat);

		head = new GameObject(app);
		head->setMesh(new Sphere(headRadius, 16));
		// planning on fight poses, in which a stable head position should look best
		head->getTransform()->setParent(getTransform());
		head->getTransform()->name = "Head";
		head->setMaterial(mat);

		leftThigh->getTransform()->setLocalPosition(Vector3(-pelvisWidth, 0, 0));
		leftCalf->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		rightThigh->getTransform()->setLocalPosition(Vector3(pelvisWidth, 0, 0));
		rightCalf->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		collarJoint->getTransform()->setLocalPosition(Vector3(0, torsoLength, 0));
		leftUpperArm->getTransform()->setLocalPosition(Vector3(-collarWidth, 0, 0));
		leftForeArm->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		rightUpperArm->getTransform()->setLocalPosition(Vector3(collarWidth, 0, 0));
		rightForeArm->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		head->getTransform()->setLocalPosition(Vector3(0, torsoLength + headRadius, 0));

		setPose(Vector3(0, 0, 0), Poses::NEUTRAL);

		anim = new Animation(2.0f);
		addComponent(anim);
		poses.anim = anim;

		poses.poses.push_back(Poses::WAVE[0]);
		poses.positions.push_back(Vector3(0, 0, 0));
		poses.times.push_back(0);

		poses.poses.push_back(Poses::WAVE[1]);
		poses.positions.push_back(Vector3(0, 0, 0));
		poses.times.push_back(1);

		poses.poses.push_back(Poses::WAVE[0]);
		poses.positions.push_back(Vector3(0, 0, 0));
		poses.times.push_back(2);

		//startAnimation();
	}

	void StickFigure::startAnimation() {
		for (unsigned i = 0; i < poses.poses.size(); i++) {
			appendPose(anim, poses.positions[i], poses.poses[i], poses.times[i]);
		}
		anim->loop(true);
		anim->play();
	}

	void StickFigure::setPose(Vector3 position, const Poses::Pose pose) {
		getTransform()->setLocalPosition(position);

		getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::PELVIS]));
		leftThigh->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::LTHIGH]));
		leftCalf->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::LCALF]));
		rightThigh->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::RTHIGH]));
		rightCalf->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::RCALF]));
		collarJoint->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::COLLAR]));
		leftUpperArm->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::LUPPERARM]));
		leftForeArm->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::LFOREARM]));
		rightUpperArm->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::RUPPERARM]));
		rightForeArm->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::RFOREARM]));
		head->getTransform()->setLocalRotation(Quaternion(Math::HALF_PI * pose[Poses::HEAD]));
	}

	void StickFigure::appendPose(Animation *anim, Vector3 position, const Poses::Pose pose, float time) {
		anim->addKey("Stick Figure", time, Quaternion(Math::HALF_PI * pose[Poses::PELVIS]), position);
		anim->addKey("Left Thigh", time, Quaternion(Math::HALF_PI * pose[Poses::LTHIGH]), leftThigh->getTransform()->getLocalPosition());
		anim->addKey("Left Calf", time, Quaternion(Math::HALF_PI * pose[Poses::LCALF]), leftCalf->getTransform()->getLocalPosition());
		anim->addKey("Right Thigh", time, Quaternion(Math::HALF_PI * pose[Poses::RTHIGH]), rightThigh->getTransform()->getLocalPosition());
		anim->addKey("Right Calf", time, Quaternion(Math::HALF_PI * pose[Poses::RCALF]), rightCalf->getTransform()->getLocalPosition());
		anim->addKey("Collar Joint", time, Quaternion(Math::HALF_PI * pose[Poses::COLLAR]), collarJoint->getTransform()->getLocalPosition());
		anim->addKey("Left UpperArm", time, Quaternion(Math::HALF_PI * pose[Poses::LUPPERARM]), leftUpperArm->getTransform()->getLocalPosition());
		anim->addKey("Left ForeArm", time, Quaternion(Math::HALF_PI * pose[Poses::LFOREARM]), leftForeArm->getTransform()->getLocalPosition());
		anim->addKey("Right UpperArm", time, Quaternion(Math::HALF_PI * pose[Poses::RUPPERARM]), rightUpperArm->getTransform()->getLocalPosition());
		anim->addKey("Right ForeArm", time, Quaternion(Math::HALF_PI * pose[Poses::RFOREARM]), rightForeArm->getTransform()->getLocalPosition());
		anim->addKey("Head", time, Quaternion(Math::HALF_PI * pose[Poses::HEAD]), head->getTransform()->getLocalPosition());
	}

	StickFigure::~StickFigure() {
	}
}