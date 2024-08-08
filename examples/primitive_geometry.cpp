/**
 * This example shows how to work with geometry of primitives (like facets, cells)
*/
#include <ultimaille/all.h>


using namespace UM;

int main() {

	// --- CREATE QUADS ---

	{
		// Init a Quad mesh
		Quads m;

		// Create and place 8 points
		m.points.create_points(4);
		m.points[0] = vec3(0, 0, 0);
		m.points[1] = vec3(1, 0, 0);
		m.points[2] = vec3(1, 1, 0);
		m.points[3] = vec3(0, 1, 0);

		m.create_facets(1);

		m.vert(0, 0) = 0;
		m.vert(0, 1) = 1;
		m.vert(0, 2) = 2;
		m.vert(0, 3) = 3;

		// --- GET QUAD3 ---

		// Get facet at index 0
		auto f = Quads::Facet(m, 0);
		// Extract quad geometry from facet f
		auto quad_geo = f.geom<Quad3>();
		// Now, we could compute some info from geometry
		auto n = quad_geo.normal(); // Get normal of quad
		auto b = quad_geo.bary_verts(); // Get barycenter of quad
		auto a = quad_geo.unsigned_area(); // Get area of quad
		auto quad2_geo = quad_geo.xy(); // Get 2D quad from 3D (no projection, just truncate z)

		// Display
		std::cout 
			<< "Quad facet geometry is defined by: [" 
			<< quad_geo.v[0] << ", " 
			<< quad_geo.v[1] << ", " 
			<< quad_geo.v[2] << ", " 
			<< quad_geo.v[3] << "]" 
			<< std::endl;

		std::cout << " - normal: " << n << std::endl;
		std::cout << " - barycenter: " << b << std::endl;
		std::cout << " - area: " << a << std::endl;

		std::cout 
			<< " - corresponding 2D Quad facet geometry is defined by: [" 
			<< quad2_geo.v[0] << ", " 
			<< quad2_geo.v[1] << ", " 
			<< quad2_geo.v[2] << ", " 
			<< quad2_geo.v[3] << "]" 
			<< std::endl;
	}

	{
		// Init a Tri mesh
		Triangles m;

		// Create and place 8 points
		m.points.create_points(3);
		m.points[0] = vec3(0, 0, 0);
		m.points[1] = vec3(1, 0, 0);
		m.points[2] = vec3(1, 1, 0);

		m.create_facets(1);

		m.vert(0, 0) = 0;
		m.vert(0, 1) = 1;
		m.vert(0, 2) = 2;

		// --- GET TRI3 ---

		// Get facet at index 0
		auto f = Triangles::Facet(m, 0);
		// Extract tri geometry from facet f
		auto tri_geo = f.geom<Triangle3>();
		// Now, we could compute some info from geometry
		auto n = tri_geo.normal(); // Get normal of quad
		auto b = tri_geo.bary_verts(); // Get barycenter of quad
		auto a = tri_geo.unsigned_area(); // Get area of quad
		// and many other functions...
		auto tri2_geo = tri_geo.xy(); // Get 2D quad from 3D (no projection, just truncate z)

		// Display
		std::cout 
			<< "Tri facet geometry is defined by: [" 
			<< tri_geo.v[0] << ", " 
			<< tri_geo.v[1] << ", " 
			<< tri_geo.v[2] << "]" 
			<< std::endl;

		std::cout << " - normal: " << n << std::endl;
		std::cout << " - barycenter: " << b << std::endl;
		std::cout << " - area: " << a << std::endl;

		std::cout 
			<< " - corresponding 2D Tri facet geometry is defined by: [" 
			<< tri2_geo.v[0] << ", " 
			<< tri2_geo.v[1] << ", " 
			<< tri2_geo.v[2] << "]" 
			<< std::endl;
	}

	{
		// Init a Hex mesh
		Hexahedra m;
		m.points.create_points(8);
		m.points[0] = vec3(-0.5,-0.5,-0.5);
		m.points[1] = vec3(0.5,-0.5,-0.5);
		m.points[2] = vec3(-0.5,0.5,-0.5);
		m.points[3] = vec3(0.5,0.5,-0.5);
		m.points[4] = vec3(-0.5,-0.5,0.5);
		m.points[5] = vec3(0.5,-0.5,0.5);
		m.points[6] = vec3(-0.5,0.5,0.5);
		m.points[7] = vec3(0.5,0.5,0.5);

		// Create 1 cell
		m.create_cells(1);

		m.vert(0, 0) = 0;
		m.vert(0, 1) = 1;
		m.vert(0, 2) = 2;
		m.vert(0, 3) = 3;
		m.vert(0, 4) = 4;
		m.vert(0, 5) = 5;
		m.vert(0, 6) = 6;
		m.vert(0, 7) = 7;

		// --- GET HEXAHEDRON ---
		// Get cell at index 0
		auto c = Hexahedra::Cell(m, 0);
		// Extract tri geometry from facet f
		auto hex_geo = c.geom<Hexahedron>();
		// Now, we could compute some info from geometry
		auto b = hex_geo.bary_verts(); // Get barycenter of quad
		auto v = hex_geo.volume(); // Get volume
		auto j = hex_geo.scaled_jacobian(); // Get scaled jacobian quality metrics

		// Display
		std::cout 
			<< "Hex cell geometry is defined by: [" 
			<< hex_geo.v[0] << ", " 
			<< hex_geo.v[1] << ", " 
			<< hex_geo.v[2] << ", " 
			<< hex_geo.v[3] << ", " 
			<< hex_geo.v[4] << ", " 
			<< hex_geo.v[5] << ", " 
			<< hex_geo.v[6] << ", " 
			<< hex_geo.v[7] << "]" 
			<< std::endl;

		std::cout << " - barycenter: " << b << std::endl;
		std::cout << " - volume: " << v << std::endl;
		std::cout << " - scaled jacobian: " << j << std::endl;
	}

	// --- END ---

	return 0;
}