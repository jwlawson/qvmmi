/*
 * fast_mmi_slave.cc
 */

#include "fast_mmi_slave.h"
#include "mmi.h"


namespace qvmmi {

	using cluster::QuiverMatrix;
	using cluster::mmi::fast_mmi;

	bool FastMMISlave::calc_result() {
			return fast_mmi(matrix_);
	}

}

