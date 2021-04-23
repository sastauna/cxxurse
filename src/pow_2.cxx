#pragma once
#include <type_traits>
using namespace std;

template <class T, typename = enable_if_t<is_unsigned_v<T>>>
inline T pow(T base, T exp) noexcept {
	size_t prod{};
	do {
		if (exp & 1) {
			prod *= base;
		}

		base = {base * base};
	} while (exp >>= 1);
	return prod;
}
