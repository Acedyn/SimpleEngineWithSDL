#include "ship.h"
#include "spriteComponent.h"
#include "assets.h"
#include "inputComponent.h"
#include "maths.h"
#include "laser.h"

Ship::Ship() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("ship"));
	InputComponent* ic = new InputComponent(this);
	ic->setMaxForwardSpeed(0.5f);
	ic->setMaxAngularSpeed(0.5f);
}

void Ship::actorInput(const Uint8* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && laserCoolDown <= 0.0f)
	{
		Laser* laser = new Laser();
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());
		laserCoolDown = 0.2f;
	}
}

void Ship::updateActor(float dt)
{
	laserCoolDown -= dt;
}