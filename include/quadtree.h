#pragma once
#include "raylib.h"
#include "game_object.h"
#include <memory>
#include <vector>

class QuadTree {
private:
    Rectangle _bounds;
    std::vector<GameObject*> _objects;
    std::size_t _capacity;
    std::unique_ptr<QuadTree> _topLeft;
    std::unique_ptr<QuadTree> _topRight;
    std::unique_ptr<QuadTree> _bottomLeft;
    std::unique_ptr<QuadTree> _bottomRight;
    bool _divided;

    void subDivide();

public:
    QuadTree(const Rectangle& bounds);
    void Clear();
    bool Insert(GameObject* object);
    std::vector<GameObject*> Query(const Rectangle& range);
};
