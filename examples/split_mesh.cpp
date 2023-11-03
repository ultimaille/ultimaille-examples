#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

void split_mesh(Triangles& mesh, CornerAttribute<bool>& hardEdgeAttr, FacetAttribute<int>& groupAttr) {
    
    // Create DS and add facet as root elements
    DisjointSet ds(mesh.nfacets());
    for (auto f : mesh.iter_facets()) {
        ds.root(f);
    }

    for (auto h : mesh.iter_halfedges()) {
        if (hardEdgeAttr[h])
            continue;

        ds.merge(h.facet(), h.opposite().facet());
    }

    std::vector setIds = mesh.facets;
    ds.get_sets_id(setIds);

    for (int i = 0; i < setIds.size(); i++) {
        groupAttr[i] = setIds[i];
    }

    std::cout << "n set: " << ds.nsets() << std::endl;
}

int main(int argc, char** argv) {

    std::string path = getExecutablePath();

    // Load mesh from file
    Triangles mesh;
    SurfaceAttributes attr = read_by_extension(path + "/assets/tet_13225_hard_edges.geogram", mesh);
    // Make connectivity
    mesh.connect();

    // Get hard edges attribute on the loaded model
    CornerAttribute<bool> hard_edges_attr("hard_edges" , attr, mesh);
    // Create a facet attribute
    FacetAttribute<int> group_attr(mesh);

    split_mesh(mesh, hard_edges_attr, group_attr);

    // Save into new file containing the hard edge into a corner attribute (hard_edge_attr)
    std::string fullpath = path + "/assets/tet_13225_splitted.geogram";
    write_by_extension(fullpath, mesh, {{}, {{"groups", group_attr.ptr}}, {{"hard_edges", hard_edges_attr.ptr}}});

    std::cout << "Save model at " << fullpath << std::endl;

    return 0;
}

