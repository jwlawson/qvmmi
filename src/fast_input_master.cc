/**
 * fast_input_master.cc
 */
#include "fast_input_master.h"

namespace qvmmi {

	FastInputMaster::FastInputMaster(std::istream& input)
		: iter_(input),
			map_() {
		iter_.progress(true);
	}

	void FastInputMaster::run() {
		/* 
		 * Keep track of how many tasks were originally submitted. It oculd happen
		 * that fewer tasks are generated and sent than there are cores, so don't
		 * want to be waiting for tasks to return which were never submitted.
		 */
		int submitted = 1;
		/* Send initial matrices to workers. */
		for(int i = 1; i < num_proc_ && iter_.has_next(); ++i) {
			MatrixPtr matrix = iter_.next();
			send_matrix(*matrix, i);
			map_[i] = matrix;
			submitted++;
		}

		while(iter_.has_next()) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
			MatrixPtr matrix = iter_.next();
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

	void FastInputMaster::handle_result(int result, int worker) {
		if(result == 1) {
			/* Matrix is mmi. */
			MatrixPtr mat = map_[worker];
			std::cout << *mat << std::endl;
		}
	}
}

