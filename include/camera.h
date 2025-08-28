#pragma once

#include "hittable.h"
#include "color.h"
#include <memory>
#include <iostream>

// viewport
struct Viewport
{
  double     width;
  double     height;
  Direction3 v_u;
  Direction3 v_v;
  Direction3 px_du;
  Direction3 px_dv;
  Vector<double, 2> resolution;
};

// camera factory
class CameraFactory
{
protected:
  virtual ~CameraFactory() = 0;
};

// camera
class Camera
{
public:
  Camera() = default;
  ~Camera() = default;

  // Returns a buffer of Color3, whose size is equal to the information given in 
  // the viewport's resolution
  // This function will allocate a new buffer if null is passed
  // in this case, caller MUST free the memory
  // Note that this is passed as a single array, and the returned image will be 
  // ordered left to right, top to bottom
  Color3 *render(const Hittable& world, Color3* buf = nullptr) const;
  void printDebugInfo() const;

  Point3     eyePoint;
  Direction3 look; // focalLength is the length of this vector!!
  Viewport   viewport;

private:
  inline Point3 getViewportUpperLeft() const
  {
    return eyePoint + look - (viewport.v_u + viewport.v_v)*0.5F + (viewport.px_du+viewport.px_dv)*0.5F;
  }
  inline Point3     getPixelPosition(size_t x, size_t y) const
  {
    return getViewportUpperLeft() + viewport.px_du*x + viewport.px_dv*y;
  }
  inline Direction3 getPixelDirection(size_t x, size_t y) const
  {
    return getPixelPosition(x, y) - eyePoint;
  }
  inline Color3 rayColor(const Ray3& r, const Hittable& world) const
  {
    // hitbox
    HitRecord hr;
    if (world.hit(r, IntervalD(0, infty), hr))
      return (hr.normal + Color3(1.0F, 1.0F, 1.0F)) * 0.5F;

    // skybox
    Direction3 unitDir {r.direction().normalized()};
    double l = 0.5F*(unitDir.y + 1.0F);
    return Color3(1.0F, 1.0F, 1.0F)*(1.0F-l) + Color3(0.5F, 0.7F, 1.0F)*l;
  }
};

class MainCameraFactory : public CameraFactory
{
public:
  static std::weak_ptr<Camera> makeMainCamera(Vector<double, 2> imageResolution, double aspectRatio, double viewportScale = 2.0F);
  static void destroyMainCamera();
  static std::weak_ptr<Camera> getMainCamera();

  static MainCameraFactory factory;

private:
  MainCameraFactory()
    : mainCamera(nullptr)
  {}
  virtual ~MainCameraFactory() override;

  std::shared_ptr<Camera> mainCamera;
};
