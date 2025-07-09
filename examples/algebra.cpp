/**
 * This example shows how to use vectors and matrices
*/
#include <ultimaille/all.h>


using namespace UM;

int main() {

    // --- 2D VECTORS ---

    // Create 2D vectors
    std::cout << "--- 2D Vectors ---" << std::endl;
    vec2 v2a{1., 1.};
    vec2 v2b{3., 4.};
    // Addition of vectors
    std::cout << v2a << "+ " << v2b << "= " << v2a + v2b << std::endl;
    // Subtraction of vectors
    std::cout << v2a << "- " << v2b << "= " << v2a - v2b << std::endl;
    double a = 2.;
    // Vector scalar multiplication
    std::cout << v2a << "* " << a << " = " << v2a * a << std::endl;
    // Vector scalar division
    std::cout << v2a << "/ " << a << " = " << v2a / a << std::endl;
    // Negate
    std::cout << "-( " << v2a << ")" << " = " << -v2a << std::endl;
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
    vec3 v3a{1., 2., 3.};
    vec3 v3b{3., 4., .5};
    // Addition of vectors
    std::cout << v3a << "+ " << v3b << "= " << v3a + v3b << std::endl;
    // Subtraction of vectors
    std::cout << v3a << "- " << v3b << "= " << v3a - v3b << std::endl;
    // Vector scalar multiplication
    std::cout << v3a << "* " << a << " = " << v3a * a << std::endl;
    // Vector scalar division
    std::cout << v3a << "/ " << a << " = " << v3a / a << std::endl;
    // Negate
    std::cout << "-( " << v3a << ")" << " = " << -v3a << std::endl;
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

    //  Create 2x2 matrix
    std::cout << "--- 2x2 Matrix ---" << std::endl;
    mat2x2 m22a{{{0., 1.}, {1., 0.}}};
    vec2 v2c{0., 1.};
    // Create an identity matrix
    std::cout << "identity: " << mat2x2::identity() << std::endl;
    // Matrix / matrix multiplication
    std::cout << m22a << "* " << m22a << "= " << m22a * m22a << std::endl;
    // Matrix point-wise addition
    std::cout << m22a << "+ " << m22a << "= " << m22a + m22a << std::endl;
    // Matrix point-wise subtraction
    std::cout << m22a << "- " << m22a << "= " << m22a - m22a << std::endl;
    // Matrix / vector multiplication
    std::cout << m22a << "* " << v2c << "= " << m22a * v2c << std::endl << std::endl;
    // Matrix / scalar multiplication
    std::cout << m22a << "* " << a << "= " << m22a * a << std::endl << std::endl;
    // Matrix / scalar division
    std::cout << m22a << "/ " << a << "= " << m22a / a << std::endl << std::endl;
    // Compute the norm (length) of matrix
    std::cout << "norm: " << m22a.norm() << std::endl;
    // Get row 0 of matrix
    std::cout << "Access row 0: " << m22a[0] << std::endl;
    // Get row 1 of matrix
    std::cout << "Access col 1: " << m22a.col(1) << std::endl;
    // Get sum of square norm of rows of matrix
    std::cout << "Sum square: " << m22a.sumsqr() << std::endl;
    // Transpose matrix (swap rows & cols)
    mat2x2 m22b{{{1., 2.}, {3., 4.}}};
    std::cout << "Transpose: " << m22b << "=" << m22b.transpose() << std::endl;

    // std::cout << "Sum square: " << m22b.get_minor() << std::endl;

    // TODO

    // --- END ---


    return 0;
}