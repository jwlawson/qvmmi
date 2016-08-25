/*
 * slave.h
 */
#pragma once

#include <mpi.h>
#include "qv/equiv_quiver_matrix.h"
#include "codec.h"

namespace qvmmi {

	template<class T>
	class Slave {
		protected:
			typedef cluster::EquivQuiverMatrix Matrix;

		public:
			void run();

		protected:
			Matrix matrix_;
			virtual T calc_result() = 0;

		private:
			MPI::Status status_;
			Codec<Matrix> codec_;
			std::vector<int> array_cache_;

			bool receive();
			void send_result(const T& result);

	};
}

