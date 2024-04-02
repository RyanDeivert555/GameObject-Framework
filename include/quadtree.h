#pragma once
#include "raylib.h"
#include "game_object.h"
#include <memory>
#include <vector>

class Point {
public:
    Vector2 Position;
    GameObject* Object;

    Point(const Vector2& centerPoint, GameObject* object);
};

class QuadTree {
private:
    Rectangle _bounds;
    std::vector<Point> _points;
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
    bool Insert(const Point& p);
    std::vector<GameObject*> Query(const Rectangle& range);
};
