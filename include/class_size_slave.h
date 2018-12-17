/*
 * class_size_slave.h
 */
#pragma once
#include "slave.h"

namespace qvmmi {
class ClassSizeSlave : public Slave<int> {
 protected:
  virtual int calc_result();
};
}  // namespace qvmmi
