/*
 * fast_mmi_master.cc
 */
#include "fast_mmi_master.h"

#include "class_ext_iterator.h"
#include "codec.h"

namespace qvmmi {
	FastMMIMaster::FastMMIMaster(const QuiverMatrix& mat) :
		matrix_(mat) {}

	void FastMMIMaster::run() {
		using cluster::EquivMutClassExtIterator;
		EquivMutClassExtIterator iter(matrix_);

		/* Send initial matrices to workers. */
		for(int i = 1; i < num_proc_; ++i) {
			QuiverMatrix matrix = iter.next();
			send_matrix(matrix, i);
			map_[i] = matrix;
		}

		while(iter.has_next()) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
			QuiverMatrix matrix = iter.next();
			send_matrix(matrix, worker);
			map_[worker] = matrix;
		}
		/* Wait for remaining tasks. */
		for(int i = 1; i < num_proc_; ++i) {
			int result = receive_result();
			int worker = status_.Get_source();
			handle_result(result, worker);
		}
		send_shutdown();
	}

	void FastMMIMaster::handle_result(int result, int worker) {
		if(result == 1) {
			/* Matrix is mmi. */
			QuiverMatrix mat = map_[worker];
			std::cout << mat << std::endl;
		}
	}

}

