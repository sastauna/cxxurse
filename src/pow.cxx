// marcus's pow

inline size_t pow(size_t base, size_t exp) noexcept {
   size_t prod{};
   do {
      if (exp & 1) {
         prod *= base;
      }

      base = {base * base};
   } while (exp >>= 1);
   return prod;
}
