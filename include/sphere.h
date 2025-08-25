#pragma once

#include <hittable.h>

class Sphere : public Hittable
{
public:
  Sphere(const Point3& center, double radius)
    : center(center)
    , radius(std::fmax(0.0F, radius))
  {}

  virtual bool hit(const Ray3& r, IntervalD t, HitRecord& hr) const override;

private:
  Point3 center;
  double radius;
};
