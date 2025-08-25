#define VEC_DBL_3 Vector<double, 3>

inline VEC_DBL_3 VEC_DBL_3::operator-() const
{
  return VEC_DBL_3(-x, -y, -z);
}

inline VEC_DBL_3 VEC_DBL_3::operator-(const VEC_DBL_3& other) const
{
  return VEC_DBL_3(x-other.x, y-other.y, z-other.z);
}

inline VEC_DBL_3& VEC_DBL_3::operator-=(const VEC_DBL_3& other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

inline VEC_DBL_3& VEC_DBL_3::neg()
{
  x = -x;
  y = -y;
  z = -z;
  return *this;
}

inline VEC_DBL_3 VEC_DBL_3::operator+(const VEC_DBL_3& other) const
{
  return VEC_DBL_3(x + other.x, y + other.y, z + other.z);
}

inline VEC_DBL_3& VEC_DBL_3::operator+=(const VEC_DBL_3& other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

inline VEC_DBL_3 VEC_DBL_3::operator+(const double& val) const
{
  return VEC_DBL_3(x + val, y + val, z + val);
}

inline VEC_DBL_3& VEC_DBL_3::operator+=(const double& val)
{
  x += val;
  y += val;
  z += val;
  return *this;
}

inline VEC_DBL_3 VEC_DBL_3::operator*(const double& val) const
{
  return VEC_DBL_3(x * val, y * val, z * val);
}

inline VEC_DBL_3& VEC_DBL_3::operator*=(const double& val)
{
  x *= val;
  y *= val;
  z *= val;
  return *this;
}

inline double VEC_DBL_3::dot(const VEC_DBL_3& other) const
{
  return (x * other.x) + (y * other.y) + (z * other.z);
}

inline double VEC_DBL_3::operator*(const VEC_DBL_3& other) const
{
  return dot(other);
}

inline VEC_DBL_3 VEC_DBL_3::cross(const VEC_DBL_3& other) const
{
  return VEC_DBL_3(
      y * other.z - z * other.y,
      z * other.x - x * other.z,
      x * other.y - y * other.x
    );
}

inline VEC_DBL_3 VEC_DBL_3::operator^(const VEC_DBL_3& other) const
{
  return cross(other);
}

inline VEC_DBL_3& VEC_DBL_3::operator^=(const VEC_DBL_3& other)
{
  vals = cross(other).vals; // maybe faster approach possible, but eh
  return *this;
}

inline double VEC_DBL_3::length() const
{
  return std::sqrt(lengthSquared());
}

inline double VEC_DBL_3::lengthSquared() const
{
  return x*x + y*y + z*z;
}

inline VEC_DBL_3& VEC_DBL_3::normalize()
{
  const double l = length();
  if (l == 0.0F)
    return *this;

  x /= l;
  y /= l;
  z /= l;
  return *this;
}

inline VEC_DBL_3 VEC_DBL_3::normalized() const
{
  const double l = length();
  if (l == 0.0F)
    return VEC_DBL_3();

  return VEC_DBL_3(x/l, y/l, z/l);
}

inline std::string VEC_DBL_3::string() const
{
  return std::string("(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")");
}
