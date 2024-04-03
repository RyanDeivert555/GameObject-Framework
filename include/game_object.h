#pragma once
#include "raylib.h"
#include "component.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class GameObject {
private:
    GameObject* _parent = nullptr;
    std::vector<GameObject*> _children{};

protected:
    std::unordered_map<std::size_t, std::unique_ptr<Component>> Components{};

public:
    std::string Name{};
    
    GameObject(const std::string& name);
    ~GameObject();

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

    const std::vector<GameObject*>& GetChildren() const {
        return _children;
    }

    GameObject* GetParent() const {
        return _parent;
    }

    GameObject* AddChild(const std::string& name);
    Rectangle GetRect();
};
