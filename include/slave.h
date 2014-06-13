/*
 * slave.h
 */
#pragma once

#include <mpi.h>
#include "qv/quiver_matrix.h"
#include "codec.h"

namespace qvmmi {

	using cluster::QuiverMatrix;

	template<class T>
	class Slave {
		public:
			void run();

		protected:
			QuiverMatrix matrix_;
			virtual T calc_result() = 0;

		private:
			MPI::Status status_;
			Codec<QuiverMatrix> codec_;

			bool receive();
			void send_result(const T& result);

	};
}

