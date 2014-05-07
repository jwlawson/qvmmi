/*
 * fast_mmi_master.cc
 */
#include "fast_mmi_master.h"

namespace qvmmi {
	FastMMIMaster::FastMMIMaster(const Matrix& mat) :
		iter_(mat) {}

	void FastMMIMaster::run() {
		/* 
		 * Keep track of how many tasks were originally submitted. It oculd happen
		 * that fewer tasks are generated and sent than there are cores, so don't
		 * want to be waiting for tasks to return which were never submitted.
		 */
		int submitted = 0;
		/* Send initial matrices to workers. */
		for(int i = 1; i < num_proc_ && iter_.has_next(); ++i) {
			Matrix matrix = iter_.next();
			send_matrix(matrix, i);
			map_[i] = matrix;
			submitted++;
		}

		while(iter_.has_next()) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
			Matrix matrix = iter_.next();
			send_matrix(matrix, worker);
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

	void FastMMIMaster::handle_result(int result, int worker) {
		if(result == 1) {
			/* Matrix is mmi. */
			Matrix mat = map_[worker];
			std::cout << mat << std::endl;
		}
	}

}

