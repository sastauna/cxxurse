#include <limits>

struct u128 {
	size_t greater;
	size_t lesser;
};

size_t MAX = std::numeric_limits<size_t>::max();

bool add_will_overflow(size_t a, size_t b) {
	return b > MAX - a;
}

u128* add(u128* a, u128* b) {
	u128* sum = new u128;
	sum->lesser = a->lesser + b->lesser;
	sum->greater = a->greater + b->greater;
	if(add_will_overflow(a->lesser, b->lesser)) sum->greater++;
	return sum;
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
