#include <iostream>
#include <array>
#include <tuple>

template<typename... Ts, size_t... Ns, typename... Idx>
constexpr auto get_cartesian_element(const std::array<Ts, Ns>&... arrays, Idx... indices) {
    // 1. Проверка количества индексов
    static_assert(sizeof...(Ns) == sizeof...(Idx),
                  "Ошибка: количество индексов не совпадает с количеством массивов");
    
    // 2. Проверка выхода индексов за границы
    static_assert(((indices < Ns) && ...),
                  "Ошибка: один или несколько индексов выходят за границы массивов");
                  
    return std::make_tuple(arrays[indices]...);
}

int main() {
    constexpr std::array arr1 = {1, 2, 3};
    constexpr std::array arr2 = {'a', 'b'};
    constexpr std::array arr3 = {10.0, 20.0, 30.0};

    constexpr auto elem = get_cartesian_element(arr1, arr2, arr3, 2, 1, 0);
    
    std::cout << "Element: (" 
              << std::get<0>(elem) << ", " 
              << std::get<1>(elem) << ", " 
              << std::get<2>(elem) << ")\n";

    return 0;
}