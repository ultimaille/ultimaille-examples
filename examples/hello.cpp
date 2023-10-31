#include <ultimaille/all.h>

using namespace UM;

int main(int argc, char** argv) {

    // Create two vector
    vec3 a(1,2,3);
    vec3 b(4,5,6);

    // Display dot product
    std::cout << "( " << a << ") . ( " << b << ") = " << a * b << std::endl;

    return 0;
}