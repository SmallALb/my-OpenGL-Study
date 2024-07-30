#pragma once
#include "light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight();
	~DirectionalLight();
public:
	glm::vec3 mDir{ -1.0 };
};