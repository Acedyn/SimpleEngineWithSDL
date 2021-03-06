#include "animSpriteComponent.h"
#include "log.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* ownerP, const std::vector<Texture*>& texturesP, int drawOrderP) :
	SpriteComponent(ownerP, *texturesP[0], drawOrderP),
	currentFrame(0.0f),
	animFPS(0.02f)
{
	setAnimTextures(texturesP);
}

AnimSpriteComponent::~AnimSpriteComponent() {}

void AnimSpriteComponent::setAnimTextures(const std::vector<Texture*>& texturesP)
{
	animTextures = texturesP;
	if (animTextures.size() > 0)
	{
		currentFrame = 0.0f;
		setTexture(*animTextures[0]);
	}
}

void AnimSpriteComponent::setAnimFPS(float animFPSP)
{
	animFPS = animFPSP;
}

void AnimSpriteComponent::update(float dt)
{
	SpriteComponent::update(dt);

	if (animTextures.size() > 0)
	{
		currentFrame += animFPS * dt;
		while (currentFrame >= animTextures.size())
		{
			currentFrame -= animTextures.size();
		}
		setTexture(*animTextures[static_cast<int>(currentFrame)]);
	}
}