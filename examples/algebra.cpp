/**
 * This example shows how to use vectors and matrices
*/
#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

int main(int argc, char** argv) {

    // --- 2D VECTORS ---

    // Create 2D vectors
    std::cout << "--- 2D Vectors ---" << std::endl;
    vec2 v2a = {1., 1.};
    vec2 v2b = {3., 4.};
    // Addition of vectors
    std::cout << v2a << "+ " << v2b << "= " << v2a + v2b << std::endl;
    // Subtraction of vectors
    std::cout << v2a << "- " << v2b << "= " << v2a - v2b << std::endl;
    // Dot product of vectors
    std::cout << "dot product: " << v2a << ". " << v2b << "= " << v2a * v2b << std::endl;
    // Compute the square of the norm (square of length) of vector
    std::cout << "square norm: " << v2a.norm2() << std::endl;
    // Compute the norm (length) of vector
    std::cout << "norm: " << v2a.norm() << std::endl;
    // Compute the normalization of vector and return it
    std::cout << "normalized: " << v2a.normalized() << std::endl;
    // Normalize vector "in-place"
    v2a.normalize();
    std::cout << "normalized: " << v2a << std::endl;

    // --- 3D VECTORS ---

    // Create 3D vectors
    std::cout << "--- 3D Vectors ---" << std::endl;
    vec3 v3a = {1., 2., 3.};
    vec3 v3b = {3., 4., .5};
    // Addition of vectors
    std::cout << v3a << "+ " << v3b << "= " << v3a + v3b << std::endl;
    // Subtraction of vectors
    std::cout << v3a << "- " << v3b << "= " << v3a - v3b << std::endl;
    // Dot product of vectors
    std::cout << "dot product: " << v3a << ". " << v3b << "= " << v3a * v3b << std::endl;
    // Cross product of vectors
    std::cout << "cross product: " << v3a << ". " << v3b << "= " << cross(v3a, v3b) << std::endl;
    // Compute the square of the norm (square of length) of vector
    std::cout << "square norm: " << v3a.norm2() << std::endl;
    // Compute the norm (length) of vector
    std::cout << "norm: " << v3a.norm() << std::endl;
    // Compute the normalization of vector and return it
    std::cout << "normalized: " << v3a.normalized() << std::endl;
    // Normalize vector "in-place"
    v3a.normalize();
    std::cout << "normalized: " << v3a << std::endl;

    // --- 2x2 MAT ---

    // TODO

    // --- END ---


    return 0;
}