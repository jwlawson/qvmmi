/*
 * class_sixe_slave.cc
 */

#include "class_size_slave.h"
#include "qv/equiv_mutation_class_size.h"

namespace qvmmi {

int
ClassSizeSlave::calc_result() {
  using cluster::EquivQuiverMatrix;
  using cluster::equivsize::Size;
  EquivQuiverMatrix m(matrix_);
  return Size(m);
}

}  // namespace qvmmi
