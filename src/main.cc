/*
 * main.cc
 */

#include "fast_mmi_slave.h"
#include "fast_mmi_master.h"
#include "quiver_matrix.h"
#include "mpi_tags.h"
#include "dynkin.h"
#include <string>

int main(int argc, char* argv[]) {

	MPI::Init(argc, argv);
	int rank = MPI::COMM_WORLD.Get_rank();

	std::string str = argv[1];
	try{
		cluster::dynkin::MAP.at(str);
	} catch(std::logic_error e) {
		MPI::Finalize();
		return 1;
	}

	QuiverMatrix mat = cluster::dynkin::MAP.at(str);
	if(rank == MASTER) {
		qvmmi::FastMMIMaster m(mat);
		m.run();

	} else {
		qvmmi::FastMMISlave s;
		s.run();

	}

	MPI::Finalize();
	return 0;
}

		
