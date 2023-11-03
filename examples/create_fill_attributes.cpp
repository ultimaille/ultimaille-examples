/**
 * This example shows how to create attributes of different type, fill them
 * save them into a mesh file and reload them from a mesh file
*/
#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

int main(int argc, char** argv) {

    // --- LOAD ---

    // Get path of current executable
    std::string path = getExecutablePath();

    // Declare a mesh with triangle surface
    Triangles m;
    // Loading catorus.geogram into m
    read_by_extension(path + "/assets/catorus.geogram", m);

    // --- FACE ATTR ---

    // Create a facet attribute
    FacetAttribute<int> fa(m);

    // For all facets in mesh, associate a random int value between 0-100
    for (auto f : m.iter_facets())
        fa[f] = rand() % 100;

    // --- SAVE ---

    // Save mesh with all previously created attributes
    write_by_extension("catorus_attr.geogram", m, {{}, {{"fa", fa.ptr}}, {}});

    // --- END ---

    return 0;
}