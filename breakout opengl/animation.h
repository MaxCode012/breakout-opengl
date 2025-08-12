#pragma once

#include <glm/glm.hpp>

class Animation
{
private:
	unsigned int frameCount;
	unsigned int currentFrame;
	float frameTime;
	float elapsedTime;

public:
	glm::vec2 frameSize;
	Animation();
	Animation(unsigned int frames, float frameDuration);

	void Update(float dt);
	glm::vec2 GetFrameOffset();

};

