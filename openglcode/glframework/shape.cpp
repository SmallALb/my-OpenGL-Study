#include "shape.h"


Shape::Shape()
{
}

Shape::~Shape() {
	if (mVertexBuffer) delete[] mVertexBuffer;
}

void Shape::CreateBall(unsigned int Longitude, unsigned int Latitude, float r) {
	if (mVertexBuffer) assert(false);
	mSize = 6 * Longitude * Latitude*12;
	mVertexBuffer = new float[mSize];
	glm::vec3 color = { 1.0, 1.0, 1.0 };
	float pi = glm::pi<float>();
	float lon_step = 1.0f / Longitude;
	float lat_step = 1.0f / Latitude;
	unsigned int offset = 0;
	for (int lon = 0; lon<Longitude; lon++) {
		for (int lat = 0; lat<Latitude; lat++) {

			glm::vec2 uv1;
			glm::vec2 uv2;
			glm::vec2 uv3;
			glm::vec2 uv4;

			glm::vec3 p1 = getPoint(lat * lat_step, lon * lon_step, uv1, r); //(0 0)
			glm::vec3 p2 = getPoint((lat + 1) * lat_step, lon * lon_step, uv2, r); //(1 0)
			glm::vec3 p3 = getPoint((lat + 1) * lat_step, (lon + 1) * lon_step, uv3, r);//(1 1
			glm::vec3 p4 = getPoint(lat * lat_step, (lon + 1) * lon_step, uv4, r);//(0 1)

			glm::vec3 normaline = glm::cross(p3 - p2, p1 - p2);

			//..................
			memcpy(mVertexBuffer + offset, glm::value_ptr(p1), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(mVertexBuffer + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(mVertexBuffer + offset, glm::value_ptr(uv1), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(mVertexBuffer + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//..............
			memcpy(mVertexBuffer + offset, glm::value_ptr(p4), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(mVertexBuffer + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(mVertexBuffer + offset, glm::value_ptr(uv4), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(mVertexBuffer + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//
			memcpy(mVertexBuffer + offset, glm::value_ptr(p3), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(mVertexBuffer + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(mVertexBuffer + offset, glm::value_ptr(uv3), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(mVertexBuffer + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//..............
			memcpy(mVertexBuffer + offset, glm::value_ptr(p1), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(mVertexBuffer + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(mVertexBuffer + offset, glm::value_ptr(uv1), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(mVertexBuffer + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//.............
			memcpy(mVertexBuffer + offset, glm::value_ptr(p3), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(mVertexBuffer + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(mVertexBuffer + offset, glm::value_ptr(uv3), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(mVertexBuffer + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
			//..............
			memcpy(mVertexBuffer + offset, glm::value_ptr(p2), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(mVertexBuffer + offset, glm::value_ptr(color), 4 * sizeof(GLfloat));
			offset += 4;
			memcpy(mVertexBuffer + offset, glm::value_ptr(uv2), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(mVertexBuffer + offset, glm::value_ptr(normaline), 3 * sizeof(GLfloat));
			offset += 3;
		}
	}

	
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexBuffer), mVertexBuffer, GL_STATIC_DRAW);

	//3 EBO创建

	//4 VAO创建
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	//5 绑定vbo ebo 加入属性描述信息
	//5.1 加入位置属性描述信息
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(7 * sizeof(float)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(9 * sizeof(float)));

	glBindVertexArray(0);
}

void Shape::CreateCube(float l, float w) {
	if (mVertexBuffer) assert(false);
	mVertexBuffer = new float[12 * 6 * 6];
	glm::vec3 nor1 = glm::cross(glm::vec3(0.5f, 0.5f, -0.5f) - glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, -0.5) - glm::vec3(-0.5, -0.5, -0.5));
	glm::vec3 nor2 = glm::cross(glm::vec3(0.5f, -0.5f, 0.5f) - glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, 0.5, 0.5) - glm::vec3(-0.5, -0.5, 0.5));
	glm::vec3 nor3 = glm::cross(glm::vec3(-0.5f, -0.5f, -0.5f) - glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-0.5, -0.5, 0.5) - glm::vec3(-0.5, 0.5, 0.5));
	glm::vec3 nor4 = glm::cross(glm::vec3(0.5f, 0.5f, -0.5f) - glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, -0.5, -0.5) - glm::vec3(0.5, 0.5, 0.5));
	glm::vec3 nor5 = glm::cross(glm::vec3(0.5f, -0.5f, -0.5f) - glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5f, -0.5f, 0.5f) - glm::vec3(-0.5, -0.5, -0.5));
	glm::vec3 nor6 = glm::cross(glm::vec3(0.5f, 0.5f, 0.5f) - glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5f, 0.5f, -0.5) - glm::vec3(-0.5, 0.5, -0.5));

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

	mVertexBuffer = positions;

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexBuffer), mVertexBuffer, GL_STATIC_DRAW);

	//3 EBO创建

	//4 VAO创建
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	//5 绑定vbo ebo 加入属性描述信息
	//5.1 加入位置属性描述信息
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(7 * sizeof(float)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(9 * sizeof(float)));

	glBindVertexArray(0);
}

glm::vec3 Shape::getPoint(float u, float v, glm::vec2& uv, float r) {
	float pi = glm::pi<float>();
	float z = r * cos(pi * u);
	float x = r * sin(pi * u) * cos(2 * pi * v);
	float y = r * sin(pi * u) * sin(2 * pi * v);
	uv = glm::vec2(u, 1.0 - v);
	return glm::vec3(x, y, z);
}

