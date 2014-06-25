/*
 * fast_mmi_master.cc
 */
#include "fast_mmi_master.h"

namespace qvmmi {
	FastMMIMaster::FastMMIMaster(const Matrix& mat)
		: FastMaster<Iterator>() {
		iter_ = Iterator(mat);
	}

}

