#pragma once
#include "light.h"
#include "../object.h"
class PointLight : public Light, public Object {
public:
	PointLight();
	~PointLight();
public:
	float mk2 = 1.0f;
	float mk1 = 1.0f;
	float mkc = 1.0f;
};