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

#include "qv/equiv_quiver_matrix.h"

namespace qvmmi {
	template<class T, class Matrix>
	class FastMaster : Master {

		public:
			FastMaster();
			/**
			 * For each matrix in the iterator, see which are minimally mutation
			 * infinite.
			 *
			 * Each MMI matrix is printed to stdout.
			 */
			virtual void run();

		protected:
			/** Iterator containing the matrices to check. */
			T iter_;
			/**
			 * Handle the result provided by the specifed worker.
			 * @param result Result returned by the worker
			 * @param worker Id of the worker node
			 */
			virtual void handle_result(int result, int worker);

		private:
			/**
			 * Map from worker node id to the matrix currently being checked by that
			 * worker.
			 */
			std::map<int, Matrix> map_;
	};
}

