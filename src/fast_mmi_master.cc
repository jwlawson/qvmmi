/*
 * fast_mmi_master.cc
 */
#include "fast_mmi_master.h"

namespace qvmmi {
	FastMMIMaster::FastMMIMaster(const cluster::QuiverMatrix& mat)
		: FastMaster<Iterator, cluster::QuiverMatrix>() {
		iter_ = Iterator(mat);
	}

}

