#include <iostream>
#include <chrono>
#include "SceneLoader.hpp"

int main(int argc, char *argv[])
{
  std::cout << std::endl;
  std::cout << "*********************************" << std::endl;
  std::cout << "*** Kevin's Awesome Raytracer ***" << std::endl;
  std::cout << "*********************************" << std::endl;
  std::cout << std::endl;

  if (argc < 2)
  {
    std::cerr << "[ERROR] Please a path your scene file (.json)" << std::endl;
    std::cout << std::endl;
    exit(0);
  }

  std::cout << "-----------------------------------" << std::endl;
  std::cout << "Optimizations:" << std::endl;
  #ifdef AABB_ON
  std::cout << "AABB is ON." << std::endl;
  #else
  std::cout << "AABB is OFF." << std::endl;
  #endif

  #ifdef MULTITHREAD_ON
  std::cout << "Multithreading is ON." << std::endl;
  #else
  std::cout << "Multithreading is OFF." << std::endl;
  #endif
  std::cout << "-----------------------------------" << std::endl;

  std::string path = argv[1];
  auto [scene, camera, image] = SceneLoader::Load(path);

  std::string outpath = "image.png";
  if (argc > 2)
  {
    outpath = argv[2];
  }

  std::cout << "Rendering " << image->width << "x" << image->height << " pixels..." << std::endl;

  auto begin = std::chrono::high_resolution_clock::now();
  camera->render(*image, *scene);
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  std::cout << "Done." << std::endl;
  const double NANOSECONDS_TO_SECONDS = 1.0 * 1e-9;
  std::printf("Total time: %.3f seconds.\n", elapsed.count() * NANOSECONDS_TO_SECONDS);

  std::cout << "Writing file: " << outpath << std::endl;
  image->writeFile(outpath);

  std::cout << "Cleaning up..." << std::endl;

  delete scene;
  delete camera;
  delete image;

  std::cout << "Done. Goodbye!" << std::endl;
}
