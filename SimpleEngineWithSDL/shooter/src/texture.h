#pragma once
#include "renderer.h"
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool load(Renderer& rendererP, const std::string& fileNameP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	std::string fileName;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};