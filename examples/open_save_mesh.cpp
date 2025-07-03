#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

int main() {

    // Get path of current executable
    std::string path = getAssetPath();

    // Declare a mesh with triangle surface
    Triangles m;
    // Loading catorus.geogram into m
    read_by_extension(path + "catorus.geogram", m);

    // Display the number of vertices, facets and corners
    std::cout 
        << "n vertices: " << m.nverts() 
        << ", n facets: " << m.nfacets() 
        << ", n corners: " << m.ncorners() << std::endl;

    // Save mesh
    write_by_extension("catorus_cpy.obj", m);

    return 0;
}

