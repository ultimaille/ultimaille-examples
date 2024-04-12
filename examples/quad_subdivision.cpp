#include "helpers.h"
#include <ultimaille/all.h>

using namespace UM;

int main(/*int argc, char** argv*/) {

    // Get path of current executable
    std::string path = getAssetPath();

    // Open mesh
    Triangles m;
    read_by_extension(path + "quarterdisk_tri.mesh", m);
    m.connect();

    // Group all half-edge with their opposite
    DisjointSet ds(m.ncorners());

    for (auto h : m.iter_halfedges()) {
        if (h.opposite().active()) {
            ds.merge(h, h.opposite());
        }
    }

    std::vector<int> setIds;
    ds.get_sets_id(setIds);

    // Create quad mesh
    Quads qm;
    int n_p = m.nfacets() + m.nverts() + ds.nsets();
    
    int offset = m.nverts();
    std::cout << "n facet " << m.nfacets() << ", nvert:" << m.nverts() << ", ncorners: " << m.ncorners() << std::endl;
    std::cout << "n sets: " << ds.nsets() << std::endl;
    std::cout << "offset: " << offset << std::endl;
    std::cout << "create " << n_p << " points." << std::endl;

    qm.points.create_points(n_p);
    qm.create_facets(3 * m.nfacets());

    for (auto h : m.iter_halfedges()) {

        auto hn = h.next().next();

        // get group at element at i
        auto groupId = setIds[h];
        auto groupIdN = setIds[hn];

        int from_idx = h.from();
        int mid_idx = offset + groupId;
        int midn_idx = offset + groupIdN;
        int g_idx = offset + ds.nsets() + h.facet();
        
        // Compute geometry
        qm.points[from_idx] = h.from().pos();
        qm.points[mid_idx] = (h.from().pos() + h.to().pos()) *.5;
        qm.points[midn_idx] = (hn.from().pos() + hn.to().pos()) * .5;
        qm.points[g_idx] = (h.facet().vertex(0).pos() + h.facet().vertex(1).pos() + h.facet().vertex(2).pos()) / 3.;

        // Rely points
        qm.vert(h,0) = from_idx;
        qm.vert(h,1) = mid_idx;
        qm.vert(h,2) = g_idx;
        qm.vert(h,3) = midn_idx;
    }

    // Save into new file
    write_by_extension("quad_subdivision.geogram", qm, {{}, {}, {}});    

    return 0;
}

