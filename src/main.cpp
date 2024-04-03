#include "raylib.h"
#include "../include/game_object.h"
#include "../include/manager.h"
#include "../include/basic_components.h"

class CollisionResponse : public Component {
public:
    DEFINE_COMPONENT(CollisionResponse);

    void OnCollision(GameObject* other) override {
        auto transform = GetComponent<TransformComponent>();
        transform->Position.x += 10.0f;
    }
};

void Game::Setup() {
    {
        auto o1 = AddObject("o1");
        auto transform = o1->AddComponent<TransformComponent>();
        auto movement = o1->AddComponent<MovementComponent>();
        movement->Speed = 300.0f;
        transform->Position = Vector2{100.0f, 100.0f};
        o1->AddComponent<ControllerComponent>();
        auto render = o1->AddComponent<RenderComponent>();
        render->Color = Fade(BLACK, 0.5f);
        render->Scale = 100.0f;
        auto collider = o1->AddComponent<CollisionComponent>();
        collider->Size = Vector2{100.0f, 100.0f};
    }
    {
        auto o2 = AddObject("o2");
        auto transform = o2->AddComponent<TransformComponent>();
        transform->Position = Vector2{500.0f, 500.0f};
        auto render = o2->AddComponent<RenderComponent>();
        render->Color = Fade(YELLOW, 0.5f);
        render->Scale = 50.0f;
        auto collider = o2->AddComponent<CollisionComponent>();
        collider->Size = Vector2{50.f, 50.0f};
        o2->AddComponent<CollisionResponse>();
    }
}

void Game::Update() {
    UpdateObjects();
    BeginDrawing();
    ClearBackground(WHITE);
    RenderObjects();
    EndDrawing();
}

int main() {
    InitWindow(800, 600, "Game Object Example");
    SetTargetFPS(60);
    // make base scene
    Game::Setup();

    while (!WindowShouldClose()) {
        Game::Mainloop();
    }

    return 0;
}