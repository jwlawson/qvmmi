/*
 * fast_mmi_slave.h
 *
 * FastMMISlave class computes whether a matrix is MMI or not. The method
 * calc_result returns a value from one of -1, 0 or 1 as follows:
 *
 * 	-1 = Matrix is probably mutation-finite
 * 	 0 = Matrix is mutation-infinite but not minimally
 * 	 1 = Matrix is minimally mutation-infinite
 *
 * The slave waits for matrices to be communicated by MPI and once it has
 * computed whether the matrix is MMI or not sends the result back to the master
 * node.
 */
#pragma once
#include "slave.h"

using cluster::QuiverMatrix;

namespace qvmmi {
class FastMMISlave : public Slave<int> {
 protected:
  virtual int calc_result();

 private:
  int mmi(Matrix& mat);
};
}  // namespace qvmmi
