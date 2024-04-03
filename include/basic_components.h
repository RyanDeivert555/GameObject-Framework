#pragma once
#include "component.h"
#include "raylib.h"

class TransformComponent : public Component {
public:
    DEFINE_COMPONENT(TransformComponent);

    Vector2 Position{};
    float Rotation{};

    void PushMatrix();
    void PopMatrix();
};

class RenderComponent : public Component {
public:
    DEFINE_COMPONENT(RenderComponent);

    Color Color{};
    Rectangle Source{0.0f, 0.0f, 1.0f, 1.0f};
    float Scale{1.0f};

    void OnRender() override;
};

class MovementComponent : public Component {
public:
    DEFINE_COMPONENT(MovementComponent);

    Vector2 Velocity{};
    float Speed{};

    void OnUpdate() override;
};

class ControllerComponent : public Component {
public:
    DEFINE_COMPONENT(ControllerComponent);

    void OnUpdate() override;
};

class CollisionComponent : public Component {
public:
    DEFINE_COMPONENT(CollisionComponent);
    
    Vector2 Size{};

    void OnCreate() override;
    void OnCollision(GameObject* other) override;
    // debug
    void OnRender() override;
};
