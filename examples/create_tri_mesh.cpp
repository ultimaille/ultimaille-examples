/**
 * This example shows how to create tri mesh from scratch
*/
#include <ultimaille/all.h>


using namespace UM;

int main(int argc, char** argv) {

    // --- LOAD ---

    // Declare a mesh with triangle surface
    Triangles m;

    // --- CREATE ---

    // Create 5 points in mesh
    m.points.create_points(5);
    m.points[0] = vec3(0.,0.,0.);
    m.points[1] = vec3(1.,0.,0.);
    m.points[2] = vec3(0.5,1.,0.);
    m.points[3] = vec3(1.5,1.,0.);
    m.points[4] = vec3(1.,2.,0.);

    // Create 5 facets
    m.create_facets(3);
    // Link facet 0, vertex 0 with point 0
    m.vert(0, 0) = 0;
    // Link facet 0, vertex 1 with point 1
    m.vert(0, 1) = 1;
    // Link facet 0, vertex 2 with point 2
    m.vert(0, 2) = 2;

    // Link facet 1, vertex 0 with point 1
    m.vert(1, 0) = 1;
    // ...
    m.vert(1, 1) = 3;
    m.vert(1, 2) = 2;

    m.vert(2, 0) = 2;
    m.vert(2, 1) = 3;
    m.vert(2, 2) = 4;

    // --- SAVE ---

    // Save mesh
    write_by_extension("tri_mesh.geogram", m, {{}, {}, {}});

    // --- END ---

    return 0;
}