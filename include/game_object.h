#pragma once
#include "raylib.h"
#include "component.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class GameObject {
protected:
    std::unordered_map<std::size_t, std::unique_ptr<Component>> Components{};

public:
    std::string Name{};
    
    GameObject(const std::string& name);
    virtual ~GameObject() = default;

    void ProcessCollisions(GameObject* other);
    void Update();
    void Render();

    Component* AddComponent(std::unique_ptr<Component> component);
    bool RemoveComponent(std::size_t id);
    Component* GetComponent(std::size_t id);

    template<class T>
    T* AddComponent() {
        return static_cast<T*>(GameObject::AddComponent(std::make_unique<T>(*this)));
    }

    template<class T>
    bool RemoveComponent() {
        return GameObject::RemoveComponent(T::GetComponentId());
    }

    template<class T>
    T* GetComponent() {
        return static_cast<T*>(GameObject::GetComponent(T::GetComponentId()));
    }

    Rectangle GetRect();
};
