/**
 * This example shows how to iterate primitives over a mesh with connectivity
*/
#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

int main(int argc, char** argv) {

    // --- LOAD ---

    // Get path of current executable
    std::string path = getAssetPath();

    // Declare a mesh with triangle surface
    Triangles m;
    // Loading catorus.geogram into m
    read_by_extension(path + "catorus.geogram", m);

    // --- CONNECT ---

    // Connect the mesh 
    // (result to connect the components - primitives - of the mesh)
    // If you comment this instruction you will get the following error: 
    // Surface::Halfedge::facet(): Assertion `m.connected()' failed. Aborted (core dumped)
    m.connect();

    // --- ITERATE ---

    // Iterate over facets
    for (auto f : m.iter_facets()) {

        // Print info about facet
        std::cout 
            << std::endl
            << "facet: " << f 
            << " has " << f.size() << " sides. " 
            << std::endl;

        // Iterate over half-edge of the facet
        // This only be possible on connected mesh !
        for (auto he : f.iter_halfedges()) {
            // Print info about edge 
            std::cout 
                << "hald-edge " << he << ":" 
                << he.from().pos() << "," 
                << he.to().pos() 
                << std::endl;
        }
    }

    // --- END ---

    return 0;
}