/**
 * fast_input_master.cc
 */
#include "fast_master.h"

#include "qv/class_ext_iterator.h"
#include "qv/stream_extension_iterator.h"

namespace qvmmi {

	template<class T, class M>
	FastMaster<T, M>::FastMaster()
		:	Master(),
			map_() {}

	template<class T, class M>
	void FastMaster<T, M>::run() {
		/* 
		 * Keep track of how many tasks were originally submitted. It oculd happen
		 * that fewer tasks are generated and sent than there are cores, so don't
		 * want to be waiting for tasks to return which were never submitted.
		 */
		int submitted = 1;
		/* Send initial matrices to workers. */
		for(int i = 1; i < num_proc_ && iter_.has_next(); ++i) {
			M const& matrix = iter_.next();
			send_matrix(matrix, i);
			map_[i].set_matrix(matrix);
			submitted++;
		}

		while(iter_.has_next()) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
			M const& matrix = iter_.next();
			send_matrix(matrix, worker);
			map_[worker].set_matrix(matrix);
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

	template<class T, class M>
	void FastMaster<T, M>::handle_result(int result, int worker) {
		if(result == 1) {
			/* Matrix is mmi. */
			M const& mat = map_[worker];
			std::cout << mat << std::cout.widen('\n');
		} else if (result == -1) {
			/* Matrix needs to be checked if finite. */
			M const& mat = map_[worker];
			std::cout << "Finite: " << mat << std::cout.widen('\n');
		}
	}

	template class FastMaster<cluster::StreamExtIterator<cluster::QuiverMatrix>, cluster::QuiverMatrix>;
	template class FastMaster<cluster::EquivMutClassExtIterator, cluster::QuiverMatrix>;

}

