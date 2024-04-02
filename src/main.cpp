#include "raylib.h"
#include "../include/game_object.h"
#include "../include/manager.h"
#include "../include/basic_components.h"

class CollisionResponse : public Component {
public:
    DEFINE_COMPONENT(CollisionResponse);

    void OnCollision(GameObject* other) override {
        other->GetComponent<RenderComponent>()->Color.a -= 1;
    }
};

void Game::Setup() {
    // o1
    {
        auto o1 = root.AddChild("o1");
        auto transform = o1->AddComponent<TransformComponent>();
        transform->Position = {100.0f, 300.0f};
        auto render = o1->AddComponent<RenderComponent>();
        render->Color = Fade(RED, 0.5f);
        render->Scale = 50.0f;
        auto collider = o1->AddComponent<CollisionComponent>();
        collider->Size = {50.0f, 50.0f};
        o1->AddComponent<CollisionResponse>();
    }
    // o2
    {
        auto o2 = root.AddChild("o2");
        auto transform = o2->AddComponent<TransformComponent>();
        transform->Position = {300.0f, 100.0f};
        auto render = o2->AddComponent<RenderComponent>();
        render->Color = Fade(BLUE, 0.5);
        render->Scale = 200.0f;
        auto movement = o2->AddComponent<MovementComponent>();
        movement->Speed = 200.0;
        movement->Velocity = {0.0f, 1.0f};
        o2->AddComponent<ControllerComponent>();
        auto collider = o2->AddComponent<CollisionComponent>();
        collider->Size = {200.0f, 200.0f};
        {
            // child
            auto child = o2->AddChild("o2 child");
            auto transform = child->AddComponent<TransformComponent>();
            auto render = child->AddComponent<RenderComponent>();
            render->Color = BLACK;
            render->Scale = 20.0f;
            auto collider = child->AddComponent<CollisionComponent>();
            collider->Size = {20.0f, 20.0f};
        }
    }
}

void Game::Update() {
    root.Update();
    BeginDrawing();
    ClearBackground(WHITE);
    root.Render();
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