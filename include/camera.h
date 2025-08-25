#pragma once

#include <point.h>
#include <memory>

// viewport
struct Viewport
{
  double     width;
  double     height;
  Direction3 v_u;
  Direction3 v_v;
  Direction3 px_du;
  Direction3 px_dv;
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

  inline Point3     getPixelPosition(size_t x, size_t y) const
  {
    return getViewportUpperLeft() + viewport.px_du*x + viewport.px_dv*y;
  }
  inline Direction3 getPixelDirection(size_t x, size_t y) const
  {
    return getPixelPosition(x, y) - eyePoint;
  }

  Point3     eyePoint;
  Direction3 look; // focalLength is the length of this vector!!
  Viewport   viewport;

private:
  inline Point3 getViewportUpperLeft() const
  {
    return eyePoint + look - (viewport.v_u + viewport.v_v)*0.5F + (viewport.px_du+viewport.px_dv)*0.5F;
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
