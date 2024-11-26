cmake_minimum_required(VERSION 3.5.0)

enable_testing()

project(raytracer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add openssl
find_package(OpenSSL REQUIRED)

add_executable(raytracer main.cpp)

add_executable(image_compare ./tests/image_compare.cpp)

target_include_directories(image_compare PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/raymath"
                           "${PROJECT_SOURCE_DIR}/src/rayimage"
                           "${PROJECT_SOURCE_DIR}/src/rayscene"
                           )


target_include_directories(raytracer PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/raymath"
                           "${PROJECT_SOURCE_DIR}/src/rayimage"
                           "${PROJECT_SOURCE_DIR}/src/rayscene"
                           )


add_subdirectory(./src/raymath)
add_subdirectory(./src/rayimage)
add_subdirectory(./src/rayscene)
add_subdirectory(./src/lodepng)

target_link_libraries(raytracer 
                      PUBLIC 
                      rayscene
                      raymath
                      rayimage
                      lodepng
                      )

target_link_libraries(image_compare OpenSSL::SSL OpenSSL::Crypto rayscene raymath rayimage lodepng)

# Verify a normal case 
add_test(NAME global_test COMMAND ./raytracer ../scenes/two-spheres-on-plane.json two-spheres-on-plane-builded.png)

# Verify if proram fail whhen there is no json provided
add_test(NAME empty_arg COMMAND ./raytracer)
set_tests_properties(empty_arg PROPERTIES WILL_FAIL FALSE FAIL_REGULAR_EXPRESSION "Usage: raytracer <scene.json> [output.png]")

# Verify if proram fail when the json provided dosent exist
add_test(NAME no_json_test COMMAND ./raytracer ../scenes/nonexistent-file.json nonexistent.png)
set_tests_properties(no_json_test PROPERTIES WILL_FAIL TRUE)

# Verify if proram fail when the json provided is not a valid json
add_test(NAME invalid_json_test COMMAND ./raytracer ../scenes/invalid.json invalid.png)
#WILL_FAIL is set to false because the program will generate black screen
set_tests_properties(invalid_json_test PROPERTIES WILL_FAIL FALSE FAIL_REGULAR_EXPRESSION "Error: Invalid JSON file, black screen generated")

add_test(NAME malformed_json_test COMMAND ./raytracer ../scenes/malformed.json malformed.png)
set_tests_properties(malformed_json_test PROPERTIES WILL_FAIL TRUE FAIL_REGULAR_EXPRESSION "Error: Malformed JSON file, black screen generated")

# Test de résolution d'image
add_test(NAME resolution_check
        COMMAND raytracer ../scenes/two-spheres-on-plane.json res_output.png)
set_tests_properties(resolution_check
        PROPERTIES PASS_REGULAR_EXPRESSION "[0-9]+x[0-9]+ pixels")

add_test(NAME image_compare_test
        COMMAND image_compare ../scenes/two-spheres-on-plane.json ../tests/iso_image/two-spheres-on-plane.png)