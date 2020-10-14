#include "actor.h"
#include "game.h"
#include "component.h"
#include "maths.h"
#include <algorithm>

Actor::Actor() :
	state(Actor::ActorState::Active),
	position(Vector2::zero),
	scale(1.0f),
	rotation(0.0f),
	game(Game::instance())
{
	game.addActor(this);
}

// Call all components destructors and ask to the game to remove it from the actors array
Actor::~Actor()
{
	game.removeActor(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::setState(ActorState stateP)
{
	state = stateP;
}

void Actor::setPosition(Vector2 positionP)
{
	position = positionP;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
}

void Actor::setRotation(float rotationP)
{
	rotation = rotationP;
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		updateComponent(dt);
		updateActor(dt);
	}
}

void Actor::updateComponent(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::updateActor(float dt)
{

}

// Add a component to the component array. Called by the component constructor
void Actor::addComponent(Component* component)
{
	int componentOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (componentOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	components.insert(iter, component);
}

// Remove a component to the component array. Called by the component destructor
void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}

Vector2 Actor::getForward() const
{
	return Vector2(Maths::cos(Maths::toRadians(rotation)), -Maths::sin(Maths::toRadians(rotation)));
}

void Actor::processInput(const Uint8* keyState)
{
	if (state == Actor::ActorState::Active)
	{
		for (auto component : components)
		{
			component->processInput(keyState);
		}
		actorInput(keyState);
	}
}

void Actor::actorInput(const Uint8* keyState) {}