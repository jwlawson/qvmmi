/*
 * codec.cc
 */
#include "codec.h"

#include "qv/equiv_quiver_matrix.h"

#include <cstring>

namespace qvmmi {

	template<class T>
	int*
	Codec<T>::encode(T const& matrix) {
		int rows = matrix.num_rows();
		int cols = matrix.num_cols();
		const int* data = matrix.data();
		_array_cache.reserve(2 + rows * cols);
		int * arr = _array_cache.data();
		arr[0] = rows;
		arr[1] = cols;
		std::memcpy(arr + 2, data, rows * cols * sizeof(int));
		return arr;
	}

	template<class T>
	T const&
	Codec<T>::decode(int* arr) {
		decode_into(arr, _matrix_cache);
		return _matrix_cache;
	}
	template<class T>
	void
	Codec<T>::decode_into(int* arr, T& result) {
		int rows = arr[0];
		int cols = arr[1];
		int* val = arr + 2;
		if(result.num_rows() == rows && result.num_cols() == cols) {
			std::memcpy(result.data(), val, rows * cols * sizeof(int));
			result.reset();
		} else {
			result = T(rows, cols, val);
		}
	}

	template class Codec<cluster::QuiverMatrix>;
	template class Codec<cluster::EquivQuiverMatrix>;
}

