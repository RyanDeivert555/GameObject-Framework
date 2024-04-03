#include "../include/game_object.h"
#include "../include/basic_components.h"
#include "raylib.h"
#include <memory>
#include <cassert>

GameObject::GameObject(const std::string& name) {
    Name = name;
}

void GameObject::ProcessCollisions(GameObject* other) {
    for (auto& [_, component] : Components) {
        component->OnCollision(other);
    }
}

void GameObject::Update() {
    for (auto& [_, component] : Components) {
        component->OnUpdate();
    }
}

void GameObject::Render() {
    for (auto& [_, component] : Components) {
        component->OnRender();
    }
}

Component* GameObject::AddComponent(std::unique_ptr<Component> component) {
    component->OnCreate();
    std::size_t id = component->GetTypeId();
    Components.insert_or_assign(id, std::move(component));

    return GetComponent(id);
}

bool GameObject::RemoveComponent(std::size_t id) {
    auto it = Components.find(id);
    if (it == Components.end()) {
        return false;
    }
    it->second->OnDestroy();
    Components.erase(it);

    return true;
}

Component* GameObject::GetComponent(std::size_t id) {
    auto it = Components.find(id);
    if (it == Components.end()) {
        return nullptr;
    }

    return it->second.get();
}

// for Component
Component* Component::GetComponent(size_t id) {
    return Object.GetComponent(id);
}

Rectangle GameObject::GetRect() {
    auto transform = GetComponent<TransformComponent>();
    auto collider = GetComponent<CollisionComponent>();
    
    Vector2 position = transform->Position;
    Vector2 size = collider->Size;

    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}
