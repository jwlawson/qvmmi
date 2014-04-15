/*
 * fast_mmi_master.h
 */
#pragma once

#include <map>

#include <mpi.h>

#include "master.h"

using cluster::QuiverMatrix;

namespace qvmmi {
	class FastMMIMaster : Master {

		public:
			FastMMIMaster(const QuiverMatrix& mat);
			virtual void run();

		protected:
			virtual void handle_result(int result, int worker);

		private:
			QuiverMatrix matrix_;
			std::map<int, QuiverMatrix> map_;

	};
}

