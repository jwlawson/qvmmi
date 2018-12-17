/*
 * master.cc
 */
#include "master.h"

#include "mpi_tags.h"

namespace qvmmi {

Master::Master() { num_proc_ = MPI::COMM_WORLD.Get_size(); }

void
Master::send_matrix(const QuiverMatrix& matrix, int worker) {
  int size = matrix.num_rows() * matrix.num_cols() + 2;
  MPI::COMM_WORLD.Send(&size, 1, MPI::INT, worker, SIZE_TAG);
  MPI::COMM_WORLD.Recv(NULL, 0, MPI::BYTE, worker, OK_TAG);
  int* arr = codec_.encode(matrix);
  MPI::COMM_WORLD.Send(arr, size, MPI::INT, worker, MATRIX_TAG);
}

int
Master::receive_result() {
  int result;
  MPI::COMM_WORLD.Recv(&result, 1, MPI::INT, MPI::ANY_SOURCE, RESULT_TAG,
                       status_);
  return result;
}

void
Master::send_shutdown() {
  int number = MPI::COMM_WORLD.Get_size();
  for (int i = 1; i < number; ++i) {
    MPI::COMM_WORLD.Send(NULL, 0, MPI::BYTE, i, END_TAG);
  }
}
}  // namespace qvmmi
