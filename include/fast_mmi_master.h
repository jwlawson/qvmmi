/*
 * fast_mmi_master.h
 */
#include <mpi.h>
#include "quiver_matrix.h"
#include "codec.h"
#include <map>

using cluster::QuiverMatrix;

namespace qvmmi {
	class FastMMIMaster {

		public:
			FastMMIMaster(const QuiverMatrix& mat);
			void run();

		private:
			QuiverMatrix matrix_;
			MPI::Status status_;
			Codec<QuiverMatrix> codec_;
			std::map<int, QuiverMatrix> map_;

			void send_matrix(const QuiverMatrix& matrix, int worker);
			int receive_result();
			void handle_result(int result, int worker);
			void send_shutdown(int number);
	};
}

