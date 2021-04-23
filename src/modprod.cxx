#pragma once
#include <iostream>
#include <limits>
#include <cstdint>

#define size_t uint64_t
#define times *

constexpr int i = 0xFFFF;
constexpr unsigned char c = i;
constexpr unsigned char halfsize{sizeof(size_t) * 4};

struct u128 {
	size_t greater;
	size_t lesser;
	constexpr u128(size_t greater, size_t lesser) noexcept:
		greater{greater},
		lesser{lesser}
	{}
};

struct u32_2 {
	static constexpr size_t lesser_mask32 = 0x00000000FFFFFFFF;
	size_t greater;
	size_t lesser;
	constexpr u32_2(size_t a) noexcept:
		greater{a >> halfsize},
		lesser{a & u32_2::lesser_mask32}
	{}
};

constexpr size_t max64 = 0xFFFFFFFFFFFFFFFF;

constexpr bool add_will_overflow(size_t a, size_t b) {
	return b > max64 - a;
}

constexpr u128 add(u128 a, u128 b) {
	u128 sum{a.greater + b.greater, a.lesser + b.lesser};
	if(add_will_overflow(a.lesser, b.lesser)) sum.greater++;
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

int main() {
	constexpr u128 product = prod<max64, max64>();
	std::cout << product.lesser << '\n';
}
