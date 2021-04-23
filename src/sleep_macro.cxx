#include <chrono>
#include <thread>
using namespace std;

void sleep_ms(size_t ms) {
	this_thread::sleep_for(chrono::milliseconds(ms));
}

void sleep_s(size_t s) {
	this_thread::sleep_for(chrono::seconds(s));
}

#define make_sleep(abbr, type) void sleep_made_ ## abbr (size_t abbr) { \
	this_thread::sleep_for(chrono::type(abbr)); \
}

make_sleep(ms, milliseconds);
make_sleep(s, seconds);

int main() {
	sleep_made_ms(10);
}
