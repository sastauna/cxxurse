#pragma once
#include <iostream>
#include <limits>
#include <cstdint>

#define size_t uint64_t
#define times *

constexpr int i = 0xFFFF;
constexpr unsigned char c = i;
constexpr unsigned char halfsize{sizeof(size_t) * 4};
constexpr unsigned char fullsize{2 * halfsize};
constexpr size_t max32  = 0x00000000FFFFFFFF;
constexpr size_t max64  = 0xFFFFFFFFFFFFFFFF;
constexpr size_t mask63 = 0x8000000000000000;

struct u128 {
	size_t greater;
	size_t lesser;
	constexpr u128(size_t greater, size_t lesser) noexcept:
		greater{greater},
		lesser{lesser}
	{}
};

struct u32_2 {
	size_t greater;
	size_t lesser;
	constexpr u32_2(size_t a) noexcept:
		greater{a >> halfsize},
		lesser{a & max32}
	{}
};


constexpr bool add_will_overflow(size_t a, size_t b) {
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

constexpr u128 toMid(size_t in) {
	u128 res{in >> halfsize, in << halfsize};
	return res;
}

template<size_t a, size_t b>
constexpr u128 prod() {
	constexpr u32_2 A(a);
	constexpr u32_2 B(b);
	constexpr u128 prod{A.greater * B.greater, A.lesser * B.lesser};
	constexpr u128 midProd1 = toMid(A.lesser * B.greater);
	constexpr u128 midProd2 = toMid(A.greater * B.lesser);
	return add(add(prod, midProd1), midProd2);
}

constexpr u128 getMaxPower(u128 a, u128 test) {
	return greaterthan(test, shiftR(a, 1)) ? test : getMaxPower(a, shiftL(test, 1));
}

constexpr size_t modularSubtract(u128 a, u128 x) {
	if(a.greater == 0) return a.lesser;
	return modularSubtract(greaterthan(x, a) ? a : subtract(a, x), shiftR(x, 1));
}

constexpr size_t mod(u128 a, size_t base) {
	if(a.greater == 0) {
		return a.lesser % base;
	}
	return modularSubtract(a, getMaxPower(a, u128{0, base})) % base;
}

int main() {
	constexpr u128 product = prod<max64 - 2, max64 - 4>();
	// max64 is divisible by max32, so we should expect a remainder of (-2)*(-4)
	constexpr size_t remainder = mod(product, max32);
}
