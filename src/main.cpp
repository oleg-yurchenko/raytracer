#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <point.h>
#include <color.h>
#include <camera.h>
#include <ray.h>

#define WIDTH 1280
#define HEIGHT 720

#define OUT_PATH "/Users/olegyurchenko/dev/raytracing/img/"

typedef Color3     Color;
typedef Point3     Point;
typedef Direction3 Dir;

using namespace std;

static constexpr const double DEFAULT_ASPECT_RATIO    {(double)WIDTH/HEIGHT};
static constexpr const double DEFAULT_VIEWPORT_HEIGHT {2.0F};
static constexpr const double DEFAULT_VIEWPORT_WIDTH  {DEFAULT_VIEWPORT_HEIGHT * DEFAULT_ASPECT_RATIO};

Color rayColor(const Ray3& r)
{
  Dir unitDir {r.direction().normalized()};
  double l = 0.5F*(unitDir.y + 1.0F);
  return Color(1.0F, 1.0F, 1.0F)*(1.0F-l) + Color(0.5F, 0.7F, 1.0F)*l;
}

int main()
{
  string filename{OUT_PATH};
  filename += "img" + to_string(time(nullptr)) + ".ppm";
  ofstream image{filename, ios::binary | ios::out};

  // set up header of output image
  // First arg sets filetype to ppm
  // Second arg, dimensions of image
  // Third arg, max color value per pixel
  image << "P3 " << WIDTH << " " << HEIGHT << " 255 ";

  // create our main camera
  weak_ptr<Camera> mainCamera = MainCameraFactory::makeMainCamera({WIDTH, HEIGHT}, DEFAULT_ASPECT_RATIO, DEFAULT_VIEWPORT_HEIGHT);

  if (false)
  {
    cout << "camera created with:" << endl;
    cout << "eyepoint: " << mainCamera.lock()->eyePoint.string() << endl;
    cout << "look: " << mainCamera.lock()->look.string() << endl;
    cout << "viewport width: " << mainCamera.lock()->viewport.width << endl;
    cout << "viewport height: " << mainCamera.lock()->viewport.height << endl;
    cout << "viewport u: " << mainCamera.lock()->viewport.v_u.string() << endl;
    cout << "viewport v: " << mainCamera.lock()->viewport.v_v.string() << endl;
    cout << "viewport du: " << mainCamera.lock()->viewport.px_du.string() << endl;
    cout << "viewport dv: " << mainCamera.lock()->viewport.px_dv.string() << endl;
    cout << "upper left: " << mainCamera.lock()->getPixelPosition(0,0).string() << endl;
    cout << "upper left dir: " << mainCamera.lock()->getPixelDirection(0,0).string() << endl;
  }

  for (size_t i = 0; i < HEIGHT; ++i)
  {
    clog << "\rScanlines remaining: " << (HEIGHT - i) << ' ' << flush;
    for (size_t j = 0; j < WIDTH; ++j)
    {
      //cout << "pixel (" << i << "," << j << ") -- " << mainCamera.lock()->getPixelPosition(i, j).string() << endl;
      Ray3 r{mainCamera.lock()->eyePoint, mainCamera.lock()->getPixelDirection(j, i)};
      Color c {rayColor(r)};
      image << c;
    }
  }

  image << endl;

  clog << "\rDone.";
  for (size_t i = 0; i < 20; ++i)
    clog << ' ';
  clog << endl;

  return 0;
}
