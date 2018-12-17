/*
 * slow_check_master.h
 */
#pragma once
#include "master.h"

#include <istream>
#include <map>
#include <unordered_map>

#include "qv/stream_submatrix_iterator.h"

namespace qvmmi {
class SlowCheckMaster : Master {
 public:
  SlowCheckMaster(std::istream& input = std::cin);
  virtual void run();

 protected:
  virtual void handle_result(int result, int worker);

 private:
  static const int kFinite;
  static const int kInfinite;
  static const int kUnset;

  typedef std::shared_ptr<QuiverMatrix> MatrixPtr;
  typedef cluster::StreamSubIter<QuiverMatrix> Iter;

  struct MMITracker {
    MatrixPtr matrix;
    bool infinite;
    std::vector<int> finite_sub;
  };

  std::map<int, Iter::MatrixSub> running_;
  std::unordered_map<MatrixPtr, MMITracker> map_;
  Iter iter_;

  MMITracker& get_tracker(const MatrixPtr& matrix);
  void handle_tracker(const MMITracker& tracker);
};
}  // namespace qvmmi
