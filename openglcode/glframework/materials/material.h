#pragma once
#include "../base.h"
#include "../math.h"

enum  class MateralType {
	PHONG,
	WHITE
};

class Material {
public:
	Material();
	~Material();
public:
	MateralType mType;
};