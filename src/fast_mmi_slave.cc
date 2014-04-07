/*
 * fast_mmi_slave.cc
 */

#include "mmi.h"
#include "fast_mmi_slave.h"
#include "mpi_tags.h"
#include "codec.h"

using cluster::QuiverMatrix;
using cluster::mmi::fast_mmi;

namespace qvmmi {

	FastMMISlave::FastMMISlave() : matrix_(), status_() {}

	void FastMMISlave::run() {
		while(receive(matrix_)) {
			bool mmi = fast_mmi(matrix_);
			send_result(mmi);
		}
	}

	bool FastMMISlave::receive(QuiverMatrix& matrix) {
		int size;
		MPI::COMM_WORLD.Recv(&size, 1, MPI::INT, MASTER, MPI::ANY_TAG, status_);
		if(status_.Get_tag() == END_TAG) {
			return false;
		}
		MPI::COMM_WORLD.Send(NULL, 0, MPI::BYTE, MASTER, OK_TAG);
		int* arr = new int[size];
		MPI::COMM_WORLD.Recv(arr, size, MPI::INT, MASTER, MATRIX_TAG);
	
		matrix.set(codec_.decode(arr, size));
		delete [] arr;

		return true;
	}

	void FastMMISlave::send_result(bool mmi) {
		int result = static_cast<int>(mmi);
		MPI::COMM_WORLD.Send(&result, 1, MPI::INT, MASTER, RESULT_TAG);
	}

}


