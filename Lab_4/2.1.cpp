#include <iostream>
#include <tuple>
#include <string>

template<typename Func, typename Tuple, size_t I = 0>
struct TupleForEach {
    static void apply(Tuple& t, Func f) {
        f(std::get<I>(t));
        TupleForEach<Func, Tuple, I + 1>::apply(t, f);
    }
};

// База рекурсии
template<typename Func, typename Tuple, size_t N>
struct TupleForEach<Func, Tuple, N> {
    static void apply(Tuple&, Func) {}
};

template<typename Func, typename Tuple>
void tuple_for_each(Tuple& t, Func f) {
    TupleForEach<Func, Tuple>::apply(t, f);
}

int main() {
    auto t = std::make_tuple(42, 3.14, std::string("hello"));
    
    // Печатаем каждый эл-т
    tuple_for_each(t, [](auto& x) {
        std::cout << x << " | ";
    });
    std::cout << '\n';

    tuple_for_each(t, [](auto& x) {
        if constexpr (std::is_arithmetic_v<decltype(x)>) x *= 2;
    });
    tuple_for_each(t, [](auto& x) { std::cout << x << " | "; });
    std::cout << '\n';
    return 0;
}