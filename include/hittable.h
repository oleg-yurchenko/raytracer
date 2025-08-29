#pragma once

#include <ray.h>
#include <interval.h>
#include <memory>

class Material;

class HitRecord
{
public:
  Point3     p;
  Direction3 normal;
  std::shared_ptr<Material> mat;
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
