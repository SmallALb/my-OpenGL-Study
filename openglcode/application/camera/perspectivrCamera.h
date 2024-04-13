#pragma once

#include "camera.h"


class PerspectivrCamera : public Camera {
public:
	PerspectivrCamera(float f, float a, float n, float far);
	~PerspectivrCamera();

	glm::mat4 getProjectMatrix()override;
	void scale(float deltaScale);
public:
	float mFovy = 0.0f;
	float mAspect = 0.0f;
	float mNear = 0.0f;
	float mFar = 0.0f;
};