#pragma once
#include <cstddef>
#include <cstdint>

using u64 = uint64_t;

constexpr unsigned char halfsize{sizeof(u64) * 4};
constexpr unsigned char fullsize{2 * halfsize};
constexpr u64 max32 = 0x00000000FFFFFFFF;
constexpr u64 max64 = 0xFFFFFFFFFFFFFFFF;

struct u128 {
	u64 greater;
	u64 lesser;
	constexpr u128(u64 greater, u64 lesser) noexcept:
		greater{greater},
		lesser{lesser}
	{}
};

struct u32_2 {
	u64 greater;
	u64 lesser;
	constexpr u32_2(u64 a) noexcept:
		greater{a >> halfsize},
		lesser{a & max32}
	{}
};

constexpr bool add_will_overflow(u64 a, u64 b) {
	return b > max64 - a;
}

constexpr bool greaterthan(u128 a, u128 b) {
	return a.greater > b.greater || (a.greater == b.greater && a.lesser > b.lesser);
}

constexpr u128 shiftL(u128 a, int shift) {
	u128 shifted{a.greater << shift | (a.lesser >> (fullsize - shift)), a.lesser << shift};
	return shifted;
}

constexpr u128 shiftL(u128 a) {
	return shiftL(a, 1);
}

constexpr u128 shiftR(u128 a, int shift) {
	u128 shifted{a.greater >> shift, (a.greater << (fullsize - shift)) | a.lesser >> shift};
	return shifted;
}

constexpr u128 shiftR(u128 a) {
	return shiftR(a, 1);
}

constexpr u128 add(u128 a, u128 b) {
	u128 sum{a.greater + b.greater, a.lesser + b.lesser};
	if (add_will_overflow(a.lesser, b.lesser)) sum.greater++;
	return sum;
}

constexpr u128 subtract(u128 a, u128 b) {
	// a damn well be greater than b, or else I don't know what happens here.
	// The overflow will take care of carrying for us
	u128 diff{a.greater - b.greater, a.lesser - b.lesser};
	// If we needed to carry
	if(b.lesser > a.lesser) diff.greater--;
	return diff;
}

constexpr u128 to_mid(u64 in) {
	return {in >> halfsize, in << halfsize};
}

constexpr u128 multiply(u64 a, u64 b) {
	u32_2 A{a};
	u32_2 B{b};
	u128 prod{A.greater * B.greater, A.lesser * B.lesser};
	u128 midProd1 = to_mid(A.lesser * B.greater);
	u128 midProd2 = to_mid(A.greater * B.lesser);
	return add(add(prod, midProd1), midProd2);
}

constexpr u128 getMaxPower(u128 a, u128 test) {
	return greaterthan(test, shiftR(a, 1)) ? test : getMaxPower(a, shiftL(test, 1));
}

constexpr u64 modularSubtract(u128 a, u128 x) {
	if(a.greater == 0) return a.lesser;
	return modularSubtract(greaterthan(x, a) ? a : subtract(a, x), shiftR(x, 1));
}

constexpr u64 mod(u128 a, u64 base) {
	if(a.greater == 0) {
		return a.lesser % base;
	}
	return modularSubtract(a, getMaxPower(a, u128{0, base})) % base;
}

constexpr u64 modpow_rec(
	u64 const base,
	u64 const divisor,
	u64 const exp,
	u64 const prod
) noexcept
{
	if (exp == 0) {
		return prod;
	}

	return modpow_rec(
		mod(multiply(base, base), divisor),
		divisor,
		exp >> 1,
		exp & 1 ? mod(multiply(prod, base), divisor) : prod
	);
}

constexpr u64 modpow(u64 base, u64 exp, u64 divisor) {
	return modpow_rec(base, exp, divisor, 1);
}

constexpr bool is_pseudoprime(u64 p, u64 test) {
	return modpow(p, test - 1, test) == 1;
}

#include <iostream>
int main() {
	constexpr u128 product = multiply(max64 - 2, max64 - 4);
	// max64 is divisible by max32, so we should expect a remainder of (-2)*(-4)
	constexpr u64 remainder = mod(product, max32);
	std::cout << remainder << '\n';
}
