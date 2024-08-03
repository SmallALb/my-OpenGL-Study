#include "mesh.h"

Mesh::Mesh(Shape* shape, Material* material) {
	mType = ObjectType::Mesh;
	mShape = shape;
	mMaterial = material;
}


Mesh::~Mesh()
{
}
