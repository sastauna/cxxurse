#include "modpow_1.cxx"
#include <cstdint>

constexpr bool is_prime_1(size_t const val) noexcept {
	return modpow_1(2, val) == 1;
}

