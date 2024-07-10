#include "shape.h"
#include "shape.h"

Shape::Shape()
{
}

Shape::~Shape() {
	if (mVao) glDeleteVertexArrays(1, &mVao);
	if (mPosVbo) glDeleteBuffers(1, &mPosVbo);
	if (mUvVbo) glDeleteBuffers(1, &mUvVbo);
	if (mEbo) glDeleteBuffers(1, &mEbo);
    if (mNormal) glDeleteBuffers(1, &mNormal);
}

Shape* Shape::createBox(float size) {
	Shape* shape = new Shape();
	float halfSize = size / 2.0f;
    shape->mIndicesCount = 36;
    float vertices[] = {
        -halfSize, -halfSize, -halfSize,
         halfSize, -halfSize, -halfSize,
         halfSize,  halfSize, -halfSize,
         halfSize,  halfSize, -halfSize,
        -halfSize,  halfSize, -halfSize,
        -halfSize, -halfSize, -halfSize,

        -halfSize, -halfSize,  halfSize,
         halfSize, -halfSize,  halfSize,
         halfSize,  halfSize,  halfSize,
         halfSize,  halfSize,  halfSize,
        -halfSize,  halfSize,  halfSize,
        -halfSize, -halfSize,  halfSize,

        -halfSize,  halfSize,  halfSize,
        -halfSize,  halfSize, -halfSize,
        -halfSize, -halfSize, -halfSize,
        -halfSize, -halfSize, -halfSize,
        -halfSize, -halfSize,  halfSize,
        -halfSize,  halfSize,  halfSize,

         halfSize,  halfSize,  halfSize,
         halfSize,  halfSize, -halfSize,
         halfSize, -halfSize, -halfSize,
         halfSize, -halfSize, -halfSize,
         halfSize, -halfSize,  halfSize,
         halfSize,  halfSize,  halfSize,

        -halfSize, -halfSize, -halfSize,
         halfSize, -halfSize, -halfSize,
         halfSize, -halfSize,  halfSize,
         halfSize, -halfSize,  halfSize,
        -halfSize, -halfSize,  halfSize,
        -halfSize, -halfSize, -halfSize,

        -halfSize,  halfSize, -halfSize,
         halfSize,  halfSize, -halfSize,
         halfSize,  halfSize,  halfSize,
         halfSize,  halfSize,  halfSize,
        -halfSize,  halfSize,  halfSize,
        -halfSize,  halfSize, -halfSize,
    };


    // 定义uv坐标数组
    float uvs[] = {
       0.0f,  0.0f,
       1.0f,  0.0f,
       1.0f,  1.0f,
       1.0f,  1.0f,
       0.0f,  1.0f,
       0.0f,  0.0f,

       0.0f,  0.0f,
       1.0f,  0.0f,
       1.0f,  1.0f,
       1.0f,  1.0f,
       0.0f,  1.0f,
       0.0f,  0.0f,

       1.0f,  0.0f,
       1.0f,  1.0f,
       0.0f,  1.0f,
       0.0f,  1.0f,
       0.0f,  0.0f,
       1.0f,  0.0f,

       1.0f,  0.0f,
       1.0f,  1.0f,
       0.0f,  1.0f,
       0.0f,  1.0f,
       0.0f,  0.0f,
       1.0f,  0.0f,

       0.0f,  1.0f,
       1.0f,  1.0f,
       1.0f,  0.0f,
       1.0f,  0.0f,
       0.0f,  0.0f,
       0.0f,  1.0f,

       0.0f,  1.0f,
       1.0f,  1.0f,
       1.0f,  0.0f,
       1.0f,  0.0f,
       0.0f,  0.0f,
       0.0f,  1.0f,
    };

    float normals[] = {
        0.0, 0.0, - 1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,

        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,

        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,

        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,

        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,

        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
    };


    // 定义索引数组（每面4个顶点，每个三角形的索引是连续的）
    unsigned int indices[] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12,13,14,15,16,17,
        18,19,20,21,22,23,
        24,25,26,27,28,29,
        30,31,32,33,34,35
    };

    GLuint& posVbo = shape->mPosVbo, uvVbo = shape->mUvVbo, norVbo = shape->mNormal;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &uvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glGenBuffers(1, &norVbo);
    glBindBuffer(GL_ARRAY_BUFFER, norVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

    glGenBuffers(1, &shape->mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &shape->mVao);
    glBindVertexArray(shape->mVao);

    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, norVbo);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->mEbo);
    glBindVertexArray(0);
	return shape;
}

Shape* Shape::createSphere(float radius) {
	Shape* shape = new Shape();

    std::vector<GLfloat> positions{};
    std::vector<GLfloat> uvs{};
    std::vector<GLuint> indeices{};
    std::vector<GLfloat> normals{};
    int numLatLines = 160;
    int numLongLines = 160;

    for (int i = 0; i <= numLatLines; i++) {
        for (int j = 0; j <= numLongLines; j++) {
            float phi = i* glm::pi<float>() / numLatLines;
            float thea = j *2 * glm::pi<float>() / numLongLines;

            float y = radius * cos(phi);
            float x = radius * sin(phi) * cos(thea);
            float z = radius * sin(phi) * sin(thea);

            positions.push_back(x);
            positions.push_back(y);
            positions.push_back(z);

            float u =  (float)j / (float) numLongLines;
            float v =  (float)i / (float)numLatLines;

            uvs.push_back(u);
            uvs.push_back(v);

            normals.push_back(x);
            normals.push_back(y);
            normals.push_back(z);
        }
    }

    for (int i = 0; i < numLatLines; i++) {
        for (int j = 0; j < numLongLines; j++) {
            int p1 = i * (numLongLines + 1) + j;
            int p2 = p1 + numLongLines + 1;
            int p3 = p1 + 1;
            int p4 = p2 + 1;

            indeices.push_back(p1);
            indeices.push_back(p2);
            indeices.push_back(p3);
            

            indeices.push_back(p3);
            indeices.push_back(p2);
            indeices.push_back(p4);
        }
    }
    GLuint& posVbo = shape->mPosVbo, uvVbo = shape->mUvVbo, normalVbo = shape->mNormal;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, positions.size()*sizeof(float), positions.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &uvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &normalVbo);
    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &shape->mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeices.size() * sizeof(GLuint), indeices.data(), GL_STATIC_DRAW);


    glGenVertexArrays(1, &shape->mVao);
    glBindVertexArray(shape->mVao);

    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->mEbo);
    glBindVertexArray(0);

    shape->mIndicesCount = indeices.size();

	return shape;
}

Shape* Shape::createPlan(float width, float heigt) {
    Shape* shape = new Shape();

    float hafw = width / 2.0;
    float hafh = heigt / 2.0;


    float positions[] = {
        -hafw, -hafh, 0.0f,
        hafw, -hafh, 0.0f,
        hafw, hafh, 0.0f,
        -hafw, hafh, 0.0f,
    };

    float normals[] = {
        0.0, 0.0, 0.1,

    };

    float uvs[] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    shape->mIndicesCount = 6;

    GLuint& posVbo = shape->mPosVbo, uvVbo = shape->mUvVbo, normalVbo = shape->mNormal;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenBuffers(1, &uvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glGenBuffers(1, &normalVbo);
    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

    glGenBuffers(1, &shape->mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &shape->mVao);
    glBindVertexArray(shape->mVao);

    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->mEbo);
    glBindVertexArray(0);
    return shape;
}
