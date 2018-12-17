/**
 * fast_input_master.cc
 */
#include "fast_input_master.h"

namespace qvmmi {

FastInputMaster::FastInputMaster(std::istream& input)
    : FastMaster<Iter, cluster::QuiverMatrix>() {
  iter_ = Iter(input);
}

}  // namespace qvmmi
