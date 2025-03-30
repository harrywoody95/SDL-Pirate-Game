#include "Collision.h"

bool IsPointInsideBox(Box box, Vec2 point)
{
    return point.x >= box.Left && point.x < box.Right && point.y <= box.Bottom && point.y > box.Top;
}

bool BoxesOverlap(Box a, Box b)
{
    Vec2 a_lb = Vec2{ a.Left,  a.Bottom };
    Vec2 a_lt = Vec2{ a.Left,  a.Top };
    Vec2 a_rb = Vec2{ a.Right, a.Bottom };
    Vec2 a_rt = Vec2{ a.Right, a.Top };

    Vec2 b_lb = Vec2{ b.Left,  b.Bottom };
    Vec2 b_lt = Vec2{ b.Left,  b.Top };
    Vec2 b_rb = Vec2{ b.Right, b.Bottom };
    Vec2 b_rt = Vec2{ b.Right, b.Top };

    if (IsPointInsideBox(b, a_lb))
        return true;

    if (IsPointInsideBox(b, a_lt))
        return true;

    if (IsPointInsideBox(b, a_rb))
        return true;

    if (IsPointInsideBox(b, a_rt))
        return true;

    if (IsPointInsideBox(a, b_lb))
        return true;

    if (IsPointInsideBox(a, b_lt))
        return true;

    if (IsPointInsideBox(a, b_rb))
        return true;

    if (IsPointInsideBox(a, b_rt))
        return true;

    return false;
}