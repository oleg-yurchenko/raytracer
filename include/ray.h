#pragma once

#include <point.h>

template<typename Point, typename Direction>
class Ray
{
public:
  Ray() {}
  Ray(const Point& origin, const Direction& direction)
    : orig(origin)
    , dir(direction)
  {}

  ~Ray() = default;

  inline const Point& origin() const { return orig; }
  inline const Direction& direction() const { return dir; }

  Point at(double t) const;

private:
  Point orig;
  Direction dir;
};

typedef Ray<Point3, Direction3> Ray3;

#include <ray.inl>
