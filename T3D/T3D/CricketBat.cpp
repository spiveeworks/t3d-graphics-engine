#include "CricketBat.h"
#include "T3DApplication.h"
#include "Cylinder.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {
	CricketBat::CricketBat(T3DApplication *app, Material *mat) :GameObject(app) {
		getTransform()->name = "CricketBat";
		setMaterial(mat);

		std::vector<Vector3> handleProfile;
		SweepPath handlesp;
		{
			float ridges = 8.0f;
			float ridgeWidth = Math::TWO_PI / ridges;
			float lowPortion = 0.2f;
			float slopePortion = 0.1f;
			float lowRadius = 1.0f;
			float highRadius = 1.05f;
			for (float ridge = 0; ridge < ridges; ridge++) {
				auto add = [&](float r, float theta) { handleProfile.push_back(Vector3(r * cos(theta), r * sin(theta), 0.0f)); };
				add(lowRadius, ridge * ridgeWidth);
				add(lowRadius, (ridge + lowPortion) * ridgeWidth);
				add(highRadius, (ridge + lowPortion + slopePortion) * ridgeWidth);
				add(highRadius, (ridge + (1.0f - slopePortion)) * ridgeWidth);
			}

			Transform t;

			t.setLocalPosition(Vector3(0, 0, 0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));

			float pommelSize = 1.1f;
			float x;
			float y;
			for (float i = 0.0f; i <= 12.0f; i += 1.0f) {
				x = pommelSize * cos((20.0f - i) * 0.05f * Math::PI);
				y = pommelSize * sin((20.0f - i) * 0.05f * Math::PI);
				t.setLocalScale(Vector3(y, y, 1.0));
				t.setLocalPosition(Vector3(x, 0, 0));
				handlesp.addTransform(t);
			}

			float handleTwirl = 2 * Math::TWO_PI / ridges;
			float handleLength = 5.0f;
			for (float i = 1.0f; i <= 10.0f; i += 1.0f) {
				t.setLocalScale(Vector3(y, y, 1.0));
				t.setLocalPosition(Vector3(x + handleLength * (i / 10.0f), 0, 0));
				t.setLocalRotation(Quaternion(Quaternion(Vector3(i * handleTwirl / 10.0f, 0, 0)) * Quaternion(Vector3(0, Math::PI / 2, 0))));
				handlesp.addTransform(t);
			}
			handlesp.addTransform(t);

			//Adjust the scale for the final 'cap':
			t.setLocalScale(Vector3(0, 0, 1.0));
			handlesp.addTransform(t);
		}

		handle = new GameObject(app);
		handle->setMesh(new Sweep(handleProfile, handlesp, true));
		handle->getTransform()->setParent(getTransform());
		handle->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		handle->getTransform()->name = "handle";
		handle->setMaterial(mat);

		blade = new GameObject(app);
		blade->getTransform()->setParent(getTransform());
		blade->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		blade->getTransform()->name = "blade";
		blade->setMaterial(mat);

		/*
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
		*/
	}

	CricketBat::~CricketBat() {
	}
}