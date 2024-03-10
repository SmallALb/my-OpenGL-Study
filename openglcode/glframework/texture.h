#pragma once
#include "../globa/base.h"


class Texture {
public:
	Texture(const std::string &path, unsigned int unit);
	~Texture();

	void bind();
private:
	unsigned int mTexture{0};
	int mWidth{0};
	int mHeight{0};
	unsigned int mUnit{0};
};