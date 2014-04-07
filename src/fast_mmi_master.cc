/*
 * fast_mmi_master.cc
 */

#include "fast_mmi_master.h"
#include "class_ext_iterator.h"
#include "codec.h"
#include "mpi_tags.h"

using cluster::QuiverMatrix;
using cluster::ExtensionIterator;
using cluster::EquivMutationClass;
using cluster::EquivMutClassExtIterator;

namespace qvmmi {
	FastMMIMaster::FastMMIMaster(const QuiverMatrix& mat) :
		matrix_(mat), status_(), map_() {}

	void FastMMIMaster::run() {
		int number = MPI::COMM_WORLD.Get_size();
		
		EquivMutClassExtIterator iter(matrix_);

		/* Send initial matrices to workers. */
		for(int i = 1; i < number; ++i) {
			send_matrix(iter.next(), i);
		}
		int result;
		while(iter.has_next()) {
			MPI::COMM_WORLD.Recv(&result, 1, MPI::INT, MPI::ANY_SOURCE, RESULT_TAG,
					status_);
			int worker = status_.Get_source();
			if(result == 1) {
				/* Matrix is mmi. */
				QuiverMatrix mat = map_[worker];
				std::cout << mat << std::endl;
			}
			send_matrix(iter.next(), worker);
		}
		/* Wait for remaining tasks. */
		for(int i = 1; i < number; ++i) {
			MPI::COMM_WORLD.Recv(&result, 1, MPI::INT, MPI::ANY_SOURCE, RESULT_TAG,
					status_);
			int worker = status_.Get_source();
			if(result == 1) {
				/* Matrix is mmi. */
				QuiverMatrix mat = map_[worker];
				std::cout << mat << std::endl;
			}
		}
		send_shutdown(number);
	}

	void FastMMIMaster::send_matrix(const QuiverMatrix& matrix, int worker) {
		int size = matrix.num_rows() * matrix.num_cols() + 2;
		MPI::COMM_WORLD.Send(&size, 1, MPI::INT, worker, SIZE_TAG);
		MPI::COMM_WORLD.Recv(NULL, 0, MPI::BYTE, worker, OK_TAG);
		int* arr = codec_.encode(matrix);
		MPI::COMM_WORLD.Send(arr, size, MPI::INT, worker, MATRIX_TAG);
		delete [] arr;
		
		map_[worker] = matrix;
	}

	void FastMMIMaster::send_shutdown(int number) {
		for(int i = 1; i < number; ++i) {
			MPI::COMM_WORLD.Send(NULL, 0, MPI::BYTE, i, END_TAG);
		}
	}

}

