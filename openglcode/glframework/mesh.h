#pragma once
#include "object.h"
#include "shape.h"
#include "materials/material.h"


class Mesh : public Object {
public:
	Mesh(Shape* shape, Material* material);

	~Mesh();

public:
	Shape* mShape{ nullptr };
	Material* mMaterial{ nullptr };
};