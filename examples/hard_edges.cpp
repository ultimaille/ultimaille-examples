#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

void find_hard_edges(Triangles& mesh, CornerAttribute<bool>& hard_edges_attr, double threshold) {

    // Iter on all mesh halfedges
    for (auto h : mesh.iter_halfedges()) {
        
        // Get opposite halfedge
        auto opposite = h.opposite();
        
        // if (!opposite.active())
        //     continue;

        // Compute normals of a face and its opposite face
        vec3 normalA = mesh.util.normal(h.facet());
        vec3 normalB = mesh.util.normal(opposite.facet());
        // Compute the dot product of normals
        double d = normalA * normalB;

        // The closer the scalar product of its normals is to zero, 
        // the closer the angle between two faces is to 90 degrees
        if (std::abs(d) <= threshold) {
            hard_edges_attr[h] = true;
        }
    }

}

int main(int argc, char** argv) {

    std::string path = getExecutablePath();

    // Load mesh from file
    Triangles mesh;
    read_by_extension(path + "/assets/tet_13225.geogram", mesh);
    // Make connectivity
    mesh.connect();

    // Find hard edges
    CornerAttribute<bool> hard_edges_attr(mesh);
    find_hard_edges(mesh, hard_edges_attr, 0.1);

    // Save into new file containing the hard edge into a corner attribute (hard_edge_attr)
    std::string fullpath = path + "/assets/tet_13225_hard_edges.geogram";
    write_by_extension(fullpath, mesh, {{}, {}, {{"hard_edges", hard_edges_attr.ptr}}});

    std::cout << "Save model at " << fullpath << std::endl;

    return 0;
}

