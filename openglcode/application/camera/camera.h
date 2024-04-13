#pragma once
#include "../../globa/base.h"
#include "../../globa/math.h"


class Camera {
public:
	glm::mat4 getViewMatrix();
	virtual glm::mat4 getProjectMatrix();
	virtual void scale(float deltaScale) = 0;
public:
	glm::vec3 mPosition{0.0, 0.0, 1.0};
	glm::vec3 mUp{ 0.0, 1.0, 0.0 };
	glm::vec3 mRight{ 1.0, 0.0, 0.0 };
};