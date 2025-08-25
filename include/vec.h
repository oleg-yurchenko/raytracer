#pragma once

#include <cmath>
#include <iostream>
#include <cstring>

#define SHARED_VECTOR_FUNCS(T, N) \
  Vector<T, N>  operator-() const; \
  Vector<T, N>  operator-(const Vector<T, N>& other) const; \
  Vector<T, N>& operator-=(const Vector<T, N>& other); \
  Vector<T, N>& neg(); \
  Vector<T, N>  operator+(const Vector<T, N>& other) const; \
  Vector<T, N>& operator+=(const Vector<T, N>& other); \
  Vector<T, N>  operator+(const T& val) const; \
  Vector<T, N>& operator+=(const T& val); \
  Vector<T, N>  operator*(const T& val) const; \
  Vector<T, N>& operator*=(const T& val); \
  T dot(const Vector<T, N>& other) const; \
  T operator*(const Vector<T, N>& other) const; \
  Vector<T, N>  cross(const Vector<T, N>& other) const; \
  Vector<T, N>  operator^(const Vector<T, N>& other) const; \
  Vector<T, N>& operator^=(const Vector<T, N>& other);\
  std::string   string() const;


template<typename T, size_t N>
class Vector
{
public:
  Vector();
  ~Vector();

  SHARED_VECTOR_FUNCS(T,N)

};

template<>
class Vector<double, 3>
{
public:
  Vector(double a = 0.0F, double b = 0.0F, double c = 0.0F)
    : x(a)
    , y(b)
    , z(c)
  {}
  Vector(const Vector<double, 3>& other)
  {
    memcpy(vals.data(), other.vals.data(), sizeof(double) * 3);
  }
  ~Vector() = default;

  SHARED_VECTOR_FUNCS(double, 3)

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

template<>
class Vector<double, 2>
{
public:
  Vector(double a, double b)
    : x(a)
    , y(b)
  {}
  Vector()
    : Vector(0.0F, 0.0F)
  {}

  ~Vector() = default;

  union
  {
    std::array<double, 2> vals;
    struct {
      double x;
      double y;
    };
    struct {
      double w;
      double h;
    };
  };
};

#include <vec.inl>
