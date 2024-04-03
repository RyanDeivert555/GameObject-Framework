#pragma once
#include "game_object.h"
#include <memory>
#include <vector>

namespace Game {
    extern std::vector<GameObject*> collisionObjects;
    extern std::vector<std::unique_ptr<GameObject>> objects;

    GameObject* AddObject(const std::string& name);
    void AddToSceneGraph(GameObject* object);
    void Setup();
    void UpdateObjects();
    void RenderObjects();
    void Update();
    void Mainloop();
}