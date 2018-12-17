/*
 * main.cc
 */
#include "fast_input_master.h"
#include "fast_mmi_master.h"
#include "fast_mmi_slave.h"
#include "slow_check_master.h"
#include "sure_finite_slave.h"

#include <unistd.h>
#include <fstream>
#include <string>

#include "qv/dynkin.h"
#include "qv/quiver_matrix.h"

#include "mpi_tags.h"

void
usage() {
  std::cout << "qvmmi [-sf] [-d diagram | -m matrix | -i input ]" << std::endl;
}

bool
valid_dynkin(std::string matrix) {
  return cluster::dynkin::MAP.count(matrix) != 0;
}

QuiverMatrix
get_matrix(bool dynkin, std::string matrix) {
  if (dynkin) {
    return cluster::dynkin::MAP.at(matrix);
  }
  return QuiverMatrix(matrix);
}

int
main(int argc, char* argv[]) {
  MPI::Init(argc, argv);
  int rank = MPI::COMM_WORLD.Get_rank();

  int opt;
  bool slow = false;
  bool fast = false;
  bool dynkin = false;
  std::string matrix;
  std::string input;

  while ((opt = getopt(argc, argv, "fsd:m:i:")) != -1) {
    switch (opt) {
      case 'f':
        fast = true;
        break;
      case 's':
        slow = true;
        break;
      case 'd':
        matrix = optarg;
        dynkin = true;
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

  if (slow) {
    if (rank == MASTER) {
      if (input.empty()) {
        qvmmi::SlowCheckMaster master;
        master.run();
      } else {
        std::ifstream file;
        file.open(input);
        if (!file.is_open()) {
          std::cerr << "Error opening input file " << input << std::endl;
          MPI::Finalize();
          return 1;
        }
        qvmmi::SlowCheckMaster master(file);
        master.run();
        file.close();
      }
    } else {
      qvmmi::SureFiniteSlave slave;
      slave.run();
    }

  } else if (fast) {
    if (rank == MASTER) {
      if (!input.empty()) {
        std::ifstream file;
        file.open(input);
        if (!file.is_open()) {
          std::cout << "Error opening input file " << input << std::endl;
          MPI::Finalize();
          return 1;
        }
        qvmmi::FastInputMaster master(file);
        master.run();
        file.close();
      } else if (dynkin && !valid_dynkin(matrix)) {
        std::cerr << "Invalid matrix" << std::endl;
        MPI::Finalize();
        return 1;
      } else {
        QuiverMatrix mat = get_matrix(dynkin, matrix);
        qvmmi::FastMMIMaster m(mat);
        m.run();
      }
    } else {
      qvmmi::FastMMISlave s;
      s.run();
    }
  } else if (rank == MASTER) {
    /* Only want this printed once. */
    usage();
    std::cout << "Specify an option" << std::endl;
  }

  MPI::Finalize();
  return 0;
}
