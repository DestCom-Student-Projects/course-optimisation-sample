#pragma once
#include "SceneObject.hpp"
#include "../raymath/Vector3.hpp"
#include "../raymath/Color.hpp"
#include "../raymath/Ray.hpp"
#ifdef AABB_ON
#include "../raymath/AABB.hpp"
#endif

class Sphere : public SceneObject
{
private:
  Vector3 center;
  double radius;
  #ifdef AABB_ON
  AABB boundingBox;
  #endif

public:
  Sphere(double r);
  ~Sphere();

  virtual void applyTransform() override;
  virtual bool intersects(Ray &r, Intersection &intersection, CullingType culling) override;
  #ifdef AABB_ON
  void updateBoundingBox();
  #endif
};
