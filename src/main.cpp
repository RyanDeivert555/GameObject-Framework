#include "raylib.h"
#include "raymath.h"
#include "../include/game_object.h"
#include "../include/manager.h"
#include "../include/basic_components.h"
#include <iostream>

class CollisionResponse : public Component {
public:
    DEFINE_COMPONENT(CollisionResponse);

    void OnCollision(GameObject* other) override {
        auto p1 = Object.GetComponent<TransformComponent>();
        auto p2 = other->GetComponent<TransformComponent>();
        auto c1 = Object.GetComponent<CollisionComponent>();
        auto c2 = other->GetComponent<CollisionComponent>();

        Vector2 center1 = Vector2Scale(Vector2Add(p1->Position, c1->Size), 0.5f);
        Vector2 center2 = Vector2Scale(Vector2Add(p2->Position, c2->Size), 0.5f);
        Vector2 size1 = c1->Size;
        Vector2 size2 = c2->Size;

        if (center1.x > center2.x - size1.x) {
            p1->Position.x = center2.x - size1.x;
        }
        if (center1.x < center2.x + size2.x) {
            p1->Position.x = center2.x + size2.x;
        }
        if (center1.y > center2.y - size1.y) {
            p1->Position.y = center2.y - size1.y;
        }
        if (center1.y < center2.y + size2.y) {
            p1->Position.y = center2.y + size2.y;
        }
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
            render->Color = Fade(YELLOW, 0.5f);
            render->Scale = 20.0f;
            auto collider = child->AddComponent<CollisionComponent>();
            collider->Size = {20.0f, 20.0f};
            child->AddComponent<CollisionResponse>();
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