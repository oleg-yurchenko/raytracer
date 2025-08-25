#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <point.h>
#include <color.h>

#define WIDTH 1280
#define HEIGHT 720

#define OUT_PATH "/Users/olegyurchenko/dev/raytracing/img/"

using namespace std;

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

  for (size_t i = 0; i < HEIGHT; ++i)
  {
    clog << "\rScanlines remaining: " << (HEIGHT - i) << ' ' << flush;
    for (size_t j = 0; j < WIDTH; ++j)
    {
      Color c {(double)i/HEIGHT, (double)j/WIDTH, 0.0F};
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
