#include "StickFigure.h"
#include "T3DApplication.h"
#include "Capsule.h"
#include "Sphere.h"
#include "Animation.h"

namespace T3D {
	const char* StickFigure::JOINT_NAMES[Poses::NUMJOINTS] = {
		"Left Thigh",
		"Left Calf",
		"Right Thigh",
		"Right Calf",
		"Collar Joint",
		"Left UpperArm",
		"Left ForeArm",
		"Right UpperArm",
		"Right ForeArm",
		"Head"
	};

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

		for (unsigned i = 0; i < Poses::NUMJOINTS; i++) {
			joints[i] = new GameObject(app);
			joints[i]->getTransform()->name = JOINT_NAMES[i];
			joints[i]->setMaterial(mat);
		}

		joints[Poses::LTHIGH]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::LTHIGH]->getTransform()->setParent(getTransform());

		joints[Poses::LCALF]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::LCALF]->getTransform()->setParent(joints[Poses::LTHIGH]->getTransform());

		joints[Poses::RTHIGH]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::RTHIGH]->getTransform()->setParent(getTransform());

		joints[Poses::RCALF]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::RCALF]->getTransform()->setParent(joints[Poses::RTHIGH]->getTransform());

		joints[Poses::COLLAR]->getTransform()->setParent(getTransform());

		joints[Poses::LUPPERARM]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::LUPPERARM]->getTransform()->setParent(joints[Poses::COLLAR]->getTransform());

		joints[Poses::LFOREARM]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::LFOREARM]->getTransform()->setParent(joints[Poses::LUPPERARM]->getTransform());

		joints[Poses::RUPPERARM]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::RUPPERARM]->getTransform()->setParent(joints[Poses::COLLAR]->getTransform());

		joints[Poses::RFOREARM]->setMesh(new Capsule(limbRadius, limbLength, 16));
		joints[Poses::RFOREARM]->getTransform()->setParent(joints[Poses::RUPPERARM]->getTransform());

		joints[Poses::HEAD]->setMesh(new Sphere(headRadius, 16));
		// planning on fight poses, in which a stable joints[Poses::HEAD] position should look best
		joints[Poses::HEAD]->getTransform()->setParent(getTransform());

		joints[Poses::LTHIGH]->getTransform()->setLocalPosition(Vector3(-pelvisWidth, 0, 0));
		joints[Poses::LCALF]->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		joints[Poses::RTHIGH]->getTransform()->setLocalPosition(Vector3(pelvisWidth, 0, 0));
		joints[Poses::RCALF]->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		joints[Poses::COLLAR]->getTransform()->setLocalPosition(Vector3(0, torsoLength, 0));
		joints[Poses::LUPPERARM]->getTransform()->setLocalPosition(Vector3(-collarWidth, 0, 0));
		joints[Poses::LFOREARM]->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		joints[Poses::RUPPERARM]->getTransform()->setLocalPosition(Vector3(collarWidth, 0, 0));
		joints[Poses::RFOREARM]->getTransform()->setLocalPosition(Vector3(0, limbLength, 0));
		joints[Poses::HEAD]->getTransform()->setLocalPosition(Vector3(0, torsoLength + headRadius, 0));

		setPose(Vector3(0, 0, 0), Vector3(0, 0, 0), Poses::NEUTRAL);

		anim = new Animation(30);
		addComponent(anim);
		poses.anim = anim;
	}

	void StickFigure::startAnimation(float time) {
		anim->clearKeys();

		for (unsigned i = 0; i < poses.poses.size(); i++) {
			appendPose(anim, poses.positions[i], poses.orientations[i], poses.poses[i], poses.times[i]);
		}
		anim->loop(false);
		anim->play(time);
	}

	void StickFigure::setPose(Vector3 position, Vector3 orientation, const Poses::Pose pose) {
		getTransform()->setLocalPosition(position);

		Quaternion body_conj = Quaternion(Math::HALF_PI * Poses::CONJUGATOR[Poses::HEAD]),
			ori = Quaternion(Math::HALF_PI * orientation),
			body_rot = body_conj * ori / body_conj;
		getTransform()->setLocalRotation(body_rot);
		for (unsigned i = 0; i < Poses::NUMJOINTS; i++) {
			Quaternion ref = Quaternion(Math::HALF_PI * Poses::REFERENCE[i]),
				conj = Quaternion(Math::HALF_PI * Poses::CONJUGATOR[i]),
				joint = Quaternion(Math::HALF_PI * pose[i]),
				rot = ref * conj * joint / conj;

			joints[i]->getTransform()->setLocalRotation(rot);
		}
	}

	void StickFigure::appendPose(Animation *anim, Vector3 position, Vector3 orientation, const Poses::Pose pose, float time) {
		Quaternion body_conj = Quaternion(Math::HALF_PI * Poses::CONJUGATOR[Poses::HEAD]),
			ori = Quaternion(Math::HALF_PI * orientation),
			body_rot = body_conj * ori / body_conj;
		anim->addKey("Stick Figure", time, body_rot, position);
		for (unsigned i = 0; i < Poses::NUMJOINTS; i++) {
			Quaternion ref = Quaternion(Math::HALF_PI * Poses::REFERENCE[i]),
				conj = Quaternion(Math::HALF_PI * Poses::CONJUGATOR[i]),
				joint = Quaternion(Math::HALF_PI * pose[i]),
				rot = ref * conj * joint / conj;
			anim->addKey(JOINT_NAMES[i], time, rot, joints[i]->getTransform()->getLocalPosition());
		}
	}
}