#include <stdlib.h>
#include <stdint.h>
#include <utility>

using u32 = uint32_t;

constexpr u32 len(u32 n) {
	u32 l = 0;
	while(n) {
		l++;
		n>>=1;
	}
	return l;
}
constexpr u32 ceildiv(u32 a, u32 b) {
	return !!(a % b) + a / b;
}
std::pair<u32, char*> to_memseq(u32 num_msgs, u32* ns, char** msgs) {
	u32 buf_length = 0;
	for(u32 k = 0; k < num_msgs; k++) {
		u32 n = ns[k];
		buf_length += ceildiv(len(n), 7) + n;
	}
	
	char* buf = (char *) malloc(buf_length);
	u32 I = 0;
	for(u32 k = 0; k < num_msgs; k++) {
		u32 n = ns[k];
		u32 t = ceildiv(len(n), 7);
		char m = (1<<7) - 1;
		
		for(u32 i = 0; i < t; i++) {
			char nshifted = n >> (7 * (t - 1 - i));
			char firstbit = (t - 1 > i) << 7;
			buf[I + i] = firstbit | (nshifted & m);
		}
		I += t;
		
		for(u32 j = 0; j < n; j++) {
			buf[I + j] = msgs[k][j];
		}
		I += n;
	}
	
	return std::make_pair(num_msgs, buf);
}

std::pair<u32, std::pair<u32*, char**>> from_mem(u32 num_msgs, char* s) {
	u32* ns = (u32*) malloc(4 * num_msgs);
	char** msgs = (char**) malloc(8 * num_msgs);
	
	char m = (1<<7) - 1;
	
	u32 I = 0;
	for(u32 k = 0; k < num_msgs; k++) {
		u32 n = 0;
		do {
			n = n << 7 | (s[I] & m);
			I++;
		} while(s[I - 1] >> 7);
		
		ns[k] = n;
		char* msg = (char*) malloc(n);
		for(u32 j = 0; j < n; j++) {
			msg[j] = s[I + j];
		}
		msgs[k] = msg;
		I += n;
	}
	return std::make_pair(num_msgs, std::make_pair(ns, msgs));
}
