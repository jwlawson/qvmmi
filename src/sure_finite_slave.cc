/**
 * sure_finite_slave.cc
 */
#include "sure_finite_slave.h"

namespace qvmmi {

	int SureFiniteSlave::calc_result() {
		return chk_.is_finite(matrix_);
	}
}

