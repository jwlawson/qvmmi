/*
 * fast_mmi_slave.h
 */
#pragma once
#include "slave.h"

using cluster::QuiverMatrix;

namespace qvmmi {
	class FastMMISlave : public Slave<bool> {

		public:
			void add_finite(const std::shared_ptr<cluster::EquivQuiverMatrix>& mat);

		protected:
			virtual bool calc_result();

	};
}

