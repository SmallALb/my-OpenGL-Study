#include "render.h"
#include "render.h"
#include "render.h"
#include "render.h"

Renderer::Renderer() {
	phongshader = new Shader("assets/shaders/3Dvertex.glsl", "assets/shaders/lightadd.glsl");
	whiteshader = new Shader("assets/shaders/whitevertex.glsl", "assets/shaders/whiteshader.glsl");
	
}

Renderer::~Renderer()
{
}

void Renderer::render(
	const std::vector<Mesh*>& meshes,
	Camera* camaer,
	SpotLight* spotLight,
	DirectionalLight* dirLight,
	const std::vector<PointLight*>& pointlights,
	AmbientLight* ambLight
) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto mesh : meshes) {
		auto shape = mesh->mShape;
		auto material = mesh->mMaterial;

		Shader* shader = pickShader(material->mType);
		shader->begin();


		//采样器单元挂钩

		switch (material->mType) {
		case MateralType::PHONG:
		{
			PhongMaterial* phongMat = (PhongMaterial*)material;
			//diffcuse贴图
			shader->setInt("sampler", 0);
			
			phongMat->mDiffuse->bind();

			shader->setInt("specularMaskSapmler", 1);
			phongMat->mSpecularMask->bind();

			//mvp
			shader->setMat4("view", camaer->getViewMatrix());
			shader->setMat4("projection", camaer->getProjectMatrix());
			shader->setMat4("model", mesh->getModleMatrix());
			//法线矩阵
			shader->setMat4("normat", glm::transpose(glm::inverse(mesh->getModleMatrix())));
			//光照
			shader->setVector3("spotlight.position", spotLight->getPosition());
			shader->setVector3("spotlight.color", spotLight->mColor);
			shader->setFloat("spotlight.specularIntensity", spotLight->mSpecularIntensity);
			shader->setVector3("spotlight.targetDirection", spotLight->mTargetDir);
			shader->setFloat("spotlight.inerline", glm::cos(glm::radians(spotLight->mVisibleAngle)));
			shader->setFloat("spotlight.outerline", glm::cos(glm::radians(spotLight->mOuterAngle)));

			shader->setVector3("directionalLight.color", dirLight->mColor);
			shader->setVector3("directionalLight.direction", dirLight->mDir);
			shader->setFloat("directionalLight.specularIntensity", dirLight->mSpecularIntensity);

			for (int i = 0; i < pointlights.size(); i++) {
				auto pointlight = pointlights[i];
				std::string basename = "pointLights[" + std::to_string(i) + "]";

				shader->setVector3(basename +".position", pointlight->getPosition());
				shader->setVector3(basename + ".color", pointlight->mColor);
				shader->setFloat(basename + ".specularIntensity", pointlight->mSpecularIntensity);
				shader->setFloat(basename + ".k2", pointlight->mk2);
				shader->setFloat(basename + ".k1", pointlight->mk1);
				shader->setFloat(basename + ".kc", pointlight->mkc);
				shader->setInt(basename + ".flag", 1);
			}

			shader->setVector3("ambientcolor", ambLight->mColor);
			shader->setFloat("shiness", phongMat->mShiness);

			//shader->setFloat("k2", pointLight->mk2);
			//shader->setFloat("k1", pointLight->mk1);
			//shader->setFloat("kc", pointLight->mkc);


			shader->setVector3("cameraPosition", camaer->mPosition);
		}
			break;
		case MateralType::WHITE:
		{
			shader->setMat4("model", mesh->getModleMatrix());
			shader->setMat4("projection", camaer->getProjectMatrix());
			shader->setMat4("view", camaer->getViewMatrix());
		}
			break;
		default: continue;
		}

		glBindVertexArray(shape->getVao());
		glDrawElements(GL_TRIANGLES, shape->getIndicesCount(), GL_UNSIGNED_INT, 0);

		shader->end();
	}

}

void Renderer::render(
	Scence* scence, 
	Camera* camaer,
	DirectionalLight* dirLight,
	AmbientLight* ambLight
) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	renderObject(scence, camaer, dirLight, ambLight);
}

void Renderer::renderObject(Object* object, Camera* camaer, DirectionalLight* dirLight, AmbientLight* ambLight) {
	if (object->getType() == ObjectType::Mesh) {
		auto mesh = ((Mesh*)object);
		auto shape = mesh->mShape;
		auto material = mesh->mMaterial;

		Shader* shader = pickShader(material->mType);
		shader->begin();


		//采样器单元挂钩

		switch (material->mType) {
			case MateralType::PHONG:
			{
				PhongMaterial* phongMat = (PhongMaterial*)material;
				//diffcuse贴图
				shader->setInt("sampler", 0);

				phongMat->mDiffuse->bind();

				shader->setInt("specularMaskSapmler", 1);
				phongMat->mSpecularMask->bind();

				//mvp
				shader->setMat4("view", camaer->getViewMatrix());
				shader->setMat4("projection", camaer->getProjectMatrix());
				shader->setMat4("model", mesh->getModleMatrix());
				//法线矩阵
				shader->setMat4("normat", glm::transpose(glm::inverse(mesh->getModleMatrix())));
				//光照

				shader->setVector3("directionalLight.color", dirLight->mColor);
				shader->setVector3("directionalLight.direction", dirLight->mDir);
				shader->setFloat("directionalLight.specularIntensity", dirLight->mSpecularIntensity);

				shader->setVector3("ambientcolor", ambLight->mColor);
				shader->setFloat("shiness", phongMat->mShiness);

				//shader->setFloat("k2", pointLight->mk2);
				//shader->setFloat("k1", pointLight->mk1);
				//shader->setFloat("kc", pointLight->mkc);


				shader->setVector3("cameraPosition", camaer->mPosition);
			}
			break;
			case MateralType::WHITE:
			{
				shader->setMat4("model", mesh->getModleMatrix());
				shader->setMat4("projection", camaer->getProjectMatrix());
				shader->setMat4("view", camaer->getViewMatrix());
			}
			break;
			default: break;
		}

		glBindVertexArray(shape->getVao());
		glDrawElements(GL_TRIANGLES, shape->getIndicesCount(), GL_UNSIGNED_INT, 0);

		shader->end();
		}

	for (auto child : object->getChildren()) renderObject(child, camaer, dirLight, ambLight);
	
}
	



void Renderer::setClearColor(const glm::vec3& color) {
	glClearColor(color.r, color.g, color.b, 1.0f);
}

Shader* Renderer::pickShader(MateralType type) {
	Shader* res = nullptr;
	switch (type)
	{
	case MateralType::PHONG:
		res = phongshader;
		break;
	case MateralType::WHITE:
		res = whiteshader;
		break;
	default:
		std::cout << "what the fucking type of this shader?\n";
		break;
	}
	return res;
}



