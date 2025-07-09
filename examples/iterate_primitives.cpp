/**
 * This example shows how to iterate primitives over a mesh without connectivity
*/
#include <ultimaille/all.h>


using namespace UM;

int main() {

    // --- LOAD ---

    // Get path of current executable
    const std::string input_dir = ASSETS_INPUT_DIR;

    // Declare a mesh with triangle surface
    Triangles m;
    // Loading catorus.geogram into m
    read_by_extension(input_dir + "catorus.geogram", m);

    // --- ITERATE ---

    // Iterate over vertices
    std::cout << "iter over vertices: " << std::endl;
    for (auto v : m.iter_vertices()) {
        std::cout << (int)v << ": ( " << v.pos() << "), ";
    }
    std::cout << std::endl;

    // Iterate over facets
    std::cout << "iter over facets: " << std::endl;
    for (auto f : m.iter_facets()) {
        std::cout << (int)f << ", ";
    }
    std::cout << std::endl;

    // Iterate over hald-edges
    std::cout << "iter over half-edges: " << std::endl;
    for (auto he : m.iter_halfedges()) {
        std::cout << (int)he << ", ";
    }
    std::cout << std::endl;

    // --- END ---

    return 0;
}