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

class Dielectric : public Material
{
public:
  Dielectric(double refracIdx)
    :refracIdx(refracIdx)
  {}

  virtual bool scatter(const Ray3& rIn, const HitRecord& hr, Color3& attenuation, Ray3& scattered) const override
  {
    attenuation = Color3(1.0F, 1.0F, 1.0F);
    const double ri = hr.frontFace ? (1.0F / refracIdx) : refracIdx;

    Direction3 unitDir = rIn.direction().normalized();
    const double cosTheta {std::fmin((-unitDir)*hr.normal, 1.0F)};
    const double sinTheta {std::sqrt(1.0F - cosTheta*cosTheta)};

    const bool cannotRefract {ri * sinTheta > 1.0F};
    Direction3 outDir;

    if (cannotRefract || reflectance(cosTheta, ri) > randDouble())
      outDir = Direction3::reflect(unitDir, hr.normal);
    else
      outDir = Direction3::refract(unitDir, hr.normal, ri);

    scattered = Ray3(hr.p, outDir);
    return true;
  }

private:
  static double reflectance(double cosine, double ri)
  {
    // Schlick's approximation
    double r0 {(1.0F - ri) / (1.0F + ri)};
    r0 = r0*r0;
    return r0 + (1.0F - r0)*std::pow(1.0F-cosine, 5);
  }

  double refracIdx;
};
