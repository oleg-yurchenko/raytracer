#define INL_DBL_3 template<double, 3> \
  inline 

#define VEC_DBL_3 Vector<double, 3>

INL_DBL_3 VEC_DBL_3 operator-() const
{
  return VEC_DBL_3(-x, -y, -z);
}

INL_DBL_3 VEC_DBL_3& neg()
{
  x = -x;
  y = -y;
  z = -z;
  return *this;
}

INL_DBL_3 VEC_DBL_3 operator+(const VEC_DBL_3& other) const
{
  return VEC_DBL_3(x + other.x, y + other.y, z + other.z);
}

INL_DBL_3 VEC_DBL_3& operator+(const VEC_DBL_3* other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

INL_DBL_3 VEC_DBL_3 operator+(const double& val) const
{
  return VEC_DBL_3(x + val, y + val, z + val);
}

INL_DBL_3 VEC_DBL_3& operator+(const double* val)
{
  x += val;
  y += val;
  z += val;
  return *this;
}

INL_DBL_3 VEC_DBL_3 operator*(const double& val) const
{
  return VEC_DBL_3(x * val, y * val, z * val);
}

INL_DBL_3 VEC_DBL_3& operator*=(const double& val)
{
  x *= val;
  y *= val;
  z *= val;
  return *this;
}

INL_DBL_3 double dot(const VEC_DBL_3& other) const
{
  return (x * other.x) + (y * other.y) + (z * other.z);
}

INL_DBL_3 double operator*(const VEC_DBL_3& other) const
{
  return dot(other);
}

INL_DBL_3 VEC_DBL_3 cross(const VEC_DBL_3& other) const
{
  return VEC_DBL_3(
      y * other.z - z * other.y,
      z * other.x - x * other.z,
      x * other.y - y * other.x
    );
}

INL_DBL_3 VEC_DBL_3 operator^(const VEC_DBL_3& other) const
{
  return cross(other);
}

INL_DBL_3 VEC_DBL_3& operator^=(const VEC_DBL_3& other)
{
  vals = cross(other).vals; // maybe faster approach possible, but eh
  return *this;
}

INL_DBL_3 double length() const
{
  return std::sqrt(lengthSquared());
}

INL_DBL_3 double lengthSquared() const
{
  return x*x + y*y + z*z;
}

INL_DBL_3 void normalize()
{
  const double l = length();
  if (l == 0.0F)
    return;

  x /= l;
  y /= l;
  z /= l;
}

INL_DBL_3 VEC_DBL_3 normalized() const
{
  const double l = length();
  if (l == 0.0F)
    return VEC_DBL_3();

  return VEC_DBL_3(x/l, y/l, z/l);
}
