#pragma once
#include <cstddef>

#define DEFINE_COMPONENT(T) \
static const char* GetComponentName() { return #T; } \
static std::size_t GetComponentId() { return reinterpret_cast<std::size_t>(#T); } \
inline std::size_t GetTypeId() const override { return GetComponentId(); } \
T(GameObject& object) : Component(object) {}

// forward declare
class GameObject;

class Component {
protected:
    GameObject& Object;

public:
    virtual std::size_t GetTypeId() const = 0;

    Component(GameObject& object) : Object(object) {}
    virtual ~Component() = default;

    // no copy
    Component(const Component&) = delete;
    Component& operator=(Component const&) = delete;

    // TODO: make this optional or unique pointer?
    Component* GetComponent(std::size_t id);

    template<class T>
    T* GetComponent() {
        return static_cast<T*>(GetComponent(T::GetComponentId()));
    }

    virtual void OnCreate() {};
    virtual void OnDestroy() {};
    virtual void OnUpdate() {};
    virtual void OnRender() {};
    virtual void OnCollision(GameObject* other) {}
};
