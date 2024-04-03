#pragma once
#include "game_object.h"
#include <memory>
#include <vector>

namespace Game {
    GameObject* AddObject(const std::string& name);
    void AddToSceneGraph(GameObject* object);
    void Setup();
    void UpdateObjects();
    void RenderObjects();
    void Update();
    void Mainloop();
}