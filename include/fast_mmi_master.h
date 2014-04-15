/*
 * fast_mmi_master.h
 */
#include <mpi.h>
#include "master.h"
#include <map>

using cluster::QuiverMatrix;

namespace qvmmi {
	class FastMMIMaster : Master {

		public:
			FastMMIMaster(const QuiverMatrix& mat);
			virtual void run();

		protected:
			virtual void handle_result(int result, int worker);

		private:
			std::map<int, QuiverMatrix> map_;

	};
}

