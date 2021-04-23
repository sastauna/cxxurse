#pragma once
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

constexpr size_t MAX = std::numeric_limits<size_t>::max();

constexpr bool add_will_overflow(size_t a, size_t b) {
	return b > MAX - a;
}

template<u128 *a, u128 *b>
constexpr void addTo() {
	u128 sum{a->lesser + b->lesser, }
	if constexpr (add_will_overflow(a->lesser, b->lesser)) a->greater++;
	a->lesser += b->lesser;
	a->greater += b->greater;
}

u128* add(u128* a, u128* b) {
	u128* sum = new u128;
	sum->lesser = a->lesser + b->lesser;
	sum->greater = a->greater + b->greater;
	if(add_will_overflow(a->lesser, b->lesser)) sum->greater++;
	return sum;
}

template<u128 &a, u128 &b>
constexpr void addTo() {
	if constexpr (add_will_overflow(a.lesser, b.lesser)) a.greater++;
	a.lesser += b.lesser;
	a.greater += b.greater;
}

u128* subtract(u128* a, u128* b) {
	u128* diff = new u128;
	// The overflow will take care of carrying for us
	diff->lesser = a->lesser - b->lesser;
	// a damn well be greater than b, or else I don't know what happens here.
	diff->greater = a->greater - b->greater;
	// If we needed to carry
	if(b->lesser > a->lesser) {
		diff->greater--;
	}
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
	constexpr u128 prod{A.lesser * B.lesser, A.greater * B.greater};
	addTo<prod, toMid(A.lesser * B.greater)>();
	addTo<prod, toMid(A.greater * B.lesser)>();
	return prod;
}

int main() {
	prod<1,2;
}
