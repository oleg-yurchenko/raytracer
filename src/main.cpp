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
#include "material.h"

#define WIDTH 1280
#define HEIGHT 720
//#define WIDTH 2560
//#define HEIGHT 1440

#define OUT_PATH "/Users/olegyurchenko/dev/raytracing/img/"

typedef Color3     Color;
typedef Point3     Point;
typedef Direction3 Dir;

using namespace std;

static constexpr const double DEFAULT_ASPECT_RATIO    {(double)WIDTH/HEIGHT};

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

  HittableList world;
  std::shared_ptr<Material> groundMat = std::make_shared<Lambertian>(Color3(0.5F, 0.5F, 0.5F));
  world.add(std::make_shared<Sphere>(Point(0.0F, -1000.0F, 0.0F), 1000, groundMat));

  for (int a = -11; a < 11; ++a)
  {
    for (int b = -11; b < 11; ++b)
    {
      double chooseMat = randDouble();
      Point center {a + 0.9F*randDouble(), 0.2, b + 0.9F*randDouble()};

      if ((center - Point(4.0F, 0.2F, 0.0F)).lengthSquared() > 0.81F)
      {
        std::shared_ptr<Material> mat;

        if (chooseMat < 0.8F)
        {
          // diffuse
          Color3 albedo = Color3(randDouble(), randDouble(), randDouble());
          mat = std::make_shared<Lambertian>(albedo);
          world.add(std::make_shared<Sphere>(center, 0.2F, mat));
        }
        else if (chooseMat < 0.95F)
        {
          // metal
          Color3 albedo = Color3::random(0.5F, 1.0F);
          double fuzz = randDouble(0, 0.5F);
          mat = std::make_shared<Metal>(albedo, fuzz);
          world.add(std::make_shared<Sphere>(center, 0.2F, mat));
        }
        else
        {
          // glass
          mat = std::make_shared<Dielectric>(1.5F);
          world.add(std::make_shared<Sphere>(center, 0.2F, mat));
        }
      }
    }
  }

  std::shared_ptr<Material> mat1 = std::make_shared<Dielectric>(1.5F);
  world.add(std::make_shared<Sphere>(Point(0.0F, 1.0F, 0.0F), 1.0F, mat1));
  std::shared_ptr<Material> mat2 = std::make_shared<Lambertian>(Color3(0.4F, 0.2F, 0.1F));
  world.add(std::make_shared<Sphere>(Point(-4.0F, 1.0F, 0.0F), 1.0F, mat2));
  std::shared_ptr<Material> mat3 = std::make_shared<Metal>(Color3(0.7F, 0.6F, 0.5F), 0.0F);
  world.add(std::make_shared<Sphere>(Point(4.0F, 1.0F, 0.0F), 1.0F, mat3));

  // create our main camera
  shared_ptr<Camera> mainCamera = MainCameraFactory::makeMainCamera({WIDTH, HEIGHT}, DEFAULT_ASPECT_RATIO);

  // move the camera
  mainCamera->move(Point(13.0F, 2.0F, 3.0F), Point(0.0F, 0.0F, 0.0F), 10.0F);

  // render the image given the world using the main camera
  Color3* rawImage = mainCamera->render(world, nullptr);

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
