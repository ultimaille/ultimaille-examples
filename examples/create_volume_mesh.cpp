/**
 * This example shows how to create tet/hex volumetric mesh from scratch
*/
#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

int main() {

    // --- LOAD ---

    // Declare a mesh with hex cells
    Hexahedra m;

    // --- CREATE ---

    // Create and place 8 points
    // /!\ There is a vertex numbering convention (https://github.com/ultimaille/ultimaille/tree/master/notes/mesh_vertex_numbering_convention.pdf),
    // it gives a specific order of vertex to be able to rely them correctly
    // Here, this order is given by following points declaration
    // Therefore, we just have to associate vertex i with point i (m.vert(0,i) = i)
    // Note that we could have declared them in any order, but if we did, we'd have to link them in the right order
    m.points.create_points(8);
    m.points[0] = vec3(-0.5,-0.5,-0.5);
    m.points[1] = vec3(0.5,-0.5,-0.5);
    m.points[2] = vec3(-0.5,0.5,-0.5);
    m.points[3] = vec3(0.5,0.5,-0.5);
    m.points[4] = vec3(-0.5,-0.5,0.5);
    m.points[5] = vec3(0.5,-0.5,0.5);
    m.points[6] = vec3(-0.5,0.5,0.5);
    m.points[7] = vec3(0.5,0.5,0.5);

    // Create 1 cell
    m.create_cells(1);
    // Link cell 0, vertex 0 with point 0
    m.vert(0, 0) = 0;
    // Link cell 0, vertex 1 with point 1
    m.vert(0, 1) = 1;
    // ...
    m.vert(0, 2) = 2;
    m.vert(0, 3) = 3;
    m.vert(0, 4) = 4;
    m.vert(0, 5) = 5;
    m.vert(0, 6) = 6;
    m.vert(0, 7) = 7;

    // --- SAVE ---

    // Save mesh
    write_by_extension("hex_mesh.geogram", m);

    // --- END ---

    // --- RUN ---

    #ifdef _WIN32
    // Open the generated mesh with Graphite
    int result = system((getGraphitePath() + " hex_mesh.geogram").c_str());
    #endif

    return 0;
}