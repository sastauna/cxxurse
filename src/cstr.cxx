#include <cstdio>
#include <stdio.h>

struct str {
	size_t len;
	char const *data;
};

#define make_str(s) str{ \
	sizeof(# s), \
	# s \
}

#define make_str2(a, b) str { \
	sizeof(# a # b), \
	# a # b, \
}

inline void print(str const str) noexcept {
	fwrite(str.data, sizeof(char), str.len, stdout);
}

int main() noexcept {
	auto hi = make_str(Hi!);
	auto hw = make_str2(Hello, World!);
	print(hi);
	print(hw);
}
