#pragma once

#include <hittable.h>
#include "material.h"
#include <memory>

class Sphere : public Hittable
{
public:
  Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);

  virtual bool hit(const Ray3& r, IntervalD t, HitRecord& hr) const override;

private:
  Point3 center;
  double radius;
  std::shared_ptr<Material> mat;
};
