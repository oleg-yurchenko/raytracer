#include <camera.h>

using namespace std;

MainCameraFactory MainCameraFactory::factory{};
const Interval<double> Camera::intensity{0.0F, 1.0F};

CameraFactory::~CameraFactory() {}

shared_ptr<Camera> MainCameraFactory::makeMainCamera(Vector<double, 2> imageResolution, double aspectRatio)
{
  if (factory.mainCamera)
    return factory.mainCamera;

  factory.mainCamera = make_shared<Camera>();

  // for now, we set the main camera's properties as set in the book
  shared_ptr<Camera> mc = factory.mainCamera;

  mc->vfov = 90.0F;
  mc->viewport.resolution = imageResolution;
  mc->maxBounce = 50;

  // defocus setup
  mc->viewport.defocusAngle = 10.0F;

  // set up camera basis
  mc->move(Point3(0.0F, 0.0F, 0.0F), Direction3(0.0F, 0.0F, -1.0F), 3.4F);


  // multisampling
  mc->samplesPerPixel = 100;
  mc->pixelSampleScale = 1.0F / (double)mc->samplesPerPixel;
  mc->sampleRegion = []() { return Vector<double, 2>(randDouble() - 0.5F, randDouble() - 0.5F); };

  return mc;
}

void MainCameraFactory::destroyMainCamera()
{
  factory.mainCamera = nullptr;
}

shared_ptr<Camera> MainCameraFactory::getMainCamera()
{
  return factory.mainCamera;
}

MainCameraFactory::~MainCameraFactory()
{
  destroyMainCamera();
}

Color3 *Camera::render(const Hittable& world, Color3* buf) const
{
  if (buf == nullptr)
    buf = new Color3[viewport.resolution.w * viewport.resolution.h];

  for (size_t row = 0; row < (size_t)viewport.resolution.h; ++row)
  {
    clog << "\rScanlines remaining: " << (viewport.resolution.h - row) << ' ' << flush;
    for (size_t col = 0; col < (size_t)viewport.resolution.w; ++col)
    {
      // cast multiple sampled pixels
      Color3 multiSampled;
      for (size_t sample = 0; sample < samplesPerPixel; ++sample)
      {
        //Ray3 r{eyePoint, getPixelDirection(col, row)};
        Ray3 r {eyePoint, getSamplePixelDirection(col, row)};
        //Ray3 r = getDefocusRay(col, row);
        multiSampled += rayColor(r, maxBounce, world);
      }

      multiSampled *= pixelSampleScale;

      buf[col + row*((size_t)viewport.resolution.w)] = Color3(linearToGamma(intensity.clamp(multiSampled.r)), linearToGamma(intensity.clamp(multiSampled.g)), linearToGamma(intensity.clamp(multiSampled.b)));
    }
  }

  return buf;
}

void Camera::printDebugInfo() const
{
  cout << "camera created with:" << endl;
  cout << "eyepoint: " << eyePoint.string() << endl;
  cout << "look: " << look.string() << endl;
  cout << "viewport width: " << viewport.width << endl;
  cout << "viewport height: " << viewport.height << endl;
  cout << "viewport u: " << viewport.v_u.string() << endl;
  cout << "viewport v: " << viewport.v_v.string() << endl;
  cout << "viewport du: " << viewport.px_du.string() << endl;
  cout << "viewport dv: " << viewport.px_dv.string() << endl;
  cout << "viewport resolution: " << viewport.resolution.string() << endl;
  cout << "upper left: " << getPixelPosition(0,0).string() << endl;
  cout << "upper left dir: " << getPixelDirection(0,0).string() << endl;

}
