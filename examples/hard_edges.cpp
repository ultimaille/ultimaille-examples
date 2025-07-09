/**
 * This example shows how to find hard edges according to a given threshold
*/
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
        vec3 normalA = Triangle3(h.facet()).normal();
        vec3 normalB = Triangle3(opposite.facet()).normal();

        // Compute the dot product of normals
        double d = normalA * normalB;

        // The closer the scalar product of its normals is to zero, 
        // the closer the angle between two faces is to 90 degrees
        if (std::abs(d) <= threshold) {
            hard_edges_attr[h] = true;
        }
    }

}

int main() {

    const std::string input_dir = ASSETS_INPUT_DIR;
    const std::string output_dir = OUTPUT_DIR;

    // Load mesh from file
    Triangles mesh;
    read_by_extension(input_dir + "tet_13225.geogram", mesh);
    // Make connectivity
    mesh.connect();

    // Find hard edges and store into corner attribute
    CornerAttribute<bool> hard_edges_attr(mesh);
    find_hard_edges(mesh, hard_edges_attr, 0.1);

    // Save into new file containing the hard edge into a corner attribute (hard_edge_attr)
    write_by_extension(output_dir + "tet_13225_hard_edges.geogram", mesh, {{"hard_edges", hard_edges_attr}});

    return 0;
}

