/*
 * slave.cc
 */
#include "slave.h"

#include "qv/mmi.h"

#include "codec.h"
#include "mpi_tags.h"

namespace qvmmi {

template <class T>
void
Slave<T>::run() {
  while (receive()) {
    T result = calc_result();
    send_result(result);
  }
}

template <class T>
bool
Slave<T>::receive() {
  int size;
  MPI::COMM_WORLD.Recv(&size, 1, MPI::INT, MASTER, MPI::ANY_TAG, status_);
  if (status_.Get_tag() == END_TAG) {
    return false;
  }
  MPI::COMM_WORLD.Send(NULL, 0, MPI::BYTE, MASTER, OK_TAG);
  array_cache_.reserve(size);
  int* arr = array_cache_.data();
  MPI::COMM_WORLD.Recv(arr, size, MPI::INT, MASTER, MATRIX_TAG);

  codec_.decode_into(arr, matrix_);
  return true;
}

template <class T>
void
Slave<T>::send_result(const T& res) {
  int result = static_cast<int>(res);
  MPI::COMM_WORLD.Send(&result, 1, MPI::INT, MASTER, RESULT_TAG);
}

template class Slave<bool>;
template class Slave<int>;
}  // namespace qvmmi
