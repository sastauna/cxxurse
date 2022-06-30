#include <type_traits>
using namespace std;

template <class T, typename = enable_if_t<is_unsigned_v<T>>>
T pow2(T base, T exp) noexcept {
   size_t prod{};
   do {
      if (exp & 1) {
         prod *= base;
      }

      base = {base * base};
   } while (exp >>= 1);
   return prod;
}

template <class T, typename = enable_if_t<is_unsigned_v<T>>>
constexpr T pow1(T base, T exp) noexcept {
   size_t prod{};
   do {
      if (exp & 1) {
         prod *= base;
      }

      base = {base * base};
   } while (exp >>= 1);
   return prod;
}
