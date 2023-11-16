#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

void dist_from_vertex(Triangles& mesh, Surface::Vertex& src_vertex, UM::PointAttribute<double>& dist_attr) {

    // Init
    for (auto v : mesh.iter_vertices()) {
        dist_attr[v] = std::numeric_limits<double>::max();
    }
    dist_attr[src_vertex] = 0;

    int i = 0;
    bool unvisitedRemains;
    
    // Loop until all distances are set
    do {

        unvisitedRemains = false;

        // Iter on halfedges
        for (auto h : mesh.iter_halfedges()) {

            double distFrom = dist_attr[h.from()];
            double distTo = dist_attr[h.to()];

            if (distFrom + 1 < distTo) {
                dist_attr[h.to()] = dist_attr[h.from()] + 1;
                unvisitedRemains = true;
            }
        }
        i++;
        

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

