/**
 * sure_finite_slave.h
 */
#pragma once

#include "slave.h"

#include "qv/mass_finite_check.h"

namespace qvmmi {
	class SureFiniteSlave : public Slave<int> {
		private:
			typedef cluster::MassFiniteCheck Check;

		public:
			void add_finite(const std::shared_ptr<cluster::EquivQuiverMatrix>& mat);

		protected:
			virtual int calc_result();

		private:
			Check chk_;
	};
}

