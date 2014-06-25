/**
 * sure_finite_slave.cc
 */
#include "sure_finite_slave.h"

namespace qvmmi {

	void SureFiniteSlave::add_finite(const std::shared_ptr<cluster::EquivQuiverMatrix>& mat) {
		chk_.add_finite(mat);
	}

	int SureFiniteSlave::calc_result() {
		return chk_.is_finite(matrix_);
	}
}

