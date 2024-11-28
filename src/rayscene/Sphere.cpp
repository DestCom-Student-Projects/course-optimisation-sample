#include <iostream>
#include <cmath>
#include "Sphere.hpp"
#include "../raymath/Vector3.hpp"
#ifdef AABB_ON
#include "../raymath/AABB.hpp"
#endif

Sphere::Sphere(double r) : SceneObject(), radius(r)
{
  #ifdef AABB_ON
  updateBoundingBox();
  #endif
}

Sphere::~Sphere()
{
}

void Sphere::applyTransform()
{
  Vector3 c;
  this->center = this->transform.apply(c);

  #ifdef AABB_ON
  updateBoundingBox();
  #endif
}

bool Sphere::intersects(Ray &r, Intersection &intersection, CullingType culling)
{

  #ifdef AABB_ON
  if (!boundingBox.intersects(r))
  {
    return false;
  }
  #endif

  // Vector from ray origin to center of sphere
  Vector3 OC = center - r.GetPosition();

  // Project OC onto the ray
  Vector3 OP = OC.projectOn(r.GetDirection());

  // If the OP vector is pointing in the opposite direction of the ray
  // ... then it is behind the ray origin, ignore the object
  if (OP.dot(r.GetDirection()) <= 0)
  {
    return false;
  }

  // P is the corner of the right-angle triangle formed by O-C-P
  Vector3 P = r.GetPosition() + OP;

  // Is the length of CP greater than the radius of the circle ? If yes, no intersection!
  Vector3 CP = P - center;
  double distance = CP.length();
  if (distance > radius)
  {
    return false;
  }

  // Calculate the exact point of collision: P1
  double aSquared = radius * radius - distance * distance;
  double a = (aSquared > 0) ? std::sqrt(aSquared) : 0.0;
  double t = OP.length() - a;
  Vector3 P1 = r.GetPosition() + (r.GetDirection() * t);

  // Pre-calculate some useful values for rendering
  intersection.Position = P1;
  intersection.Mat = this->material;
  intersection.Normal = (P1 - center).normalize();

  return true;
}

#ifdef AABB_ON
void Sphere::updateBoundingBox()
{
  Vector3 min = Vector3(center.x - radius, center.y - radius, center.z - radius);
  Vector3 max = Vector3(center.x + radius, center.y + radius, center.z + radius);
  boundingBox = AABB(min, max);
}
#endif