#include "../include/basic_components.h"
#include "../include/game_object.h"
#include "../include/manager.h"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cassert>
#include <memory>

void TransformComponent::PushMatrix() {
    rlPushMatrix();
    rlTranslatef(Position.x, Position.y, 0.0f);
    rlRotatef(Rotation, 0.0f, 0.0f, 1.0f);
}

void TransformComponent::PopMatrix() {
    rlPopMatrix();
}

void RenderComponent::OnRender() {
    auto transform = GetComponent<TransformComponent>();
    if (transform) {
        transform->PushMatrix();
    }

    Rectangle dest{0.0f, 0.0f, std::abs(Source.width * Scale), std::abs(Source.height * Scale)};
    
    Vector2 offset{dest.width * 0.5f, dest.height * 0.5f};
    
    DrawRectanglePro(dest, offset, 0.0f, Color);
    
    if (transform) {
        transform->PopMatrix();
    }
}

void MovementComponent::OnUpdate() {
    auto transform = GetComponent<TransformComponent>();
    assert(transform);
    transform->Position = Vector2Add(transform->Position, Vector2Scale(Velocity, Speed * GetFrameTime()));
}

void ControllerComponent::OnUpdate() {
    auto movement = GetComponent<MovementComponent>();
    assert(movement);

    movement->Velocity = Vector2Zero();
    if (IsKeyDown(KEY_W)) {
        movement->Velocity.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S)) {
        movement->Velocity.y += 1.0f;
    }
    if (IsKeyDown(KEY_A)) {
        movement->Velocity.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D)) {
        movement->Velocity.x += 1.0f;
    }
    movement->Velocity = Vector2Normalize(movement->Velocity);
}

void CollisionComponent::OnCreate() {
    assert(Object.GetComponent<TransformComponent>());
    Game::AddToSceneGraph(&Object);
}

void CollisionComponent::OnCollision(GameObject* other) {
    TraceLog(LOG_INFO, TextFormat("%s hit %s", Object.Name.c_str(), other->Name.c_str()));
}

void CollisionComponent::OnRender() {
    auto transform = Object.GetComponent<TransformComponent>();
    auto collider = Object.GetComponent<CollisionComponent>();
    Vector2 position = transform->Position;
    Vector2 size = collider->Size;

    Rectangle rect{position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};

    DrawRectangleLinesEx(rect, 5.0f, GREEN);
}
