#pragma once

template <size_t ...vals>
constexpr size_t sum = (vals + ...);

// constexpr auto sum_example{sum<1, 2, 3>};
