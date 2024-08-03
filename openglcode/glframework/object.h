#pragma once
#include "base.h"
#include "math.h"


enum class ObjectType {
	Object,
	Mesh,
	Scence
};



class Object {
public:
	Object();
	~Object();

	void setPosition(glm::vec3 pos);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void setScale(glm::vec3 scale);

	glm::vec3 getPosition() const { return mPosition; }

	glm::mat4 getModleMatrix();

	void addChild(Object* obj);

	std::vector<Object*> getChildren();

	Object* getParent();

	ObjectType getType() const { return mType; }
protected:
	glm::vec3 mPosition{ 0.0f };
	float mAngleX{ 0.0f };
	float mAngleY{ 0.0f };
	float mAngleZ{ 0.0f };
	glm::vec3 mScale{ 1.0f};
	Object* mParent{nullptr};
	std::vector<Object*> mChildren{};

	ObjectType mType;
};