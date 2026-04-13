#include <iostream>
#include <array>
#include <cstddef>

// constexpr считает произвольный эл-т рекуррента

template<std::size_t N, typename T = double>
constexpr T linear_recurrence(
    const std::array<T, N>& initial,
    const std::array<T, N>& coeffs,
    std::size_t target)
{
    if (target < N) return initial[target];

    std::array<T, target + 1> seq = initial;

    for (std::size_t i = N; i <= target; ++i) {
        T next_val = T(0);
        for (std::size_t j = 0; j < N; ++j) {
            next_val += coeffs[j] * seq[i - N + j];
        }
        seq[i] = next_val;
    }
    return seq[target];
}

int main() {
    constexpr std::array fib_init = {0.0, 1.0};
    constexpr std::array fib_coeff = {1.0, 1.0};

    constexpr double fib_10 = linear_recurrence<2>(fib_init, fib_coeff, 10);
    static_assert(fib_10 == 55.0, "Ошибка: Fib(10) должно быть 55");
    std::cout << "Fib(10) = " << fib_10 << " (вычислено в compile-time)\n";

    constexpr std::array rec3_init = {1.0, 1.0, 1.0};
    constexpr std::array rec3_coeff = {0.5, -1.0, 2.0};

    constexpr double val_7 = linear_recurrence<3>(rec3_init, rec3_coeff, 7);

    std::cout << "Rec3(7) = " << val_7 << " (вычислено в compile-time)\n";

    constexpr std::array<int, 1> int_init = {1};
    constexpr std::array<int, 1> int_coeff = {3};
    constexpr int geom_5 = linear_recurrence<1, int>(int_init, int_coeff, 5);
    std::cout << "Geom(5) = " << geom_5 << " (тип int, compile-time)\n";

    return 0;
}