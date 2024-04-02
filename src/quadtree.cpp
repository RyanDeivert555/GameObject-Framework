#include "../include/quadtree.h"
#include "raylib.h"
#include <memory>
#include <vector>

// should just remove point?
Point::Point(const Vector2& topLeftPoint, GameObject* object) {
    Position = topLeftPoint;
    Object = object;
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

bool QuadTree::Insert(const Point& p) {
    if (!CheckCollisionPointRec(p.Position, _bounds)) {
        return false;
    }
    if (_points.size() < _capacity) {
        _points.push_back(p);

        return true;
    }
    if (!_divided) {
        subDivide();
    }
    if (_topLeft->Insert(p)) {
        return true;
    }
    if (_topRight->Insert(p)) {
        return true;
    }
    if (_bottomLeft->Insert(p)) {
        return true;
    }
    if (_bottomRight->Insert(p)) {
        return true;
    }
    return false;
}

void QuadTree::Clear() {
    _points.clear();
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

    for (const auto& point : _points) {
        if (CheckCollisionPointRec(point.Position, range)) {
            found.push_back(point.Object);
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