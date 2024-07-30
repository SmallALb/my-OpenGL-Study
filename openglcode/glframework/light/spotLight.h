#pragma once
#include "light.h"
#include "../object.h"
class SpotLight : public Light, public Object {
public:
	SpotLight();
	~SpotLight();
public:
	glm::vec3 mTargetDir{ -1.0f };
	float mVisibleAngle{ 0.0f };
	float mOuterAngle{ 0.0f };
};