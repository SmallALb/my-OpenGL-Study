#pragma once

#include "camera.h"

class OthographicCamera : public Camera {
public:
	OthographicCamera(float l, float r, float t, float b, float n, float f);
	~OthographicCamera();

	glm::mat4 getProjectMatrix()override;
private:
	float mLeft = 0.0f;
	float mRight = 0.0f;
	float mTop = 0.0f;
	float mBottom = 0.0f;
	float mNear = 0.0f;
	float mFar = 0.0f;
};