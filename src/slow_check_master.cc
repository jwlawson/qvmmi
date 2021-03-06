/*
 * slow_check_master.cc
 */
#include "slow_check_master.h"

#include <algorithm>
#include <string>

#include "qv/submatrix_iterator.h"

namespace qvmmi {

	SlowCheckMaster::SlowCheckMaster(std::istream& input)
		: Master(), running_(), map_(), iter_(input){}

	void SlowCheckMaster::run() {
		/* 
		 * Keep track of how many tasks were originally submitted. It oculd happen
		 * that fewer tasks are generated and sent than there are cores, so don't
		 * want to be waiting for tasks to return which were never submitted.
		 */
		int submitted = 1;
		/* Send initial matrices to workers. */
		for(int i = 1; i < num_proc_ && iter_.has_next(); ++i) {
			iter_.next_info(running_[i]);
			send_matrix(*(running_[i].submatrix), i);
			submitted++;
		}

		while(iter_.has_next()) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
			iter_.next_info(running_[worker]);
			send_matrix(*running_[worker].submatrix, worker);
		}
		/* Wait for remaining tasks. */
		for(int i = 1; i < submitted; ++i) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
		}
		send_shutdown();
		std::cout.flush();
	}

	void SlowCheckMaster::handle_result(int result, int worker) {
		MMITracker& track = get_tracker(running_[worker].matrix);
		if(result > 0) {
			/* Submatrix is finite. */
			track.finite_sub[running_[worker].removed] = kFinite;
		} else {
			/* Submatrix is infinite. */
			track.infinite = true;
			track.finite_sub[running_[worker].removed] = kInfinite;
		}
		handle_tracker(track);
	}

	SlowCheckMaster::MMITracker& SlowCheckMaster::get_tracker(
			const MatrixPtr& matrix) {
		if(map_.count(matrix) == 0) {
			map_[matrix].finite_sub = std::vector<int>(matrix->num_rows(), kUnset);
			map_[matrix].infinite = false;
			map_[matrix].matrix = matrix;
		}
		return map_[matrix];
	}

	void SlowCheckMaster::handle_tracker(const MMITracker& tracker) {
		bool mmi = true;
		if(tracker.infinite) {
			mmi = false;
		}
		bool complete = true;
		for(std::size_t i = 0; i < tracker.finite_sub.size(); ++i) {
			if(tracker.finite_sub[i] == kUnset) {
				complete = false;
			} else if(tracker.finite_sub[i] == kInfinite) {
				mmi = false;
			}
		}
		if(complete) {
			if(mmi) {
				std::cout << *(tracker.matrix) << std::cout.widen('\n');
			} else {
				std::cerr << "False: " << *(tracker.matrix) << std::endl;
			}
			map_.erase(tracker.matrix);
		}
	}
	const int SlowCheckMaster::kFinite = 1;
	const int SlowCheckMaster::kInfinite = 0;
	const int SlowCheckMaster::kUnset = -1; 
}

