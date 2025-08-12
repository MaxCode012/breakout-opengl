
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

// Game-related State data
SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // Load shader
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");

    Shader shader = ResourceManager::GetShader("sprite");

    glm::mat4 projection = glm::ortho(
        0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f,
        -1.0f, 1.0f
    );

    shader.Use().SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);

    // Initialize renderer
    Renderer = new SpriteRenderer(shader);

    // Load texture
    ResourceManager::LoadTexture("textures/buildings_1.png", true, "b1");
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/Idle.png", true, "player_idle");

    // Initialize player object
    player = GameObject(
        glm::vec2(Width / 2, Height / 2),             // Position
        glm::vec2(128.0f, 128.0f),             // Size
        ResourceManager::GetTexture("player_idle"),   // Texture
        glm::vec3(1.0f),                       // Color
        glm::vec2(0.0f, 100.0f)                        // Velocity
    );

    player.Animation = Animation(
        7,
        0.1f
        );
}


void Game::Update(float dt)
{
    player.Animation.Update(dt);

    player.Velocity.y += gravity * dt;
    player.Position += player.Velocity * dt;

    if (player.Position.y + player.Size.y >= Height) {
        player.Position.y = Height - player.Size.y;
        player.Velocity.y *= -0.8f;
    }

    if (player.Velocity.x >= maxPlayerVelocity)
    {
        player.Velocity.x = maxPlayerVelocity;
    }
    else if (player.Velocity.x <= -maxPlayerVelocity)
    {
        player.Velocity.x = -maxPlayerVelocity;
    }

}

void Game::ProcessInput(float dt)
{
    const float acceleration = 300.0f;

    if (Keys[GLFW_KEY_A]) {
        player.Velocity.x -= acceleration * dt;

    }

    else if (Keys[GLFW_KEY_D])
    {
        player.Velocity.x += acceleration * dt;
    }

    else
    {
        if (player.Velocity.x > 0.0f) {
            player.Velocity.x -= acceleration * dt;
            if (player.Velocity.x < 0.0f)
                player.Velocity.x = 0.0f;
        }
        else if (player.Velocity.x < 0.0f) {
            player.Velocity.x += acceleration * dt;
            if (player.Velocity.x > 0.0f)
                player.Velocity.x = 0.0f;
        }
    }
}

void Game::Render()
{
    if (State == GAME_ACTIVE) {
        Renderer->DrawSprite(
            player.Sprite,
            player.Position,
            player.Size,
            player.Rotation,
            player.Color,
            player.Animation.GetFrameOffset(),  
            player.Animation.frameSize        
        );
    }

}