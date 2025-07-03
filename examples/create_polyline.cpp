/**
 * This example shows how to create a polyline from scratch
*/
#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

int main() {

    // --- LOAD ---

    // Declare a polyline
    PolyLine p;

    // --- CREATE ---

    // Create 3 points in polyline
    p.points.create_points(3);
    p.points[0] = {0,0,0};
    p.points[1] = {1,0,0};
    p.points[2] = {1,1,0};

    // Create edges
    p.create_edges(2);

    // Link segment 0 with point 0
    p.vert(0, 0) = 0;
    // Link segment 0 with point 1
    p.vert(0, 1) = 1;
    // Link segment 1 with point 0
    p.vert(1, 0) = 0;
    // ...
    p.vert(1, 1) = 2;

    EdgeAttribute<int> edge_attr(p);

    edge_attr[0] = 0;
    edge_attr[1] = 1;

    // --- SAVE ---

    // Save mesh
    write_by_extension("simple_polyline.geogram", p, {{}, {{"my_edge_attr", edge_attr.ptr}}});

    // --- END ---

    // --- RUN ---

    #ifdef _WIN32
    // Open the generated mesh with Graphite
    int result = system((getGraphitePath() + " simple_polyline.geogram").c_str());
    #endif

    return 0;
}