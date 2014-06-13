/*
 * fast_mmi_slave.cc
 */
#include "fast_mmi_slave.h"

#include "qv/mmi.h"

namespace qvmmi {

	bool FastMMISlave::calc_result() {
		using cluster::mmi::fast_mmi;
		return fast_mmi(matrix_);
	}

}

