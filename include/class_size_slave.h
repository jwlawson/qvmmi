/*
 * class_size_slave.h
 */

#include "slave.h"

namespace qvmmi {
	class ClassSizeSlave : public Slave<int> {

		protected:
			virtual int calc_result();

	};
}

