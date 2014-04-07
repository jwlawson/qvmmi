/*
 * fast_mmi_slave.h
 */

#include <mpi.h>
#include "quiver_matrix.h"
#include "codec.h"

using cluster::QuiverMatrix;

namespace qvmmi {
	class FastMMISlave {

		public:
			FastMMISlave();
			void run();

		private:
			QuiverMatrix matrix_;
			MPI::Status status_;
			Codec<QuiverMatrix> codec_;
			bool receive(QuiverMatrix& matrix);
			void send_result(bool mmi);

	};
}

