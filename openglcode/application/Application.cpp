#include "Application.h"
#include "Application.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>


//��ʼ��Application�ľ�̬����
Application* Application::mInstance = nullptr;

Application* Application::getInstance() {
	//���mInstance�Ѿ�ʵ�����ˣ�new�����ˣ�����ֱ�ӷ���
	//������Ҫ��new�������ٷ���
	if (mInstance == nullptr) {
		mInstance = new Application();
	}

	return mInstance;
}

Application::Application() {

}

Application::~Application() {

}


bool Application::init(const int& width, const int& height) {
	mWidth = width;
	mHeight = height;

	//1 ��ʼ��GLFW��������
	glfwInit();
	//1.1 ����OpenGL���汾�š��ΰ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//1.2 ����OpenGL���ú���ģʽ����������Ⱦģʽ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//2 �����������
	mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLStudy", NULL, NULL);
	if (mWindow == NULL) {
		return false;
	}

	//**���õ�ǰ�������ΪOpenGL�Ļ�����̨
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

	//this���ǵ�ǰȫ��Ψһ��Application����
	glfwSetWindowUserPointer(mWindow, this);

	//������Ӧ
	glfwSetKeyCallback(mWindow, keyCallback);

	glfwSetMouseButtonCallback(mWindow, mouseCallback);

	glfwSetCursorPosCallback(mWindow, cursorCallback);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	return true;
}

bool Application::update() {
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}

	//���ղ��ַ�������Ϣ
	//�����Ϣ�����Ƿ�����Ҫ�������ꡢ���̵���Ϣ
	//����еĻ��ͽ���Ϣ����������ն���
	glfwPollEvents();

	//�л�˫����
	glfwSwapBuffers(mWindow);

	return true;
}

void Application::destroy() {
	//�˳�����ǰ���������
	glfwTerminate();
}


void Application::getCursorPosition(double* x, double* y) {
	glfwGetCursorPos(mWindow, x, y);
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	//std::cout << "Resize" << std::endl;

	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr) {
		self->mResizeCallback(width, height);
	}
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyBoardCallback != nullptr) {
		self->mKeyBoardCallback(key, action, mods);
	}
}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mMouseCallback != nullptr) {
		self->mMouseCallback(button, action, mods);
	}
}

void Application::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mCursorCallback != nullptr) {
		self->mCursorCallback(xpos, ypos);
	}
}

void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mScrollCallback != nullptr) {
		self->mScrollCallback(yoffset);
	}
}
