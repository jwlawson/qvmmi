/*
 * codec.h
 */
#pragma once
#include <memory>

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
		int* encode(T matrix);

		/**
		 * Decode an integer array back into the IntMatrix it came from.
		 *
		 * @param arr Pointer to the array
		 * @return Matrix stored in the array
		 */
		T decode(int* arr, int size);

	};
}

