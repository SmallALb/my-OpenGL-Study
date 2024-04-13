
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

float speed = 0;
float angle = 0;

Shape* s1 = nullptr;

Shader* shader = nullptr;

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
	cameraControl->setSensitivity(0.2);
}

void prepareVAO() {
	glm::vec3 nor1 = glm::cross( glm::vec3(0.5f, 0.5f, -0.5f)- glm::vec3(-0.5, -0.5, -0.5),glm::vec3(0.5, -0.5, -0.5)  - glm::vec3(-0.5, -0.5, -0.5));
	glm::vec3 nor2 = glm::cross(glm::vec3(0.5f, -0.5f, 0.5f) - glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, 0.5, 0.5) - glm::vec3(-0.5, -0.5, 0.5));
	glm::vec3 nor3 = glm::cross(glm::vec3(-0.5f, -0.5f, -0.5f) - glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5) - glm::vec3(-0.5, 0.5, 0.5));
	glm::vec3 nor4 = glm::cross(glm::vec3(0.5f, 0.5f, -0.5f) - glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, -0.5, -0.5) - glm::vec3(0.5, 0.5, 0.5));
	glm::vec3 nor5 = glm::cross(glm::vec3(0.5f, -0.5f, -0.5f) - glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5f, -0.5f, 0.5f) - glm::vec3(-0.5, -0.5, -0.5));
	glm::vec3 nor6 = glm::cross(glm::vec3(0.5f, 0.5f, 0.5f) - glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5f, 0.5f, -0.5) - glm::vec3(-0.5, 0.5, -0.5));
	
	//1 准备positions
	float positions[] = {
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 1.0f,		0.0f,  0.0f,	nor1.x, nor1.y, nor1.z,
		 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 1.0f,		1.0f,  0.0f,	nor1.x, nor1.y, nor1.z,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 1.0f,		1.0f,  1.0f,	nor1.x, nor1.y, nor1.z,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 1.0f,		1.0f,  1.0f,	nor1.x, nor1.y, nor1.z,
		-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 1.0f,		0.0f,  1.0f,	nor1.x, nor1.y, nor1.z,
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 1.0f,		0.0f,  0.0f,	nor1.x, nor1.y, nor1.z,
							 					  
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f,		0.0f,  0.0f,	nor2.x, nor2.y, nor2.z,
		 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f,		1.0f,  0.0f,	nor2.x, nor2.y, nor2.z,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f,		1.0f,  1.0f,	nor2.x, nor2.y, nor2.z,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f,		1.0f,  1.0f,	nor2.x, nor2.y, nor2.z,
		-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f,		0.0f,  1.0f,	nor2.x, nor2.y, nor2.z,
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f,		0.0f,  0.0f,	nor2.x, nor2.y, nor2.z,
							 					  
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor3.x, nor3.y, nor3.z,
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, 1.0f,		1.0f,  1.0f,	nor3.x, nor3.y, nor3.z,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor3.x, nor3.y, nor3.z,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor3.x, nor3.y, nor3.z,
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, 1.0f,		0.0f,  0.0f,	nor3.x, nor3.y, nor3.z,
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor3.x, nor3.y, nor3.z,
							 					  
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor4.x, nor4.y, nor4.z,
		 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 1.0f,		1.0f,  1.0f,	nor4.x, nor4.y, nor4.z,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor4.x, nor4.y, nor4.z,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor4.x, nor4.y, nor4.z,
		 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 1.0f,		0.0f,  0.0f,	nor4.x, nor4.y, nor4.z,
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor4.x, nor4.y, nor4.z,
							 					  
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor5.x, nor5.y, nor5.z,
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, 1.0f,		1.0f,  1.0f,	nor5.x, nor5.y, nor5.z,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor5.x, nor5.y, nor5.z,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor5.x, nor5.y, nor5.z,
		-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 1.0f,		0.0f,  0.0f,	nor5.x, nor5.y, nor5.z,
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor5.x, nor5.y, nor5.z,
							 					  
		-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor6.x, nor6.y, nor6.z,
		 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 1.0f,		1.0f,  1.0f,	nor6.x, nor6.y, nor6.z,
		 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor6.x, nor6.y, nor6.z,
		 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 1.0f,		1.0f,  0.0f,	nor6.x, nor6.y, nor6.z,
		-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 1.0f,		0.0f,  0.0f,	nor6.x, nor6.y, nor6.z,
		-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 1.0f,		0.0f,  1.0f,	nor6.x, nor6.y, nor6.z,

	};

	unsigned int indices[] = {
		0, 1, 2, 3, 4, 5,
		6, 7, 8, 9, 10, 11,
		12,13,14,15,16,17,
		18,19,20,21,22,23,
		24,25,26,27,28,29,
		30,31,32,33,34,35
	};

	//2 VBO创建
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	//3 EBO创建
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//4 VAO创建
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//5 绑定vbo ebo 加入属性描述信息
	//5.1 加入位置属性描述信息
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(3*sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(7*sizeof(float)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float)*12, (void*)(9*sizeof(float)));

	//5.2 加入ebo到当前的vao
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);
}

glm::vec3 getPoint(float u, float v, glm::vec2& uv) {
	float r = 0.5;
	float pi = glm::pi<float>();
	float z = r * cos(pi*u);
	float x = r * sin(pi * u) * cos(2*pi*v);
	float y = r * sin(pi * u) * sin(2 * pi * v);
	uv = glm::vec2(u, 1.0 - v);
	return glm::vec3(x, y, z);
}

void Createshape(float* sphere, unsigned int Longitude, unsigned int Latitude, float r) {
	GLfloat lon_step = 1.0f / Longitude;
	GLfloat lat_step = 1.0f / Latitude;
	GLuint offset = 0;
	int i = 0;
	glm::vec2 lat_uv;
	for (int lat = 0; lat < Latitude; lat++) { 
		glm::vec4 color = { 1.0, 0.0, 0.0, 1.0 };
		for (int lon = 0; lon < Longitude; lon++) { // 经线v
			// 一次构造4个点，两个三角形，
			
			glm::vec2 uv1;
			glm::vec2 uv2;
			glm::vec2 uv3;
			glm::vec2 uv4;

			glm::vec3 point1 = getPoint(lat * lat_step, lon * lon_step, uv1); //(0 0)
			glm::vec3 point2 = getPoint((lat + 1) * lat_step, lon * lon_step, uv2); //(1 0)
			glm::vec3 point3 = getPoint((lat + 1) * lat_step, (lon + 1) * lon_step, uv3);//(1 1)
			glm::vec3 point4 = getPoint(lat * lat_step, (lon + 1) * lon_step, uv4);//(0 1)

			glm::vec3 normaline= glm::cross(point3-point2, point1 - point2);
			//..................
			memcpy(sphere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(sphere + offset, glm::value_ptr(uv1), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(normaline), 3*sizeof(GLfloat));
			offset += 3;
			//..............
			memcpy(sphere + offset, glm::value_ptr(point4), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(sphere + offset, glm::value_ptr(uv4), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//
			memcpy(sphere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(sphere + offset, glm::value_ptr(uv3), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//..............
			memcpy(sphere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(sphere + offset, glm::value_ptr(uv1), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//.............
			memcpy(sphere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(sphere + offset, glm::value_ptr(uv3), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//..............
			memcpy(sphere + offset, glm::value_ptr(point2), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(sphere + offset, glm::value_ptr(uv2), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
		}
	}

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positi), positi, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3*sizeof(float)));

	glDisableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7*sizeof(float)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9*sizeof(float)));
	glBindVertexArray(0);

	for (int i = 0; i < 48; i++) {
		std::cout << positi[i] <<  (i%12 == 11 ? "\n" : " ");
	}
}
int voe = 0;
void transform() {
	angle += 0.1;
	model = glm::mat4(1.0);
	model = glm::rotate(model, angle, glm::vec3(0.0, 1.0, 0.0));
	//model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));
	model = glm::translate(model, glm::vec3(0.0, 0.3*sin(angle), 0.0));
	shader->setMat4("model", model);
	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 2);
	shader->setFloat("material.shininess", 32.0);
}

void transform2() {
	model2 = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 5.0, 5.0));
	model2 = glm::translate(model2, glm::vec3(0.0, -0.3, 0.0));
	model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
	shader->setMat4("model", model2);
	shader->setInt("material.diffuse", 1);
	shader->setInt("material.specular", 3);
	shader->setFloat("material.shininess", 2.0);

	
}
void preparebox() {
	float inint[] = {
		-0.5, 0.0, 0.0,		0.2f, 0.2f, 0.2f, 1.0f,		0.0f,  0.0f,	0.0, 1.0, 0.0,
		 0.5, 0.0, 0.0,		0.2f, 0.2f, 0.2f, 1.0f,		1.0f,  0.0f,	0.0, 1.0, 0.0,
		 0.5, 0.0,-1.8,		0.2f, 0.2f, 0.2f, 1.0f,		1.0f,  1.0f,	0.0, 1.0, 0.0,
		-0.5, 0.0,-1.8,		0.2f, 0.2f, 0.2f, 1.0f,		0.0f,  1.0f,	0.0, 1.0, 0.0,
	};

	unsigned int ind[] = {
		0, 1, 2, 
		2, 0, 3,
	};

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(inint), inint, GL_STATIC_DRAW);
	
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*12, (void*)0);
	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float)*3));
	//uv
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float)*7));
	//nor
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float)*9));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);
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
	shader->setMat4("transform", transforms);
	shader->setVector3("viewPos", glm::value_ptr(view));
	shader->setVector3("light.position", glm::value_ptr(view));
	shader->setVector3("light.direction", glm::value_ptr(lightpos));
	shader->setFloat("light.cutoff", glm::cos(glm::radians(12.5f)));
	shader->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
	shader->setVector3("light.ambient", 0.3, 0.3, 0.3);
	shader->setVector3("light.diffuse", 0.8, 0.25, 0.25);
	shader->setVector3("light.specular", 0.25, 0.5, 0.25);
	shader->setFloat("light.constant", 1.0f);
	shader->setFloat("light.linear", 0.09);
	shader->setFloat("light.quadratic", 0.032);
	//shader->setInt("blodsampler", 1);
	//shader->setInt("blacksampler", 0);
	//shader->setInt("glsssampler", 2);
	transform();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6 * lats * lons);

	transform2();
	glBindVertexArray(vao2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

	shader = new Shader("assets/shaders/3Dvertex.glsl", "assets/shaders/lightfragment.glsl");
	texture = new Texture("assets/textures/iron.jpg", 0);
	texture2 = new Texture("assets/textures/sh.jpg", 1);
	texturelight = new Texture("assets/textures/ironlight.png", 2);
	texturelight2 = new Texture("assets/textures/shlight.png", 3);
	transforms = glm::mat4(1.0);
	perpareCamera();

	pre = glm::perspective(glm::radians(45.0f), (float)app->getWidth() / (float)app->getHeight(), 0.01f, 100.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.3, 1.6, 12.0));
	view = glm::inverse(view);
	lightpos = {0.0, 0.7, 0.0};
	//std::cout << glm::to_string(view).c_str() << std::endl;
	//assert(false);
	Createshape(positi, lons, lats, 8.0f);
	//prepareVAO();
	GL_CALL(preparebox());

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
	return 0;
}