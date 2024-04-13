#pragma once

#include "camera.h"

class CameraControl {
protected:
	bool mLeftMouseDown = 0;
	bool mRightMouseDown = 0;
	bool mMiddleMouseDown = 0;

	double mCurrentX = 0.0, mCurrentY = 0.0;
	std::map<int, bool> mKeyMap;
	float mSensitivity = 0.1f;
	Camera* mCamera;
public:
	virtual void update();
	virtual void onMouse(int button, int action, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int action, int mods);
	virtual void onScroll(float offset);

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float s) { mSensitivity = s; }
};