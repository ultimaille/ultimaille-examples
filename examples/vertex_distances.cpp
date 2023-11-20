/**
 * This example shows how to compute geodesic distance between a source vertex and other vertices
*/
#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

/**
 * Compute (a "brute-force") geodesic distance between source vertex and other vertices
*/
void dist_from_vertex(Triangles& mesh, Surface::Vertex& src_vertex, UM::PointAttribute<double>& dist_attr) {

    // Init distance of all vertices to max value
    for (auto v : mesh.iter_vertices()) {
        dist_attr[v] = std::numeric_limits<double>::max();
    }
    // Source vertex (from wich we compute distance) should be initialized to 0
    dist_attr[src_vertex] = 0;

    // Get number of iter (just for info)
    int i = 0;
    bool unvisitedRemains;
    
    // Loop until all distances are set
    do {

        unvisitedRemains = false;

        // Iter on halfedges
        for (auto h : mesh.iter_halfedges()) {

            // Get current computed distance of "from" point of halfedge
            double distFrom = dist_attr[h.from()];
            // Get current computed distance of "to" point of halfedge
            double distTo = dist_attr[h.to()];

            // ASCII representation of half-edge: (from)----half-edge----->(to)
            // If the distance of "to" point is greater than dist of "from" point + 1
            // It means that the value computed is wrong 
            // We should re-compute the distance of "to" to "from" point + 1 (because it's a neighbor)
            if (distFrom + 1 < distTo) {
                dist_attr[h.to()] = dist_attr[h.from()] + 1;
                // Still vertex visited, we continue to explore the mesh graph
                unvisitedRemains = true;
            }
        }
        i++;
        
    // All distances are well setted
    } while (unvisitedRemains);
    
    std::cout << "n iter: " << i << std::endl;
}

int main(int argc, char** argv) {

    std::string path = getAssetPath();

    // Load mesh from file
    Triangles mesh;
    read_by_extension(path + "catorus.geogram", mesh);
    // Make connectivity
    mesh.connect();

    // Get the first vertex found in mesh
    auto src_vertex = mesh.iter_vertices().begin().v;

    // Compute distance of all vertices from the source vertex
    PointAttribute<double> dist_attr(mesh.points);
    dist_from_vertex(mesh, src_vertex, dist_attr); 

    // Save into new file containing the distance point attribute (dist_attr)
    write_by_extension("catorus_distance.geogram", mesh, {{{"dist", dist_attr.ptr}}, {}, {}});

    return 0;
}

