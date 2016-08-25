/**
 * fast_input_master.h
 *
 * Contains headers for the FastInputMaster class. This Master object takes an
 * input stream of matrices and checks all extensions of those matrices. Any
 * minimally mutation infinite matrices found in this way are then output to
 * stdout.
 */
#pragma once

#include "fast_master.h"

#include <unordered_set>

#include "qv/stream_extension_iterator.h"
#include "qv/equiv_quiver_matrix.h"

namespace qvmmi {
	class FastInputMaster : public
			FastMaster<cluster::StreamExtIterator<cluster::QuiverMatrix>, cluster::QuiverMatrix> {
		private:
			typedef cluster::StreamExtIterator<cluster::QuiverMatrix> Iter;

		public:
			FastInputMaster(std::istream& input);
	};
}

