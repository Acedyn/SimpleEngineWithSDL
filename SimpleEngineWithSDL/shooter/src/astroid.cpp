#include "astroid.h"
#include "random.h"
#include "window.h"
#include "maths.h"
#include "spriteComponent.h"
#include "moveComponent.h"
#include "assets.h"

Astroid::Astroid() : Actor()
{
	Vector2 randPos = Random::getVector(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
	setPosition(randPos);
	setRotation(Random::getFloatRange(0.0f, Maths::twoPi));

	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("astroid"));
	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(0.1f);
}