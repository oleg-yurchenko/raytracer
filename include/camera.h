#pragma once

#include "hittable.h"
#include "color.h"
#include <memory>
#include <iostream>
#include "material.h"

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

  // default camera settings
  Point3     eyePoint;
  Direction3 look; // focalLength is the length of this vector!!
  Viewport   viewport;
  size_t     maxBounce;
  
  // multisampling settings
  size_t            samplesPerPixel;
  double            pixelSampleScale;
  Vector<double, 2> (*sampleRegion)(void);

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
  inline Color3 rayColor(const Ray3& r, size_t depth, const Hittable& world) const
  {
    if (depth == 0)
      return {};

    // hitbox
    HitRecord hr;
    if (world.hit(r, IntervalD(0.001F, infty), hr))
    {
      Ray3 scattered;
      Color3 attenuation;
      if (hr.mat->scatter(r, hr, attenuation, scattered))
      {
        //return attenuation * rayColor(scattered, depth-1, world);
        Color3 outCol = rayColor(scattered, depth - 1, world);
        outCol.r *= attenuation.r;
        outCol.g *= attenuation.g;
        outCol.b *= attenuation.b;
        return outCol;
      }
      return Color3();
    }

    // skybox
    Direction3 unitDir {r.direction().normalized()};
    double l = 0.5F*(unitDir.y + 1.0F);
    return Color3(1.0F, 1.0F, 1.0F)*(1.0F-l) + Color3(0.5F, 0.7F, 1.0F)*l;
  }

  static const Interval<double> intensity;

  // multisampling-specific functions
  inline Point3 getSamplePixelPosition(size_t x, size_t y) const
  {
    Vector<double, 2> offset {sampleRegion()};
    return getViewportUpperLeft()
      + (viewport.px_du * (x + offset.x))
      + (viewport.px_dv * (y + offset.y));
  }
  inline Direction3 getSamplePixelDirection(size_t x, size_t y) const
  {
    return getSamplePixelPosition(x, y) - eyePoint;
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
