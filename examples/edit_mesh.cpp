/**
 * This example shows how to edit an existing mesh
*/
#include <ultimaille/all.h>


using namespace UM;

int main(int argc, char** argv) {

    // --- CREATE ---

    // Init a Quad mesh
    // We will create a cube
    Quads m;

    // Create and place 8 points
    m.points.create_points(8);
    m.points[0] = vec3(-1, -1, 1);
    m.points[1] = vec3(1, -1, 1);
    m.points[2] = vec3(1, -1, -1);
    m.points[3] = vec3(-1, -1, -1);
    m.points[4] = vec3(-1, 1, 1);
    m.points[5] = vec3(1, 1, 1);
    m.points[6] = vec3(1, 1, -1);
    m.points[7] = vec3(-1, 1, -1);

    // Create cube facets
    m.create_facets(6);

    // Link facet 0, vertex 0 with point 0
    m.vert(0, 0) = 0;
    // Link facet 0, vertex 1 with point 1
    m.vert(0, 1) = 1;
    // ...
    m.vert(0, 2) = 2;
    m.vert(0, 3) = 3;

    // Link facet 1, vertex 0 with point 4
    m.vert(1, 0) = 4;
    // ...
    m.vert(1, 1) = 5;
    m.vert(1, 2) = 6;
    m.vert(1, 3) = 7;

    m.vert(2, 0) = 0;
    m.vert(2, 1) = 1;
    m.vert(2, 2) = 5;
    m.vert(2, 3) = 4;

    m.vert(3, 0) = 3;
    m.vert(3, 1) = 2;
    m.vert(3, 2) = 6;
    m.vert(3, 3) = 7;

    m.vert(4, 0) = 0;
    m.vert(4, 1) = 4;
    m.vert(4, 2) = 7;
    m.vert(4, 3) = 3;

    m.vert(5, 0) = 1;
    m.vert(5, 1) = 5;
    m.vert(5, 2) = 6;
    m.vert(5, 3) = 2;
    
    // Connect mesh
    m.connect();

    // --- SAVE ---

    // Save cube
    write_by_extension("cube.geogram", m);

    // --- DELETE FACET ---

    // Delete facet
    
    // Deactivate facet 5
    m.conn->active[5] = false;
    // Remove deactivated facets
    m.compact();

    // Save cube without a face
    write_by_extension("cube_without_face.geogram", m);

    // --- CREATE FACET ---

    // Create facet (fill hole)
    m.conn->create_facet({1, 5, 6, 2});

    // Save 
    write_by_extension("cube_filled.geogram", m);

    // --- MOVE POINT ---

    // We move all points of facet 0
    m.points[0] = vec3(-1, -2, 1);
    m.points[1] = vec3(1, -2, 1);
    m.points[2] = vec3(1, -2, -1);
    m.points[3] = vec3(-1, -2, -1);

    // Save
    write_by_extension("cube_deform.geogram", m);

    // --- END ---

    return 0;
}