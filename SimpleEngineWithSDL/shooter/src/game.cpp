#include "game.h"
#include "log.h"
#include "assets.h"
#include "animSpriteComponent.h"
#include "spriteComponent.h"
#include "backgroundSpriteComponent.h"
#include "ship.h"
#include "astroid.h"
#include <string>

bool Game::initialize()
{
	//Create the window
	bool isWindowInit = window.initialise();
	//Start the renderer
	bool isRendererInit = renderer.initialize(window);

	// Get the window size
	int windowWidth = window.getWidth();
	int windowHeight = window.getHeight();

	// Return true if no errors
	return isWindowInit && isRendererInit;
}

void Game::loop()
{
	// Create a timer
	Timer timer;
	// Create delta time
	float dt = 0;

	while (isRunning)
	{
		dt = timer.computeDeltaTime();
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::close()
{
	//Close the window
	window.close();
	//Stop the renderer
	renderer.close();
	//Call the SDL_Quit event
	SDL_Quit();
	// Set the variable isRunning to false
	isRunning = false;
}

void Game::processInput()
{
	//Create an SDL event
	SDL_Event event;

	//As long as we are waiting for an event
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//If this event is type quit
		case SDL_QUIT:

			break;
		}
	}
	//Capture a snapshop of the keyboard input
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	// If ESCAPE is pressed
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	isUpdatingActors = true;
	// For each actors ask for update
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// For each penging actors add to the actors array
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	// Empty the pending actors array
	pendingActors.clear();

	std::vector<Actor*> deadActors;
	// For each actors if it is dead add it to the dead actors array
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	// Delete all the actors of the dead array
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

// Add an actor to the actors array. Called by the actor constructor
void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

// Remove an actor to the actors array. Called by the actor destructor
void Game::removeActor(Actor* actor)
{
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

std::vector<Astroid*>& Game::getAstroids()
{
	return astroids;
}

void Game::addAstroid(Astroid* astroid)
{
	astroids.emplace_back(astroid);
}

void Game::removeAstroid(Astroid* astroid)
{
	auto iter = std::find(std::begin(astroids), std::end(astroids), astroid);
	if (iter != astroids.end())
	{
		astroids.erase(iter);
	}
}

void Game::render()
{
	renderer.beginDraw();

	renderer.draw();

	renderer.endDraw();
}

void Game::load()
{
	// Add a texture to the Assets class
	Assets::loadTexture(renderer, "../res/textures/Ship01.png", "ship01");
	Assets::loadTexture(renderer, "../res/textures/Ship02.png", "ship02");
	Assets::loadTexture(renderer, "../res/textures/Ship03.png", "ship03");
	Assets::loadTexture(renderer, "../res/textures/Ship04.png", "ship04");
	Assets::loadTexture(renderer, "../res/textures/Farback01.png", "farback01");
	Assets::loadTexture(renderer, "../res/textures/Farback02.png", "farback02");
	Assets::loadTexture(renderer, "../res/textures/Stars.png", "stars");
	Assets::loadTexture(renderer, "../res/textures/Astroid.png", "astroid");
	Assets::loadTexture(renderer, "../res/textures/Ship.png", "ship");
	Assets::loadTexture(renderer, "../res/textures/Laser.png", "laser");

	// Create a Actor that will contain the SpriteComponent
	//Actor* actor = new Actor();
	// Create a SpriteComponent that will be linked to the texture
	//SpriteComponent* sprite = new SpriteComponent(actor, Assets::getTexture("ship01"));
	//actor->setPosition(Vector2{ 100, 100 });

	// Animated sprite
	std::vector<Texture*> animTexture{
		&Assets::getTexture("ship01"),
		&Assets::getTexture("ship02"),
		&Assets::getTexture("ship03"),
		&Assets::getTexture("ship04") };
	Actor* ship = new Actor();
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTexture);
	ship->setPosition(Vector2{ 100, 500 });

	//Background
	std::vector<Texture*> backgroundCloseTextures{
		&Assets::getTexture("stars"),
		&Assets::getTexture("stars") };
	Actor* backgroundClose = new Actor;
	BackgroundSpriteComponent* backgroundCloseSprite = new BackgroundSpriteComponent(backgroundClose, backgroundCloseTextures, 50);
	backgroundCloseSprite->setScrollSpeed(-0.2f);

	//Stars
	std::vector<Texture*> backgroundFarTextures{
		&Assets::getTexture("farback01"),
		&Assets::getTexture("farback02") };
	Actor* backgroundFar = new Actor;
	BackgroundSpriteComponent* backgroundFarSprite = new BackgroundSpriteComponent(backgroundFar, backgroundFarTextures);
	backgroundFarSprite->setScrollSpeed(-0.2f);

	Ship* shipPlayer = new Ship();
	shipPlayer->setPosition(Vector2(100.0f, 300.0f));

	const int astroidNumber = 8;
	for (int i = 0; i < astroidNumber; ++i)
	{
		new Astroid;
	}
}

void Game::unload()
{
	while (!actors.empty())
	{
		delete actors.back();
	}

	Assets::clear();
}
