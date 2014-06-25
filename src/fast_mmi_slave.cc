/*
 * fast_mmi_slave.cc
 */
#include "fast_mmi_slave.h"

#include "qv/mmi.h"

namespace qvmmi {

	void FastMMISlave::add_finite(const std::shared_ptr<cluster::EquivQuiverMatrix>& mat) {
		using cluster::mmi::add_finite;
		add_finite(mat);
	}

	bool FastMMISlave::calc_result() {
		using cluster::mmi::fast_mmi;
		return fast_mmi(matrix_);
	}

}

