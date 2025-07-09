/**
 * This example shows how to use the solver
*/
#include <ultimaille/all.h>


using namespace UM;

int main() {
	
	// Set the input and output directories
	const std::string input_dir = ASSETS_INPUT_DIR;
	const std::string output_dir = OUTPUT_DIR;

	// Load mesh from file
	Triangles m;
	read_by_extension(input_dir + "catorus.geogram", m);
	m.connect();

	// Declare solver, set number of variables
	// Each vertex has 3 coordinates (x, y, z)
	// So we have m.nverts() * 3 variables
	LeastSquares solver(m.nverts() * 3);
	
	// Select some vertices to fix
	// I choose ears, muzzle and legs
	// These vertices are fixed in the original mesh
	// and we want to keep them in the same position
	int fix_vert[] = {1249, 2378, 485, 4095, 4034};
	for (auto vi : fix_vert) {
		vec3 v = m.vertex(vi);
		for (int dim = 0; dim < 3; dim++)
			solver.fix(vi * 3 + dim, v[dim]);
	}

	for (auto &v : m.iter_vertices()) {

		for (int dim = 0; dim < 3; dim++) {
			LinExpr lexpr;

			// For each vertex, we want to average the positions of its neighbors
			int n = 0;
			for (auto &h : v.iter_halfedges()) {
				auto neighbor = h.to();
				lexpr += Linear::X(neighbor * 3 + dim);
				n++;
			}

			lexpr *= (1.0 / n);

			// We want to minimize the distance between the vertex and the average of its neighbors
			solver.add_to_energy(Linear::X(v * 3 + dim) - lexpr);
		}
	}

	// Solve
	solver.solve();

	// Update vertex positions with the solution
	for (auto &v : m.iter_vertices()) {
		double x = solver.value(v * 3);
		double y = solver.value(v * 3 + 1);
		double z = solver.value(v * 3 + 2);
		v.pos() = {x, y, z};
	}

	// Save the mesh
	write_by_extension(output_dir + "catorus_solved.geogram", m);

	return 0;
}