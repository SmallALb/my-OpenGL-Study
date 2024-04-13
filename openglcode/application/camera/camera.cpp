#include "camera.h"

glm::mat4 Camera::getViewMatrix() {
	glm::vec3 front = glm::cross(mUp, mRight);
	glm::vec3 center = mPosition + front;

	return glm::lookAt(mPosition, center, mUp);
}

glm::mat4 Camera::getProjectMatrix() {
	return glm::mat4();
}
