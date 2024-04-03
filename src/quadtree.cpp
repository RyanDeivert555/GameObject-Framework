#include "../include/quadtree.h"
#include "raylib.h"
#include <memory>
#include <vector>

bool Collide(GameObject* o1, GameObject* o2) {
    Rectangle r1 = o1->GetRect();
    Rectangle r2 = o2->GetRect();

    return CheckCollisionRecs(r1, r2);
}

QuadTree::QuadTree(const Rectangle& bounds) {
    _bounds = bounds;
    _capacity = 50;
    _topLeft = nullptr;
    _topRight = nullptr;
    _bottomLeft = nullptr;
    _bottomRight = nullptr;
    _divided = false;
}

void QuadTree::subDivide() {
    _divided = true;
    float x = _bounds.x;
    float y = _bounds.y;
    float w = _bounds.width;
    float h = _bounds.height;

    Rectangle topLeft{x, y, w / 2.0f, h / 2.0f};
    _topLeft = std::make_unique<QuadTree>(topLeft);

    Rectangle topRight{x + w / 2.0f, y, w / 2.0f, h / 2.0f};
    _topRight = std::make_unique<QuadTree>(topRight);

    Rectangle bottomLeft{x, y + h / 2.0f, w / 2.0f, h / 2.0f};
    _bottomLeft = std::make_unique<QuadTree>(bottomLeft);

    Rectangle bottomRight{x + w / 2.0f, y + h / 2.0f, w / 2.0f, h / 2.0f};
    _bottomRight = std::make_unique<QuadTree>(bottomRight);
}

bool QuadTree::Insert(GameObject* object) {
    if (!CheckCollisionRecs(object->GetRect(), _bounds)) {
        return false;
    }
    if (_objects.size() < _capacity) {
        _objects.push_back(object);

        return true;
    }
    if (!_divided) {
        subDivide();
    }
    if (_topLeft->Insert(object)) {
        return true;
    }
    if (_topRight->Insert(object)) {
        return true;
    }
    if (_bottomLeft->Insert(object)) {
        return true;
    }
    if (_bottomRight->Insert(object)) {
        return true;
    }
    return false;
}

void QuadTree::Clear() {
    _objects.clear();
    if (_divided) {
        _topLeft->Clear();
        _topRight->Clear();
        _bottomLeft->Clear();
        _bottomRight->Clear();
    }
    _divided = false;
    _topLeft.reset();
    _topRight.reset();
    _bottomLeft.reset();
    _bottomRight.reset();
}

std::vector<GameObject*> QuadTree::Query(const Rectangle& range) {
    std::vector<GameObject*> found{};
    if (!CheckCollisionRecs(range, _bounds)) {
        return found;
    }

    for (const auto& obj : _objects) {
        if (CheckCollisionRecs(obj->GetRect(), range)) {
            found.push_back(obj);
        }
    }

    if (_divided) {
        auto topLeft = _topLeft->Query(range);
        found.insert(
            found.end(), 
            std::make_move_iterator(topLeft.begin()), 
            std::make_move_iterator(topLeft.end())
        );
        auto topRight = _topRight->Query(range);
        found.insert(
            found.end(), 
            std::make_move_iterator(topRight.begin()), 
            std::make_move_iterator(topRight.end())
        );
        auto bottomLeft = _bottomLeft->Query(range);
        found.insert(
            found.end(), 
            std::make_move_iterator(bottomLeft.begin()), 
            std::make_move_iterator(bottomLeft.end())
        );
        auto bottomRight = _bottomRight->Query(range);
        found.insert(
            found.end(), 
            std::make_move_iterator(bottomRight.begin()), 
            std::make_move_iterator(bottomRight.end())
        );
    }

    return found;
}
