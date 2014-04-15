/*
 * fast_mmi_slave.h
 */

#include "slave.h"

using cluster::QuiverMatrix;

namespace qvmmi {
	class FastMMISlave : public Slave<bool> {

		protected:
			virtual bool calc_result();

	};
}

