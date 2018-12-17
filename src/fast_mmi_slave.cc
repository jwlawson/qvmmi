/*
 * fast_mmi_slave.cc
 */
#include "fast_mmi_slave.h"

#include "qv/fast_infinite.h"
#include "qv/submatrix_iterator.h"

namespace qvmmi {

int
FastMMISlave::calc_result() {
  return mmi(matrix_);
}

int
FastMMISlave::mmi(Matrix& matrix) {
  if (!cluster::fastinf::is_infinite(matrix)) {
    return -1;
  }
  cluster::SubmatrixIterator<QuiverMatrix> iter(matrix);
  while (iter.has_next()) {
    Matrix const& n = iter.next();
    if (cluster::fastinf::is_infinite(n)) {
      return 0;
    }
  }
  return 1;
}

}  // namespace qvmmi
