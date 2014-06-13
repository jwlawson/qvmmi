/*
 * codec.cc
 */
#include "codec.h"

#include "qv/quiver_matrix.h"

namespace qvmmi {

		template<class T>
		int* Codec<T>::encode(T matrix) {
			int rows = matrix.num_rows();
			int cols = matrix.num_cols();
			const int* data = matrix.data();
			int * arr = new int[2 + matrix.num_rows() * matrix.num_cols()];
			arr[0] = rows;
			arr[1] = cols;
			for(int i = 2; i < 2 + matrix.num_rows() * matrix.num_cols(); ++i) {
				arr[i] = data[i-2];
			}
			return arr;
		}

		template<class T>
		T Codec<T>::decode(int* arr) {
			int rows = arr[0];
			int cols = arr[1];
			int* val = arr + 2;
			T result(rows, cols, val);
			return result;
		}

		template class Codec<cluster::QuiverMatrix>;
}

