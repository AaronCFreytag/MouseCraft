#pragma once

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Core/UpdatableComponent.h"
#include "Animation.h"


class TransformAnimator : public UpdatableComponent
{
public:
	TransformAnimator();
	~TransformAnimator();

	virtual void Update(float deltaTime);

	// Adds an Animation object to this component.
	void AddAnimation(Animation* animation);

	// Adds an Animation object to this component, overriding the name.
	void AddAnimation(std::string name, Animation* animation);

	// Sets the current animation to be played.
	void SetCurrentAnimation(std::string name);
	
	// Sets how far into the current animation this animator is in. 
	// Takes value 0 to 1.
	void SetProgress(float percent);

	// Changes the playback speed of the animation
	void SetSpeed(float multiplier);

	// If the animation should play only once. Animation will be unset on finish.
	void SetOneShot(bool oneShot);

	// Returns if animations will play only once. 
	bool GetOneShot() const;

private:
	std::map<std::string, Animation*> _anims;
	float _counter;
	float _speed = 1.0f;
	bool _oneShot = false;
	Animation* _currentAnim = nullptr;
};
