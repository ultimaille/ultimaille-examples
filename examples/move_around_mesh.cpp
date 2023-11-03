/**
 * This example shows how to move around a mesh with connectivity
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

    // --- CONNECT ---

    // Connect the mesh 
    // (result to connect the components - primitives - of the mesh)
    // If you comment this instruction you will get the following error: 
    // Surface::Halfedge::facet(): Assertion `m.connected()' failed. Aborted (core dumped)
    m.connect();

    // --- GET OPPOSITE ---

    // Create a facet attribute
    FacetAttribute<int> fa(m, 0);

    // Get a facet
    Surface::Facet f = m.iter_facets().begin().f;

    // Set 1 to this facet attribute
    fa[f] = 1;

    // Repeat 5 times
    for (int i = 0; i < 5; i++) {

        // Get opposite halfedge of the main halfedge of the face
        Surface::Halfedge opposite_he = f.halfedge().opposite();
        // Check if opposite halfedge is active
        // It can be unactive if halfedge is on the border for example
        // Or if there is many opposite, in this case, the mesh is said to be non-manifold
        if (!opposite_he.active())
            break;
        
        // Get facet of the opposite halfedge (opposite facet)
        Surface::Facet opposite_f = opposite_he.facet();

        // Mark attribute of opposite facet
        fa[opposite_f] = 1;
        f = opposite_f;

        // Write the result in a file 
        std::string filename = "catorus_opp_" + std::to_string(i) + ".geogram";
        write_by_extension(filename.c_str(), m, {{}, {{"fa", fa.ptr}}, {}});
    }

    // --- END ---

    return 0;
}


