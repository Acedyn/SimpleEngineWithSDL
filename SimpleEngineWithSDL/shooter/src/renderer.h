#pragma once
#include"rectangle.h"
#include"window.h"
#include<SDL.h>

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void drawRect(Rectangle& rect);
	void endDraw();
	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;
};