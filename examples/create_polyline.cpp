/**
 * This example shows how to create a polyline from scratch
*/
#include <ultimaille/all.h>


using namespace UM;

int main() {

    const std::string output_dir = OUTPUT_DIR;

    // --- LOAD ---

    // Declare a polyline
    PolyLine p;

    // --- CREATE ---

    // Create 5 points in polyline
    p.points.create_points(5);
    p.points[0] = vec3(0, 0, 0);
    p.points[1] = vec3(1, 0, 0);
    p.points[2] = vec3(1, 1, 0);
    p.points[3] = vec3(0, 1, 0);
    p.points[4] = vec3(0.5, 0.5, 1);

    // Create edges
    p.create_edges(8);

    // Link segment 0 with point 0
    p.vert(0, 0) = 0;
    // Link segment 0 with point 1
    p.vert(0, 1) = 1;

    // Link segment 1 with point 0
    p.vert(1, 0) = 1;
    // ...
    p.vert(1, 1) = 2;

    p.vert(2, 0) = 2;
    p.vert(2, 1) = 3;

    p.vert(3, 0) = 3;
    p.vert(3, 1) = 0;

    p.vert(4, 0) = 0;
    p.vert(4, 1) = 4;

    p.vert(5, 0) = 1;
    p.vert(5, 1) = 4;

    p.vert(6, 0) = 2;
    p.vert(6, 1) = 4;

    p.vert(7, 0) = 3;
    p.vert(7, 1) = 4;

    EdgeAttribute<int> edge_attr(p);
    edge_attr[0] = 0;
    edge_attr[1] = 1;

    // --- SAVE ---

    // Save mesh
    write_by_extension(output_dir + "pyramid.geogram", p, {{"my_edge_attr", edge_attr}});

    // --- END ---

    // --- RUN ---

    #ifdef _WIN32
    // Open the generated mesh with Graphite
    std::string graphite_path = GRAPHITE_PATH;
    int result = system((graphite_path + " " + output_dir + "pyramid.geogram").c_str());
    #endif

    return 0;
}