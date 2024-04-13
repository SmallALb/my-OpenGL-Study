#pragma once

#include "../../globa/base.h"
#include "../../globa/math.h"
#include "cameraControl.h"

class GameCameraControl : public CameraControl {
public:
	GameCameraControl();
	~GameCameraControl();

	void onCursor(double xpos, double ypos);

	void update();

	void pitch(float angle);
	void yaw(float angle);

	void setSpeed(float speed) { mSpeed = speed; }
private:
	float mPitch = 0.0f;
	float mSpeed = 0.1f;
};