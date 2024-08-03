#include "object.h"
#include "object.h"
#include "object.h"
#include "object.h"

Object::Object() {
	mType = ObjectType::Object;
}

Object::~Object() {
}
//����λ��
void Object::setPosition(glm::vec3 pos) {
	mPosition = pos;
}
//��x��ת
void Object::rotateX(float angle) {
	mAngleX += angle;
}
//��y��ת
void Object::rotateY(float angle) {
	mAngleY += angle;
}
//��z��ת
void Object::rotateZ(float angle) {
	mAngleZ += angle;
}
//�������Ŵ�С
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
