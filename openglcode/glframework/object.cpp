#include "object.h"
#include "object.h"
#include "object.h"
#include "object.h"

Object::Object() {
	mType = ObjectType::Object;
}

Object::~Object() {
}
//设置位置
void Object::setPosition(glm::vec3 pos) {
	mPosition = pos;
}
//绕x旋转
void Object::rotateX(float angle) {
	mAngleX += angle;
}
//绕y旋转
void Object::rotateY(float angle) {
	mAngleY += angle;
}
//绕z旋转
void Object::rotateZ(float angle) {
	mAngleZ += angle;
}
//设置缩放大小
void Object::setScale(glm::vec3 scale) {
	
}

glm::mat4 Object::getModleMatrix() {
	glm::mat4 transform(1.0f);
	
	glm::mat4 parentMat{ 1.0f };
	if (mParent != nullptr) {
		parentMat = mParent->getModleMatrix();
	}


	transform = glm::scale(transform, mScale);
	transform = glm::rotate(transform, glm::radians(mAngleX), glm::vec3(1.0, 0.0, 0.0));
	transform = glm::rotate(transform, glm::radians(mAngleY), glm::vec3(0.0, 1.0, 0.0));
	transform = glm::rotate(transform, glm::radians(mAngleZ), glm::vec3(0.0, 0.0, 1.0));

	transform = parentMat * glm::translate(glm::mat4(1.0), mPosition) * transform;

	return transform;
}

void Object::addChild(Object* obj) {
	auto iter = std::find(mChildren.begin(), mChildren.end(), obj);
	if (iter != mChildren.end()) {
		std::cerr << "Duplicated Child added! \n";
		return;
	}
	mChildren.push_back(obj);
	obj->mParent = this;
}

std::vector<Object*> Object::getChildren()
{
	return mChildren;
}

Object* Object::getParent()
{
	return mParent;
}
