/*
 * master.h
 */
#pragma once

#include <mpi.h>
#include "codec.h"
#include "quiver_matrix.h"

namespace qvmmi {

	using cluster::QuiverMatrix;

	class Master {
		public:
			Master();
			virtual void run() = 0;

		protected:
			int num_proc_;
			MPI::Status status_;

			void send_matrix(const QuiverMatrix& matrix, int worker);
			int receive_result();
			void send_shutdown();

			virtual void handle_result(int result, int worker) = 0;

		private:
			Codec<QuiverMatrix> codec_;

	};
} 

