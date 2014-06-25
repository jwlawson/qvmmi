/**
 * fast_master.h
 *
 * Contains headers for the FastMaster abstract class. This Master object takes an
 * iterator of matrices and checks all extensions of those matrices. Any
 * minimally mutation infinite matrices found in this way are then output to
 * stdout.
 */
#pragma once

#include "master.h"

#include <unordered_set>

#include "qv/stream_extension_iterator.h"
#include "qv/equiv_quiver_matrix.h"

namespace qvmmi {
	template<class T>
	class FastMaster : Master {
		protected:
			typedef cluster::EquivQuiverMatrix Matrix;
			typedef std::shared_ptr<Matrix> MatrixPtr;

		public:
			virtual void run();

		protected:
			T iter_;
			virtual void handle_result(int result, int worker);

		private:
			std::map<int, MatrixPtr> map_;
			std::unordered_set<MatrixPtr> set_;

			MatrixPtr next();
	};
}

