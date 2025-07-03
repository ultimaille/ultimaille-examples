/**
 * This example shows how to move around a mesh with connectivity
 * Random walk is an algorithm that choose the next face to move
*/
#include "helpers.h"
#include <ultimaille/all.h>
#include <optional>


using namespace UM;

int main() {

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

    // --- GET OPPOSITE ---

    // Create a facet attribute
    FacetAttribute<int> fa(m, 0);

    // Get a facet
    Surface::Facet f = m.iter_facets().begin().f;

    // Set 1 to this facet attribute
    fa[f] = 1;

    // Repeat 50 times
    for (int i = 0; i < 50; i++) {

        std::optional<Surface::Facet> opposite_f_opt;

        do {

            // Get random halfedge in face
            int lh = rand() % 3;
            Surface::Halfedge random_he = f.halfedge(lh);
            // Get opposite halfedge of the selected halfedge of the face
            Surface::Halfedge opposite_he = random_he.opposite();

            // Check if opposite halfedge is active
            // It can be unactive if halfedge is on the border for example
            // Or if there is many opposite, in this case, the mesh is said to be non-manifold
            if (!opposite_he.active())
                break;
            
            // Get facet of the opposite halfedge (opposite facet)
            opposite_f_opt = std::optional<Surface::Facet>(opposite_he.facet());

        // Does not return to previously traversed faces
        } while (fa[opposite_f_opt.value()] == 1);

        // Mark attribute of opposite facet
        fa[opposite_f_opt.value()] = 1;
        f = opposite_f_opt.value();

        // Write the result in a file 
        std::string filename = "catorus_rw_" + std::to_string(i) + ".geogram";
        write_by_extension(filename.c_str(), m, {{"fa", fa}});
    }

    // --- END ---

    return 0;
}


