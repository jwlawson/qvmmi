/**
 * fast_input_master.cc
 */
#include "fast_master.h"

#include "qv/class_ext_iterator.h"
#include "qv/stream_extension_iterator.h"

namespace qvmmi {

	template<class T>
	FastMaster<T>::FastMaster()
		:	Master(),
			map_(),
			set_(),
			next_(),
			has_next_(true) {}

	template<class T>
	void FastMaster<T>::run() {
		/*
		 * The first call to next() will return an empty shared_ptr, so call now to
		 * ensure that all subsequent calls are valid.
		 */
		next();
		/* 
		 * Keep track of how many tasks were originally submitted. It oculd happen
		 * that fewer tasks are generated and sent than there are cores, so don't
		 * want to be waiting for tasks to return which were never submitted.
		 */
		int submitted = 1;
		/* Send initial matrices to workers. */
		for(int i = 1; i < num_proc_ && has_next_; ++i) {
			MatrixPtr matrix = next();
			send_matrix(*matrix, i);
			map_[i] = matrix;
			submitted++;
		}

		while(has_next_) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
			MatrixPtr matrix = next();
			send_matrix(*matrix, worker);
			map_[worker] = matrix;
		}
		/* Wait for remaining tasks. */
		for(int i = 1; i < submitted; ++i) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
		}
		send_shutdown();
	}

	template<class T>
	void FastMaster<T>::handle_result(int result, int worker) {
		if(result == 1) {
			/* Matrix is mmi. */
			MatrixPtr mat = map_[worker];
			std::cout << *mat << std::endl;
		}
	}

	template<class T>
	void FastMaster<T>::add_exception(const MatrixPtr& mat) {
		set_.insert(mat);
	}

	/**
	 * The next matrix should be stored in next_
	 * Compute the one after that in matrix, return next_
	 * then finally set matrix_ to be matrix
	 */
	template<class T>
	typename FastMaster<T>::MatrixPtr FastMaster<T>::next() {
		MatrixPtr matrix;
		do {
			if(!iter_.has_next()) {
				has_next_ = false;
				return std::move(next_);
			}
			matrix = iter_.next();
		} while(!set_.insert(matrix).second);
		std::swap(matrix, next_);
		return std::move(matrix);
	}

	template class FastMaster<cluster::StreamExtIterator<cluster::EquivQuiverMatrix>>;
	template class FastMaster<cluster::EquivMutClassExtIterator>;

}

