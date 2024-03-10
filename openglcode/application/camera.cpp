#include "camera.h"

Camera::Camera(float fovy, float aspect, float near, float far, const glm::vec3& top) {
	mTop = top;
	mProjectionMatrix = glm::perspective(fovy, aspect,near, far);
	update();
}


Camera::~Camera() {
}

void Camera::KeyBoardinputDown(int key, int action, int mods) {
	if (action != GLFW_KEY_DOWN) return;
	switch (key) {
	case GLFW_KEY_W:
		mMoveState |= MOVE_FRONT;
		break;
	case GLFW_KEY_A:
		mMoveState |= MOVE_LEFT;
		break;
	case GLFW_KEY_D:
		mMoveState |= MOVE_RIGHT;
		break;
	case GLFW_KEY_S:
		mMoveState |= MOVE_BACK;
		break;
	default:
		break;
	}
}

void Camera::KeyBoradinputUp(int key, int action, int mods) {
	if (action != GLFW_KEY_UP) return;
	switch (key) {
	case GLFW_KEY_W:
		mMoveState &= ~MOVE_FRONT;
		break;
	case GLFW_KEY_A:
		mMoveState &= ~MOVE_LEFT;
		break;
	case GLFW_KEY_S:
		mMoveState &= ~MOVE_BACK;
		break;
	case GLFW_KEY_D:
		mMoveState &= ~MOVE_RIGHT;
		break;
	default:
		break;
	}
}

void Camera::update() {
	glm::vec3 moveDirection = { 0.0, 0.0, 0.0 };
	glm::vec3 front = mFront;
	glm::vec3 right = glm::normalize(glm::cross(mFront, mTop));

	if (mMoveState & MOVE_FRONT) {
		moveDirection += front;
	}

	if (mMoveState & MOVE_BACK) {
		moveDirection += -front;
	}

	if (mMoveState & MOVE_LEFT) {
		moveDirection += -right;
	}

	if (mMoveState & MOVE_RIGHT) {
		moveDirection += right;
	}

	if (moveDirection.length != 0) {
		moveDirection = glm::normalize(moveDirection);
		mPosition += mSpeed * moveDirection;
	}

	mViewMatrix = glm::lookAt(mPosition, mPosition + mFront, mTop);
}


void Camera::pitch(int yoffset) {

}

void Camera::yaw(int xoffset) {

}
