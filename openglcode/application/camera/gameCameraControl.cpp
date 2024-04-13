#include "gameCameraControl.h"

GameCameraControl::GameCameraControl() {
	mSensitivity = 0.011f;
}

GameCameraControl::~GameCameraControl()
{
}

void GameCameraControl::onCursor(double xpos, double ypos) {
	float dY = (ypos - mCurrentY) * mSensitivity;
	float dX = (xpos - mCurrentX) * mSensitivity;
	if (mRightMouseDown) {
		pitch(-dY);
		yaw(-dX);
	}
	mCurrentX = xpos;
	mCurrentY = ypos;
}

void GameCameraControl::update() {
	auto front = glm::cross(mCamera->mUp, mCamera->mRight);
	auto right = mCamera->mRight;
	auto up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 direction(0.0);

	if (mKeyMap[GLFW_KEY_W]) {
		direction += front;
	}
	if (mKeyMap[GLFW_KEY_S]) {
		direction -= front;
	}
	if (mKeyMap[GLFW_KEY_A]) {
		direction -= right;
	}
	if (mKeyMap[GLFW_KEY_D]) {
		direction += right;
	}
	if (mKeyMap[GLFW_KEY_SPACE]) {
		direction += up;
	}
	if (mKeyMap[GLFW_KEY_LEFT_SHIFT]) {
		direction -= up;
	}
	if (glm::length(direction) != 0) {
		direction = glm::normalize(direction);
		mCamera->mPosition += direction * mSpeed;
	}
}

void GameCameraControl::pitch(float angle) {
	mPitch += angle;
	if (mPitch > 89.5 || mPitch < -89.5) {
		mPitch -= angle;
		return;
	}
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
}

void GameCameraControl::yaw(float angle) {
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0);
}
