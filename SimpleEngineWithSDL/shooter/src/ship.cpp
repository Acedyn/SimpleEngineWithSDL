#include "ship.h"
#include "spriteComponent.h"
#include "assets.h"
#include "inputComponent.h"
#include "maths.h"

Ship::Ship() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("ship"));
	InputComponent* ic = new InputComponent(this);
	ic->setMaxForwardSpeed(0.5f);
	ic->setMaxAngularSpeed(0.1f);
}