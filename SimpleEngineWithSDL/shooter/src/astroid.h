#pragma once
#pragma once
#include "Actor.h"
#include "circleCollisionComponent.h"
class Astroid : public Actor
{
public:
	Astroid();
	~Astroid();

	CircleCollisionComponent& getCollision() { return *collision; }

private:
	CircleCollisionComponent* collision;
};