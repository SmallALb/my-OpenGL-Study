#pragma once 

#include "../globa/base.h"
#include "camera.h"

#define app Application::getInstance()

class GLFWwindow;

using ResizeCallback = void(*)(int width, int height);
using KeyBoardCallback = void(*)(int key, int action, int mods);

class Application {
public:
	~Application();
	
	//���ڷ���ʵ���ľ�̬����
	static Application* getInstance();

	bool init(const int& width = 800, const int& height = 600);

	bool update();

	void destroy();


	uint32_t getWidth()const { return mWidth; }
	uint32_t getHeight()const { return mHeight; }

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; }
	void setCamera(Camera* camera) { mCamera = camera; }
private:
	//C++���ں���ָ��
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	//ȫ��Ψһ�ľ�̬����ʵ��
	static Application* mInstance;

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };

	ResizeCallback mResizeCallback{ nullptr };
	KeyBoardCallback mKeyBoardCallback{ nullptr };

	Camera* mCamera{nullptr};

	Application();
};
