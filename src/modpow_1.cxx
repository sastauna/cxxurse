#pragma once

constexpr size_t modpow_rec(
	size_t const base,
	size_t const exp,
	size_t const prod,
	size_t const bits
) noexcept
{
	if (bits == 0) {
		return prod;
	}

	return modpow_rec(
		(base * base) % exp,
		exp,
		bits & 1 ? (prod * base) % exp : prod,
		bits >> 1
	);
}

constexpr size_t modpow_1(size_t const base, size_t const exp) noexcept {
	return modpow_rec(base, exp, 1, exp - 1);
}
