#include "perspectivrCamera.h"

PerspectivrCamera::PerspectivrCamera(float f, float a, float n, float far) {
	mFovy = f;
	mAspect = a;
	mNear = n;
	mFar = far;
}

PerspectivrCamera::~PerspectivrCamera()
{
}

glm::mat4 PerspectivrCamera::getProjectMatrix(){
	return glm::perspective(glm::radians(mFovy), mAspect, mNear, mFar);
}

void PerspectivrCamera::scale(float deltaScale) {
	auto front = glm::cross(mUp, mRight);
	mPosition += (front * deltaScale);
}
