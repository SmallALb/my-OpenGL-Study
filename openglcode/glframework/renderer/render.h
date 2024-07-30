#pragma once
#include"../math.h"
#include "../base.h"
#include "../mesh.h"
#include "../../application/camera/camera.h"
#include "../light/directionLight.h"
#include "../light/ambientLight.h"
#include "../light/pointLight.h"
#include "../shader.h"
#include "../materials/phongMaterial.h"
#include "../light/spotLight.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void render(
		const std::vector<Mesh*>& meshes,
		Camera* camaer,
		SpotLight* spotLight,
		DirectionalLight* dirLight,
		const std::vector<PointLight*>& pointlights,
		AmbientLight* ambLight
	);

	void setClearColor(const glm::vec3& color);
	/*void render(
		const std::vector<Mesh*>& meshes,
		Camera* camaer,
		DirectionalLight* dirLight,
		AmbientLight* ambLight
	);*/
private:
	Shader* pickShader(MateralType type);

private:
	Shader* phongshader;
	Shader* whiteshader;
};