
#include"globa/base.h"
#include "application/Application.h"
#include "glframework/shader.h"
#include "glframework/texture.h"
#include "globa/math.h"
#include "glframework/shape.h"
#include "application/camera/perspectivrCamera.h"
#include "application/camera/cameraControl.h"
#include "application/camera/gameCameraControl.h"
#include "glframework/materials/phongMaterial.h"
#include "glframework/mesh.h"
#include "glframework/renderer/render.h"
#include "glframework/materials/whiteMaterial.h"
#include "glframework/light/pointLight.h"
#include "glframework/light/spotLight.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Renderer* renderer = nullptr;
PerspectivrCamera* camera = nullptr;
GameCameraControl* cameraControl = nullptr;
Mesh* meshwhite = nullptr;
glm::mat4 model, view, pre, model2, transforms;

Scence* scence = nullptr;

glm::vec3 clearColor{};

std::vector<Mesh*> meshes{};
SpotLight* spotlight = nullptr;
AmbientLight* ambilight = nullptr;
DirectionalLight* dirlight = nullptr;
std::vector<PointLight*> pointlights;

//
void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	std::cout << "OnResize" << std::endl;
}

void OnKey(int key, int action, int mods) {
	cameraControl->onKey(key, action, mods);
}

//鼠标回调函数
void onMouse(int button, int action, int mods) {
	double x, y;
	app->getCursorPosition(&x, &y);
	cameraControl->onMouse(button, action, x, y);
}

//鼠标位置回调
void OnCursor(double xpos, double ypos) {
	cameraControl->onCursor(xpos, ypos);
}

void OnScroll(double offset) {
	cameraControl->onScroll(offset);
}

void perpareCamera() {
	camera = new PerspectivrCamera(60.0, (float)app->getWidth()/ (float)app->getHeight(), 0.01, 1000.0 );
	camera->mPosition = {0.0, 0.0, 7.0};
	cameraControl = new GameCameraControl();
	cameraControl->setCamera(camera);
	cameraControl->setSensitivity(0.05);
	cameraControl->setSpeed(0.1);
}


void initIMGUI() {
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(app->getWindow(), 1);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void renderIMGUI() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello World!");
	ImGui::Button("Test Button", ImVec2(40, 20));
	ImGui::ColorEdit3("Clear Color",(float*) & clearColor);
	ImGui::End();

	ImGui::Render();

	int d_w, d_h;
	glfwGetFramebufferSize(app->getWindow(), &d_w, &d_h);

	glViewport(0, 0, d_w, d_h);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void render() {

	//执行opengl画布清理操作
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

}

void prepare() {
	renderer = new Renderer();
	scence = new Scence();
	auto shape = Shape::createSphere(3.0f);
	auto shape2 = Shape::createBox(1.0f);
	auto shape3 = Shape::createSphere(0.2);
	
	auto material2 = new PhongMaterial();
	auto whitematerial = new WhiteMaterial();

	material2->mShiness = 4.0f;
	material2->mDiffuse = new Texture("assets/textures/sh.png", 0);
	material2->mSpecularMask = new Texture("assets/textures/blod.png", 1);

	meshwhite = new Mesh(shape3, whitematerial);
	meshwhite->setPosition({ 1.0, 0.0, 0.0 });
	auto mesh2 = new Mesh(shape2, material2);
	auto spMesh = new Mesh(shape3, material2);
	spMesh->setPosition({ 2.0, 0.0, 0.0 });

	mesh2->setPosition({ 3.0, 0.0, 0.0 });
	meshes.push_back(meshwhite);
	meshes.push_back(mesh2);
	meshes.push_back(spMesh);

	scence->addChild(mesh2);

	mesh2->addChild(spMesh);

	spotlight = new SpotLight();
	spotlight->setPosition(meshwhite->getPosition());
	spotlight->mTargetDir = {-1.0,0.0,0.0};
	spotlight->mVisibleAngle = 30.0f;
	spotlight->mOuterAngle = 45.0f;
	spotlight->mSpecularIntensity = 1.0;

	ambilight = new AmbientLight();
	ambilight->mColor = glm::vec3(0.6f);
	ambilight->mSpecularIntensity = 0.5;

	dirlight = new DirectionalLight();
	dirlight->mDir = glm::vec3(-1.0f);
	
}

void lightmove() {
	float xpos = 2.5*glm::sin(glfwGetTime()) + 3.0f;
	meshwhite->setPosition({xpos, 0.0f, 0.0f});
	spotlight->setPosition({ xpos, 0.0f, 0.0f });
}

int main() {
	if (!app->init(1400, 1600)) {
		return -1;
	}

	app->setResizeCallback(OnResize);
	app->setKeyBoardCallback(OnKey);
	app->setMouseCallback(onMouse); 
	app->setCursorCallback(OnCursor);

	//设置opengl视口以及清理颜色
	GL_CALL(glViewport(0, 0, 1000, 1000));
	GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	perpareCamera();
	prepare();
	initIMGUI();

	while (app->update()) {
		cameraControl->update();
		//lightmove();
		renderer->render(scence, camera, dirlight,ambilight);
		renderer->setClearColor(clearColor);
		renderIMGUI();
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		_sleep(8);
		//system("cls");
	}

	app->destroy();

	return 0;
}