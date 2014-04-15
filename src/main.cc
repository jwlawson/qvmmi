/*
 * main.cc
 */
#include <unistd.h>
#include <fstream>
#include <string>

#include "dynkin.h"
#include "fast_mmi_slave.h"
#include "fast_mmi_master.h"
#include "mpi_tags.h"
#include "quiver_matrix.h"

#include "class_size_slave.h"
#include "slow_check_master.h"

int main(int argc, char* argv[]) {

	MPI::Init(argc, argv);
	int rank = MPI::COMM_WORLD.Get_rank();

	int opt;
	bool slow = false;
	bool fast = false;
	std::string matrix;
	std::string input;
	while ((opt = getopt (argc, argv, "fsm:i:")) != -1){
		switch (opt) {
			case 'f':
				fast = true;
				break;
			case 's':
				slow = true;
				break;
			case 'm':
				matrix = optarg;
				break;
			case 'i':
				input = optarg;
				break;
			case '?':
				return 1;
			default:
				return 2;
		}
	}

	if(slow) {
		if(rank == MASTER) {
			if(input.empty()){
				qvmmi::SlowCheckMaster master;
				master.run();
			} else {
				std::ifstream file;
				file.open(input);
				if(!file.is_open()) {
					std::cout << "Error opening file "<< input << std::endl;
					MPI::Finalize();
					return 1;
				}
				qvmmi::SlowCheckMaster master(file);
				master.run();
				file.close();
			}
		} else {
			qvmmi::ClassSizeSlave slave;
			slave.run();
		}

	} else if(fast) {
		try{
			cluster::dynkin::MAP.at(matrix);
		} catch(std::logic_error e) {
			MPI::Finalize();
			return 1;
		}

		QuiverMatrix mat = cluster::dynkin::MAP.at(matrix);
		if(rank == MASTER) {
			qvmmi::FastMMIMaster m(mat);
			m.run();

		} else {
			qvmmi::FastMMISlave s;
			s.run();

		}
	} else {
		std::cout << "Specify an option" << std::endl;
	}



	MPI::Finalize();
	return 0;
}

		
