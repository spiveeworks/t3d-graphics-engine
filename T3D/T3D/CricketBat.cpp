#include "CricketBat.h"
#include "T3DApplication.h"
#include "Cylinder.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {
	CricketBat::CricketBat(T3DApplication *app, Material *bladeMat, Material *handleMat) :GameObject(app) {
		getTransform()->name = "CricketBat";
		
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

			float handleTwirl = 2 * Math::TWO_PI / ridges;
			float handleLength = 7.0f;
			for (float i = 0.0f; i <= 10.0f; i += 1.0f) {
				if (i == 0.0f) {
					t.setLocalScale(Vector3(2.0f, 1.0f, 1.0));
				} else if (i == 1.0f) {
					t.setLocalScale(Vector3(1.3f, 1.0f, 1.0));
				}
				else {
					t.setLocalScale(Vector3(1.0f, 1.0f, 1.0));
				}
				t.setLocalPosition(Vector3(handleLength * (i / 10.0f), 0, 0));
				t.setLocalRotation(Quaternion(Quaternion(Vector3(i * handleTwirl / 10.0f, 0, 0)) * Quaternion(Vector3(0, Math::PI / 2, 0))));
				handlesp.addTransform(t);
			}
			//handlesp.addTransform(t);

			float angle = 8.0f;
			float pommelSize = 1.0f / sin(angle * 0.05f * Math::PI);
			float pommelCentre = handleLength + pommelSize * cos(angle * 0.05f * Math::PI);
			for (angle++; angle <= 20.0f; angle++) {
				float x = pommelCentre - pommelSize * cos(angle * 0.05f * Math::PI);
				float y = pommelSize * sin(angle * 0.05f * Math::PI);
				t.setLocalScale(Vector3(y, y, 1.0));
				t.setLocalPosition(Vector3(x, 0, 0));
				handlesp.addTransform(t);
			}
		}
		
		handle = new GameObject(app);
		handle->setMesh(new Sweep(handleProfile, handlesp, false));
		handle->getTransform()->setParent(getTransform());
		handle->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		handle->getTransform()->setLocalScale(Vector3(1.0f, 0.6f, 1.0f));
		handle->getTransform()->name = "handle";
		handle->setMaterial(handleMat);

		std::vector<Vector3> bladeProfile;
		SweepPath bladesp;
		{
			bladeProfile.push_back(Vector3(0.0f, 0.13f, 0.0f));
			bladeProfile.push_back(Vector3(-0.2f, 0.08f, 0.0f));
			bladeProfile.push_back(Vector3(-0.5f, 0.1f, 0.0f));
			bladeProfile.push_back(Vector3(-0.5f, 0.1f, 0.0f));
			bladeProfile.push_back(Vector3(-0.5f, -0.1f, 0.0f));
			bladeProfile.push_back(Vector3(-0.5f, -0.1f, 0.0f));
			bladeProfile.push_back(Vector3(-0.2f, -0.11f, 0.0f));
			bladeProfile.push_back(Vector3(0.2f, -0.11f, 0.0f));
			bladeProfile.push_back(Vector3(0.5f, -0.1f, 0.0f));
			bladeProfile.push_back(Vector3(0.5f, -0.1f, 0.0f));
			bladeProfile.push_back(Vector3(0.5f, 0.1f, 0.0f));
			bladeProfile.push_back(Vector3(0.5f, 0.1f, 0.0f));
			bladeProfile.push_back(Vector3(0.2f, 0.08f, 0.0f));
			bladeProfile.push_back(Vector3(0.0f, 0.13f, 0.0f));

			Transform t;

			Vector3 p0 = Vector3(-30.0f, 1.0f, 0.0f);
			Vector3 p1 = Vector3(-24.0f, 2.0f, 0.0f);
			Vector3 p2 = Vector3(0.0f, 1.0f, 0.0f);

			t.setLocalPosition(Vector3(p0.x, 0, 0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
			t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
			bladesp.addTransform(t);

			//Adjust the scale for the next path instance :
			t.setLocalScale(Vector3(1.0f, 1.0f, 1.0f));
			bladesp.addTransform(t);
			bladesp.addTransform(t);

			for (float i = 0.0f; i <= 1.0f; i += 1.0f / 8.0f) {
				Vector3 p01 = (1.0f - i) * p0 + i * p1;
				Vector3 p12 = (1.0f - i) * p1 + i * p2;
				Vector3 dcb = (1.0f - i) * p01 + i * p12; // De Casteljau Bezier curve
				t.setLocalPosition(Vector3(dcb.x, 0, 0));
				t.setLocalScale(Vector3(1.0f, dcb.y, 1.0f));
				bladesp.addTransform(t);
			}
			bladesp.addTransform(t);

			//Adjust the scale for the final 'cap':
			t.setLocalScale(Vector3(0, 0, 1.0));
			bladesp.addTransform(t);
		}
		blade = new GameObject(app);
		blade->setMesh(new Sweep(bladeProfile, bladesp, false));
		blade->getTransform()->setParent(getTransform());
		blade->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		blade->getTransform()->setLocalScale(Vector3(1.0f, 7.0f, 7.0f));
		blade->getTransform()->name = "blade";
		blade->setMaterial(bladeMat);
	}

	CricketBat::~CricketBat() {
	}
}