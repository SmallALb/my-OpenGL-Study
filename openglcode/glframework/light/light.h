#pragma once;

#include "../base.h"
#include "../math.h"

class Light {
public:
	Light();
	~Light();

public:
	glm::vec3 mColor{ 1.0f };
	float mSpecularIntensity{ 1.0f };
};
