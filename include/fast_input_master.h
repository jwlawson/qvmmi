/**
 * fast_input_master.h
 *
 * Contains headers for the FastInputMaster class. This Master object takes an
 * input stream of matrices and checks all extensions of those matrices. Any
 * minimally mutation infinite matrices found in this way are then output to
 * stdout.
 */
#pragma once

#include "master.h"

#include "qv/stream_extension_iterator.h"

namespace qvmmi {
	class FastInputMaster : Master {
		private:
			typedef cluster::QuiverMatrix Matrix;
			typedef std::shared_ptr<Matrix> MatrixPtr;
			typedef cluster::StreamExtIterator<Matrix> Iter;

		public:
			FastInputMaster(std::istream& input);
			virtual void run();

		protected:
			virtual void handle_result(int result, int worker);

		private:
			Iter iter_;
			std::map<int, MatrixPtr> map_;
	};
}

