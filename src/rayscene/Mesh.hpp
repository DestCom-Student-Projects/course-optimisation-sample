#pragma once
#include <vector>
#include "SceneObject.hpp"
#include "../raymath/Transform.hpp"
#include "../raymath/Vector3.hpp"
#include "../raymath/Color.hpp"
#include "../raymath/Ray.hpp"
#include "./Triangle.hpp"
#ifdef AABB_ON
#include "../raymath/AABB.hpp"
#endif

class Mesh : public SceneObject
{
private:
  std::vector<Triangle *> triangles;

public:
  Mesh();
  ~Mesh();

  #ifdef AABB_ON
  AABB boundingBox;
  #endif

  void loadFromObj(std::string path);

  virtual void applyTransform() override;
  virtual bool intersects(Ray &r, Intersection &intersection, CullingType culling) override;

  #ifdef AABB_ON
  void updateBoundingBox();
  #endif
};
