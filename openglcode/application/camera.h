#pragma once
#include "../globa/base.h"
#include "../globa/math.h"

#define NO_MOVE 0
#define MOVE_LEFT 0x001
#define MOVE_RIGHT 0x002
#define MOVE_FRONT 0x004
#define MOVE_BACK 0x008

class Camera {
public:
	Camera(float fovy, float aspect, float near, float far, const glm::vec3& top);
	~Camera();

	void KeyBoardinputDown(int key, int action, int mods);

	void KeyBoradinputUp(int key, int action, int mods);

	void update();

	glm::mat4 getViewMatrix()const { return mViewMatrix; }
	glm::mat4 getProjectionMatrix()const { return mProjectionMatrix; }
private:
	void pitch(int yoffset);

	void yaw(int xoffset);
private:
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mTop;
	float mSpeed{0.1f};

	float		mPitch{ 0.0f };
	float		mYaw{ -90.0f };
	float		mSensitivity{ 0.1f };

	uint32_t	mMoveState{ NO_MOVE };
	bool		mMouseMoving{ false };
	int			mCurrentMouseX{ 0 };
	int			mCurrentMouseY{ 0 };
};