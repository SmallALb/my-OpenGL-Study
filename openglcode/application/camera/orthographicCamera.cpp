#include "orthographicCamera.h"


OthographicCamera::OthographicCamera(float l, float r, float t, float b, float n, float f) {
	mLeft = l;
	mRight = r;
	mTop = t;
	mBottom = b;
	mNear = n;
	mFar = f;
}

OthographicCamera::~OthographicCamera()
{
}

glm::mat4 OthographicCamera::getProjectMatrix() {
	return glm::ortho(mLeft, mRight, mTop, mBottom, mNear, mFar);
}
