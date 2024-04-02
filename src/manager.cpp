#include "../include/manager.h"
#include "../include/basic_components.h"
#include "../include/quadtree.h"
#include "raylib.h"
#include <iostream>

namespace Game {
    GameObject root{"root"};
    // for physics
    std::vector<GameObject*> collisionObjects{};

    void AddToSceneGraph(GameObject* object) {
        collisionObjects.push_back(object);
    }

    void UpdateSceneGraph() {
        float width = static_cast<float>(GetScreenWidth());
        float height = static_cast<float>(GetScreenHeight());
        QuadTree sceneGraph{Rectangle{0.0f, 0.0f, width, height}};
        for (auto obj : collisionObjects) {
            auto position = obj->GetComponent<TransformComponent>()->Position;
            auto collider = obj->GetComponent<CollisionComponent>()->Size;
            position = Vector2{position.x - collider.x / 2.0f, position.y - collider.y / 2.0f};

            Point p{position, obj};
            sceneGraph.Insert(p);
        }
        for (auto obj1 : collisionObjects) {
            auto position = obj1->GetComponent<TransformComponent>()->Position;
            auto size = obj1->GetComponent<CollisionComponent>()->Size;

            // make center oriented
            Rectangle range{position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};

            for (auto obj2 : sceneGraph.Query(range)) {
                if (obj1 != obj2) {
                    obj1->GetComponent<CollisionComponent>()->OnCollision(obj2);
                    obj2->GetComponent<CollisionComponent>()->OnCollision(obj1);
                }
            }
        }
    }

    void Mainloop() {
        UpdateSceneGraph();
        Update();
    }
}
