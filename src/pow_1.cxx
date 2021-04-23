#include <type_traits>
using namespace std;

template <class T, typename = enable_if_t<is_unsigned_v<T>>>
constexpr T pow_rec(T const base, T const exp, T const prod) noexcept {
	if (exp == 0) {
		return prod;
	}

	if (exp & 1) {
		return pow_rec(
			base * base,
			exp >> 1,
			prod * base
		);
	} else {
		return pow_rec(
			base * base,
			exp >> 1,
			prod
		);
	}
}

template <class T, typename = enable_if_t<is_unsigned_v<T>>>
constexpr T pow_1(T const base, T const exp) noexcept {
	return pow_rec(base, exp, static_cast<T>(1));
}
