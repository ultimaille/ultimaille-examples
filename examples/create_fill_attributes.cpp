/**
 * This example shows how to create attributes of different type, fill them
 * save them into a mesh file and reload them from a mesh file
*/
#include "helpers.h"
#include <ultimaille/all.h>


using namespace UM;

int main() {

    // --- LOAD ---

    // Get path of current executable
    std::string path = getAssetPath();

    // Declare a mesh with triangle surface
    Triangles m;
    // Loading catorus.geogram into m
    read_by_extension(path + "catorus.geogram", m);
    m.connect();

    // Declare a polyline
    PolyLine p;
    // Loading pyramid.geogram into p
    read_by_extension(path + "pyramid.geogram", p);

    // --- POINT ATTR ---

    // Create a point attribute
    PointAttribute<double> pa(m.points);

    for (auto v : m.iter_vertices()) {
        // Compute manhattan distance (l1-norm) between origin and vertex
        auto d = vec3(0,0,0) - v.pos();
        pa[v] = std::abs(d.x) + std::abs(d.y) + std::abs(d.z);
    }

    // --- SAVE POINT ---

    // Save mesh with previously created attribute
    write_by_extension("catorus_manhattan_point_attr.geogram", m, {{"pa", pa}});

    // --- FACET ATTR ---

    // Create a facet attribute
    FacetAttribute<int> fa(m);

    // For all facets in mesh, associate a random int value between [0-99]
    for (auto f : m.iter_facets())
        fa[f] = rand() % 100;

    // --- SAVE FACET ---

    // Save mesh with previously created attribute
    write_by_extension("catorus_facet_attr.geogram", m, {{"fa", fa}});

    // --- CORNER ATTR ---

    CornerAttribute<vec2> ca(m);

    for (auto &h : m.iter_halfedges())
        ca[h] = vec2(h.from().pos().x, h.from().pos().y);

    write_by_extension("catorus_corner_attr.geogram", m, {{"ca", ca}});

    // --- END CORNER ATTR ---

    // --- EDGE ATTR ---

    // Create a edge attribute
    EdgeAttribute<int> edge_id_attr(p); 
    // For all edge in polyline set edge attribute with edge id
    for (auto &e : p.iter_edges())
        edge_id_attr[e] = e;

    write_by_extension("pyramid_attr.geogram", p, {{"edge_id", edge_id_attr}});

    // --- END EDGE ATTR ---

    // --- SAVE ALL ATTRIBUTES ---

    // Save mesh with all previously created attributes
    write_by_extension("catorus_attr.geogram", m, {{"pa", pa}, {"fa", fa}, {"ca", ca}});

    // --- READ ATTRIBUTES ---

    // Load mesh and read attributes
    Triangles m2;
    SurfaceAttributes attributes = read_by_extension("catorus_attr.geogram", m2);
    // Load "pa" attribute
    PointAttribute<double> pa2("pa", attributes, m2);
    // Load "fa" attribute
    FacetAttribute<int> fa2("fa", attributes, m2);
    // Load "ca" attribute
    CornerAttribute<vec2> ca2("ca", attributes, m2);

    std::cout 
        << "PointAttribute size: " << pa2.ptr.get()->data.size() 
        << ", FacetAttribute size: " << fa2.ptr.get()->data.size() 
        << ", CornerAttribute size: " << ca2.ptr.get()->data.size()
        << std::endl;

    // --- END READ ATTRIBUTES ---

    // --- BIND ATTRIBUTES ---

    // Comment below and uncomment next line to see different behavior
    const std::string bind_attr = "pa";
    // const std::string bind_attr = "unkown_attribute";

    // Create a new point attribute
    PointAttribute<double> pa3;

    // Bind to the mesh, if bind return true, the attribute already exists: pa3 is fill with 'pa' data
    // if bind return false, the attribute does not exist: pa3 is added to the mesh and is fill with default value
    if (pa3.bind(bind_attr, attributes, m2)) {
        std::cout 
            << "Point attribute 'pa' exists and is bound successfully." 
            << std::endl;
    } else {
        std::cout 
            << "Point attribute 'pa' does not exist and was added successfully." 
            << std::endl;
    }

    // Display attribute values
    for (int i = 0; i < 10; i++) {
        std::cout << pa3[m.vertex(i)] << " ";
    }
    std::cout << "..." << std::endl;


    // --- END BIND ATTRIBUTES ---

    return 0;
}