
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
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");

    // Initialize player object
    player = GameObject(
        glm::vec2(200.0f, 200.0f),             // Position
        glm::vec2(100.0f, 100.0f),             // Size
        ResourceManager::GetTexture("face"),   // Texture
        glm::vec3(1.0f),                       // Color
        glm::vec2(0.0f)                        // Velocity
    );
}


void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    
}

void Game::Render()
{
    if (State == GAME_ACTIVE) {

        Renderer->DrawSprite(ResourceManager::GetTexture("face"),
            player.Position,
            player.Size,
            player.Rotation,
            player.Color
            );
    }

}