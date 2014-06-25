/**
 * fast_input_master.cc
 */
#include "fast_input_master.h"

namespace qvmmi {

	FastInputMaster::FastInputMaster(std::istream& input)
		: FastMaster<Iter>() {
		iter_ = Iter(input);
		iter_.progress(true);
	}

}

