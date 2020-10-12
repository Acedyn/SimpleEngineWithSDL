#pragma once
#include "window.h"
#include "renderer.h"
#include "vector2.h"
#include "actor.h"
#include "timer.h"
#include <vector>

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() :
		isRunning(true),
		isUpdatingActors(false)
	{};

public:
	bool initialize();
	void loop();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

private:
	void processInput();
	void update(float dt);
	void render();

	Window window;
	Renderer renderer;
	bool isRunning;

	bool isUpdatingActors;
	std::vector<Actor*> actors;
	std::vector<Actor*> pendingActors;

};
