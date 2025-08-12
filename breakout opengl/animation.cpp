#include "animation.h"


Animation::Animation()
    : frameCount(1), currentFrame(0), frameTime(0.1f), elapsedTime(0.0f), frameSize(glm::vec2(1.0f, 1.0f))
{

}

Animation::Animation(unsigned int frames, float frameDuration)
    : frameCount(frames), currentFrame(0), frameTime(frameDuration), elapsedTime(0.0f), frameSize(glm::vec2(1.0f / frames, 1.0f))
{
    frameSize = glm::vec2(1.0f / frames, 1.0f);
}

void Animation::Update(float dt)
{
    elapsedTime += dt;

    if (elapsedTime >= frameTime) 
    {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

glm::vec2 Animation::GetFrameOffset()
{
    return glm::vec2(currentFrame * frameSize.x, 0.0f);
}
