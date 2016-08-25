/*
 * codec.h
 */
#pragma once

#include <vector>

namespace qvmmi {
	template<class T>
	class Codec {
		public:
		/**
		 * Encode an IntMatrix into a single integer array.
		 *
		 * @param matrix Matrix to encode
		 * @return Array containing the matrix
		 */
		int* encode(T const& matrix);

		/**
		 * Decode an integer array back into the IntMatrix it came from.
		 *
		 * @param arr Pointer to the array
		 * @return Matrix stored in the array
		 */
		T const& decode(int* arr);
		void decode_into(int* arr, T& result);
		private:
		std::vector<int> _array_cache;
		T _matrix_cache;

	};
}

