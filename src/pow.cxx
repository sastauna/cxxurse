#include <type_traits>
using namespace std;
// marcus's pow

inline size_t modpow(size_t base, size_t const exp) noexcept {
	size_t prod{1};
	size_t consumable{exp};
	do {
		if (consumable & 1) {
			prod = (prod * base) % exp;
		}

		base = (base * base) % exp;
	} while (consumable >>= 1);
	return prod;
}

template<size_t v>
constexpr size_t shiftR = v >> 1;

template<size_t exp, size_t prod, size_t base, size_t bits, typename = enable_if<bits != 0>>
constexpr size_t modpowrec = modpowrec<
	exp,
	bits & 1 ? (prod * base) % exp : prod,
	(base * base) % exp,
	shiftR<bits>
>;

// template<size_t exp, size_t prod, size_t base>
// constexpr size_t modpowrec<0> = prod;

inline size_t modpow(size_t base, size_t const exp) noexcept {
	size_t prod{1};
	size_t bits{exp};
	do {
		if (bits & 1) {
			prod = (prod * base) % exp;
		}

		base = (base * base) % exp;
	} while (bits >>= 1);
	return prod;
}
