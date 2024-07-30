#include "mesh.h"

Mesh::Mesh(Shape* shape, Material* material) {
	mShape = shape;
	mMaterial = material;
}


Mesh::~Mesh()
{
}
