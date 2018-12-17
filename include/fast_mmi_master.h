/*
 * fast_mmi_master.h
 */
#pragma once
#include "fast_master.h"

#include <map>

#include "qv/class_ext_iterator.h"

namespace qvmmi {
class FastMMIMaster : public FastMaster<cluster::EquivMutClassExtIterator,
                                        cluster::QuiverMatrix> {
 private:
  typedef cluster::EquivMutClassExtIterator Iterator;

 public:
  FastMMIMaster(const cluster::QuiverMatrix& mat);
};
}  // namespace qvmmi
