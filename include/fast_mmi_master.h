/*
 * fast_mmi_master.h
 */
#pragma once

#include <map>

#include "class_ext_iterator.h"
#include "master.h"

namespace qvmmi {
	class FastMMIMaster : Master {
		private:
			typedef cluster::QuiverMatrix Matrix;
			typedef cluster::EquivMutClassExtIterator Iterator;

		public:
			FastMMIMaster(const Matrix& mat);
			virtual void run();

		protected:
			virtual void handle_result(int result, int worker);

		private:
			Iterator iter_;
			std::map<int, Matrix> map_;

	};
}

