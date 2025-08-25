#include <camera.h>

MainCameraFactory MainCameraFactory::factory{};

CameraFactory::~CameraFactory() {}

std::weak_ptr<Camera> MainCameraFactory::makeMainCamera(Vector<double, 2> imageResolution, double aspectRatio, double viewportScale)
{
  if (factory.mainCamera)
    return factory.mainCamera;

  factory.mainCamera = std::make_shared<Camera>();

  // for now, we set the main camera's properties as set in the book
  std::shared_ptr<Camera> mc = factory.mainCamera;

  mc->eyePoint = {0.0F,0.0F,0.0F};
  mc->look = {0.0F, 0.0F, -1.0F};
  mc->viewport.width =  viewportScale*aspectRatio;
  mc->viewport.height = viewportScale;
  mc->viewport.v_u = {mc->viewport.width, 0.0F, 0.0F};
  mc->viewport.v_v = {0.0F, -mc->viewport.height, 0.0F};
  mc->viewport.px_du = mc->viewport.v_u * (1.0F / imageResolution.w);
  mc->viewport.px_dv = mc->viewport.v_v * (1.0F / imageResolution.h);

  return mc;
}

void MainCameraFactory::destroyMainCamera()
{
  factory.mainCamera = nullptr;
}

std::weak_ptr<Camera> MainCameraFactory::getMainCamera()
{
  return factory.mainCamera;
}

MainCameraFactory::~MainCameraFactory()
{
  destroyMainCamera();
}
