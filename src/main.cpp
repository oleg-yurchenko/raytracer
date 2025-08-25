#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

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
      // r
      image << int(255.0f * ((float)i/HEIGHT)) << " ";
      // g
      image << int(255.0f * ((float)j/WIDTH)) << " ";
      // b
      image << 0 << " ";
    }
  }

  image << endl;

  clog << "\rDone.";
  for (size_t i = 0; i < 20; ++i)
    clog << ' ';
  clog << endl;

  return 0;
}
