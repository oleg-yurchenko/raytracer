#pragma once

#include <ray.h>
#include <interval.h>

class HitRecord
{
public:
  Point3     p;
  Direction3 normal;
  double     t;
  bool       frontFace;

  inline void setFaceNormal(const Ray3& r, const Direction3& normal)
  {
    frontFace = r.direction() * normal < 0.0F;
    this->normal = frontFace ? normal : -normal;
  }
};

class Hittable
{
public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray3& r, IntervalD t, HitRecord& hr) const = 0;
};
