#pragma once

#include <vec.h>

typedef Vector<double, 3> Color;

inline std::ostream& operator<<(std::ostream& os, const Color& col)
{
  return os << int(col.x * 255.0F) << ' ' << int(col.y * 255.0F) << ' ' << int(col.z * 255.0F) << ' ';
}
