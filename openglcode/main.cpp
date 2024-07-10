
#include"globa/base.h"
#include "application/Application.h"
#include "glframework/shader.h"
#include "glframework/texture.h"
#include "globa/math.h"
#include "glframework/shape.h"
#include "application/camera/perspectivrCamera.h"
#include "application/camera/cameraControl.h"
#include "application/camera/gameCameraControl.h"
GLuint vao;
GLuint vao2;

Shape* shape1 = nullptr;

float speed = 0;
float angle = 0;

glm::vec3 Direction = glm::vec3(-1.0, -1.0, -1.0);
glm::vec3 Color = glm::vec3(0.9, 0.85, 0.75);

Shape* shape2 = nullptr;

Shader* shader = nullptr;

Shape* shape3 = nullptr;

Texture* texture = nullptr;
Texture* texture2 = nullptr;
Texture* texturelight = nullptr;
Texture* texturelight2 = nullptr;

PerspectivrCamera* camera = nullptr;
GameCameraControl* cameraControl = nullptr;

glm::mat4 model, view, pre, model2, transforms;

const GLuint lats = 320;
const GLuint lons = 620;

glm::vec3 lightpos;

float positi[6 *  lats * lons * 12];

void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	std::cout << "OnResize" << std::endl;
}

void OnKey(int key, int action, int mods) {
	cameraControl->onKey(key, action, mods);
}

void onMouse(int button, int action, int mods) {
	double x, y;
	app->getCursorPosition(&x, &y);
	cameraControl->onMouse(button, action, x, y);
}

void OnCursor(double xpos, double ypos) {
	cameraControl->onCursor(xpos, ypos);
}

void OnScroll(double offset) {
	cameraControl->onScroll(offset);
}

void perpareCamera() {
	camera = new PerspectivrCamera(60.0, (float)app->getWidth()/ (float)app->getHeight(), 0.01, 1000.0 );

	cameraControl = new GameCameraControl();
	cameraControl->setCamera(camera);
	cameraControl->setSensitivity(0.05);
}




int voe = 0;
void transform() {
	angle += 0.01;
	model = glm::mat4(1.0);
	model = glm::rotate(model, angle, glm::vec3(0.0, 1.0, 0.0));
	//model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));
	model = glm::translate(model, glm::vec3(0.0, 0.3*sin(angle), 0.0));
	shader->setMat4("model", model);

}

void transform2() {
	model2 = glm::mat4(1.0f);
	model2 = glm::translate(model2, glm::vec3(0.0, -0.8, 0.0));
	model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
	shader->setMat4("model", model2);
	shader->setInt("sampler", 1);


	
}

void transfrom3() {
	auto model3 = glm::mat4(1.0f);
	model3 = glm::translate(model3, glm::vec3(0.0, -0.9, 0.0));
	model3 = glm::rotate(model3, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
	shader->setMat4("model", model3);
	shader->setInt("sampler", 0);


}
void preparebox() {

	glGenVertexArrays(1, &shape1->getVao());
	glBindVertexArray(shape1->getVao());


}

void render() {

	//执行opengl画布清理操作
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	//1 绑定当前的program
	shader->begin();
	shader->setInt("blodsampler", 1);
	shader->setInt("blacksampler", 0);
	shader->setInt("glsssampler", 2);
	transform();
	
	//shader->setVector3("moveUV", speed, speed, 0.0f);
	//shader->setFloat("time", glfwGetTime());
	GL_CALL(glBindVertexArray(vao));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader->end();
}

void render2() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	shader->begin();
	lightpos.y += angle;
	shader->setMat4("view", camera->getViewMatrix());
	shader->setMat4("projection", camera->getProjectMatrix());
	shader->setVector3("Direction", glm::value_ptr(Direction));
	shader->setVector3("lightcolor", glm::value_ptr(Color));
	//shader->setInt("blodsampler", 1);
	//shader->setInt("blacksampler", 0);
	//shader->setInt("glsssampler", 2);
	transform();
	glBindVertexArray(2);
	glDrawElements(GL_TRIANGLES, shape2->getIndicesCount(), GL_UNSIGNED_INT, 0);

	transform2();
	glBindVertexArray(shape1->getVao());
	glDrawElements(GL_TRIANGLES, shape1->getIndicesCount(), GL_UNSIGNED_INT, 0);


	transfrom3();
	glBindVertexArray(shape3->getVao());
	glDrawElements(GL_TRIANGLES, shape3->getIndicesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	shader->end();
}


int main() {
	if (!app->init(1000, 1000)) {
		return -1;
	}

	app->setResizeCallback(OnResize);
	app->setKeyBoardCallback(OnKey);
	app->setMouseCallback(onMouse); 
	app->setCursorCallback(OnCursor);

	//设置opengl视口以及清理颜色
	GL_CALL(glViewport(0, 0, 1000, 1000));
	GL_CALL(glClearColor(0.8f, 0.8f, 0.8f, 1.0f));
	/*s1 = new Shape();
	s1->CreateBall(lons, lats, 1.8);*/

	shader = new Shader("assets/shaders/3Dvertex.glsl", "assets/shaders/lightadd.glsl");
	texture = new Texture("assets/textures/iron.jpg", 0);
	texture2 = new Texture("assets/textures/sh.jpg", 1);
	texturelight = new Texture("assets/textures/ironlight.png", 2);
	texturelight2 = new Texture("assets/textures/shlight.png", 3);
	shape1 = Shape::createBox(0.2);
	shape2 = Shape::createSphere(0.3);
	shape3 = Shape::createPlan(0.1, 0.1);
	transforms = glm::mat4(1.0);
	perpareCamera();

	pre = glm::perspective(glm::radians(45.0f), (float)app->getWidth() / (float)app->getHeight(), 0.01f, 100.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.3, 1.6, 12.0));
	view = glm::inverse(view);
	lightpos = {0.0, 0.1, 0.0};
	//std::cout << glm::to_string(view).c_str() << std::endl;
	//assert(false);
	//Createshape(positi, lons, lats, 8.0f);
	//prepareVAO();
	//GL_CALL(preparebox());

	while (app->update()) {
		cameraControl->update();
		render2();
		_sleep(8);
		//system("cls");
	}

	app->destroy();
	delete texture;
	delete texture2;
	delete texturelight;
	delete texturelight2;
	delete camera;
	delete cameraControl;
	delete shape1;
	delete shape2;
	delete shape3;
	return 0;
}