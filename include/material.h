#pragma once

#include "hittable.h"
#include "color.h"
#include "ray.h"

class Material
{
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray3& rIn, const HitRecord& hr, Color3& attenuation, Ray3& scattered) const
  {
    return false;
  }
};

class Lambertian : public Material
{
public:
  Lambertian(const Color3& albedo)
    : albedo(albedo)
  {}

  virtual bool scatter(const Ray3& rIn, const HitRecord& hr, Color3& attenuation, Ray3& scattered) const override
  {
    Direction3 scatterDir = hr.normal + Direction3::randUnit();
    // catch degenerate scatter dir
    if (scatterDir.isNearZero())
      scatterDir = hr.normal;

    scattered = Ray3(hr.p, scatterDir);
    attenuation = albedo;
    return true;
  }

private:
  Color3 albedo;
};

class Metal : public Material
{
public:
  Metal(const Color3& albedo, double fuzz)
    : albedo(albedo)
    , fuzz(fuzz < 1.0F ? fuzz : 1.0F)
  {}

  virtual bool scatter(const Ray3& rIn, const HitRecord& hr, Color3& attenuation, Ray3& scattered) const override
  {
    Direction3 reflected = Direction3::reflect(rIn.direction(), hr.normal).normalize() + (Direction3::randUnit() * fuzz);
    scattered = Ray3(hr.p, reflected);
    attenuation = albedo;
    return scattered.direction() * hr.normal > 0;
  }

private:
  Color3 albedo;
  double fuzz;
};
