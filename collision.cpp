#include "Collision.h"
#include "Game.h"

bool IsPointInsideBox(Box box, Vec2 point)
{
    return point.x >= box.Left && point.x < box.Right && point.y <= box.Bottom && point.y > box.Top;
}

bool LinesOverlap(float startA, float endA, float startB, float endB)
{
    if (startA >= startB && startA < endB)
        return true;

    if (endA >= startB && endA < endB)
        return true;

    if (startB >= startA && startB < endA)
        return true;

    if (endB >= startA && endB < endA)
        return true;

    return false;
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

bool MoveBlockedX(Box Moving, Box Stationary, Direction direction)
{
    float margin = 2.00f;
    //if (direction == Direction::North || direction == Direction::South)
    //{
    //    return false;
    //}
    if (direction == Direction::East)
    {
        if (std::abs(Stationary.Left - Moving.Right) < margin && LinesOverlap(Stationary.Top, Stationary.Bottom, Moving.Top, Moving.Bottom))
        {
            return true;
        }
    }
    if (direction == Direction::West)
    {
        if (std::abs(Moving.Left - Stationary.Right) < margin && LinesOverlap(Stationary.Top, Stationary.Bottom, Moving.Top, Moving.Bottom))
        {
            return true;
        }
    }
    return false;
}

bool MoveBlockedY(Box Moving, Box Stationary, Direction direction)
{
    float margin = 2.00f;
    //if (direction == Direction::East || direction == Direction::West)
    //{
    //    return false;
    //}
    if (direction == Direction::North)
    {
        if (std::abs(Stationary.Bottom - Moving.Top ) < margin && LinesOverlap(Stationary.Left, Stationary.Right, Moving.Left, Moving.Right))
        {
            return true;
        }
    }
    if (direction == Direction::South)
    {
        if (std::abs(Stationary.Top - Moving.Bottom) < margin && LinesOverlap(Stationary.Left, Stationary.Right, Moving.Left, Moving.Right))
        {
            return true;
        }
    }
    return false;
}

bool BoxCollision(Box Moving, std::vector<Box> StationaryBoxes, int speed, Direction* Direction, Vec2 CurrentVelocity, Vec2* OutVelocity)
{
    if (StationaryBoxes.size() == 0)
    {
        return false;
    }

    bool moveBlockX = false;
    bool moveBlockY = false;

    for (int x = 0; x < StationaryBoxes.size(); x++)
    {
        if (MoveBlockedX(Moving, StationaryBoxes[x], *Direction))
        {
            moveBlockX = true;
        }
        if (MoveBlockedY(Moving, StationaryBoxes[x], *Direction))
        {
            moveBlockY = true;
        }


        if (moveBlockX && moveBlockY)
        {
            *OutVelocity = Vec2{ 0.0, 0.0 };
            return true;
        }
    }

    if (moveBlockX)
    {
        *OutVelocity = Vec2{ 0.0, CurrentVelocity.y };
        return true;
    }
    else if (moveBlockY)
    {
        *OutVelocity = Vec2{CurrentVelocity.x, 0.0 };
        return true;
    }
    else
    {
        *OutVelocity = CurrentVelocity;
    }
    return false;

}