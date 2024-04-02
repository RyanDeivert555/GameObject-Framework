#pragma once
#include "game_object.h"
#include <vector>

namespace Game {
    extern GameObject root;
    extern std::vector<GameObject*> collisionObjects;

    void AddToSceneGraph(GameObject* object);
    void Setup();
    void Update();
    void Mainloop();
}