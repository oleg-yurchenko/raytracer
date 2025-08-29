#include <util.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <point.h>
#include <color.h>
#include <camera.h>
#include <ray.h>
#include <hittable_list.h>
#include <sphere.h>

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


  // Create the world
  HittableList world;
  world.add(std::make_shared<Sphere>(Point(0.0F,0.0F,-1.0F), 0.5F));
  world.add(std::make_shared<Sphere>(Point(0.0F,-100.5F,-1.0F), 100.0F));
  world.add(std::make_shared<Sphere>(Point(1.0F, 2.0F, -2.0F), 2.0F));

  // create our main camera
  weak_ptr<Camera> mainCamera = MainCameraFactory::makeMainCamera({WIDTH, HEIGHT}, DEFAULT_ASPECT_RATIO, DEFAULT_VIEWPORT_HEIGHT);

  // render the image given the world using the main camera
  Color3* rawImage = mainCamera.lock()->render(world, nullptr);

  // write back the image to the file
  for (size_t i = 0; i < WIDTH * HEIGHT; ++i)
    image << rawImage[i];

  image << endl;

  clog << "\rDone.";
  for (size_t i = 0; i < 20; ++i)
    clog << ' ';
  clog << endl;

  delete[] rawImage;

  return 0;
}
