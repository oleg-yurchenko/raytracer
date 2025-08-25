#pragma once

#include <cmath>
#include <iostream>
#include <cstring>

template<typename T, size_t N>
class Vector
{
public:
  Vector();
  ~Vector();

  Vector<T, N>  operator-() const;
  Vector<T, N>& neg();

  Vector<T, N>  operator+(const Vector<T, N>& other) const;
  Vector<T, N>& operator+=(const Vector<T, N>& other);

  Vector<T, N>  operator+(const T& val) const; // element-wise addition
  Vector<T, N>& operator+=(const T& val);

  Vector<T, N>  operator*(const T& val) const; // element-wise multiplication
  Vector<T, N>& operator*=(const T& val);

  T dot(const Vector<T, N>& other) const;
  T operator*(const Vector<T, N>& other) const; // same as dot()
  
  Vector<T, N>  cross(const Vector<T, N>& other) const;
  Vector<T, N>  operator^(const Vector<T, N>& other) const; // same as cross()
  Vector<T, N>& operator^=(const Vector<T, N>& other);

};

typedef Vector<double, 3> Point;
typedef Vector<double, 3> Color;

template<>
class Vector<double, 3>
{
public:
  Vector(double a = 0.0F, double b = 0.0F, double c = 0.0F)
    : x(a)
    , y(b)
    , z(c)
  {}
  Vector(Vector<double, 3>& other)
  {
    memcpy(vals.data(), other.vals.data(), sizeof(double) * 3);
  }
  ~Vector() = default;

  double length() const;
  double lengthSquared() const;
  void normalize(); // normalizes self
  Vector<double, 3> normalized() const; // returns normalized copy

  union
  {
    std::array<double, 3> vals;
    struct {
      double x;
      double y;
      double z;
    };
    struct {
      double r;
      double g;
      double b;
    };
  };
};
