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
	template<class T>
	class FastMaster : Master {
		protected:
			typedef cluster::EquivQuiverMatrix Matrix;
			typedef std::shared_ptr<Matrix> MatrixPtr;

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
			std::map<int, MatrixPtr> map_;
			/** Pointer to the next matrix to check. */
			MatrixPtr next_;
			/** True if there is another matrix to check. */
			bool has_next_;

			/**
			 * Get the next matrix from the iterator.
			 * @return Next matrix to check
			 */
			MatrixPtr next();
	};
}

