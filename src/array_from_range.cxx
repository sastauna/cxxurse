#include <array>
using namespace std;

template <typename T, size_t from, size_t to, size_t i = from, size_t ...vals>
constexpr array<T, to - from> from_range() {
	if constexpr (i < to) {
		return from_range<T, from, to, i + 1, vals..., i>();
	} else {
		return {vals...,};
	}
}

static auto one_to_ten{from_range<size_t, 1, 10>()};
