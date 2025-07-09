#include <ultimaille/all.h>


using namespace UM;

int main() {

    // Get path of current executable
    const std::string input_dir = ASSETS_INPUT_DIR;
    const std::string ouput_dir = OUTPUT_DIR;

    // Declare a mesh with triangle surface
    Triangles m;
    // Loading catorus.geogram into m
    read_by_extension(input_dir + "catorus.geogram", m);

    // Display the number of vertices, facets and corners
    std::cout 
        << "n vertices: " << m.nverts() 
        << ", n facets: " << m.nfacets() 
        << ", n corners: " << m.ncorners() << std::endl;

    // Save mesh
    write_by_extension(ouput_dir + "catorus_cpy.obj", m);

    return 0;
}

