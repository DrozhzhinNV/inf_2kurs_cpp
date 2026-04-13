#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iterator>

template<typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    using Cat = typename std::iterator_traits<RandomAccessIterator>::iterator_category;
    static_assert(std::is_same_v<Cat, std::random_access_iterator_tag>,
                  "Ошибка: сортировка требует RandomAccessIterator"

    if (first == last) return;

    // QuickSort
    auto quick = [&](auto&& self, auto l, auto r) -> void {
        if (l >= r) return;
        auto pivot = *(l + (r - l) / 2);
        auto i = l, j = r;
        while (i <= j) {
            while (comp(*i, pivot)) ++i;
            while (comp(pivot, *j)) --j;
            if (i <= j) {
                std::iter_swap(i, j);
                ++i; --j;
            }
        }
        if (l < j) self(self, l, j);
        if (i < r) self(self, i, r);
    };

    quick(quick, first, last - 1);
}

int main() {
    // 1
    std::vector<int> v = {5, 2, 8, 1};
    sort(v.begin(), v.end(), [](int a, int b){ return a < b; });
    std::cout << "Vector (lambda): "; for(int x : v) std::cout << x << ' '; std::cout << '\n';

    // 2
    auto cmp = [](double a, double b){ return a > b; };
    std::deque<double> dq = {3.1, 1.5, 4.2};
    sort(dq.begin(), dq.end(), cmp);
    std::cout << "Deque (func):    "; for(double x : dq) std::cout << x << ' '; std::cout << '\n';

    // 3
    struct ModComp { bool operator()(int a, int b) const { return a % 3 < b % 3; } };
    std::vector<int> mod = {7, 4, 10, 2, 9};
    sort(mod.begin(), mod.end(), ModComp{});
    std::cout << "Vector (functor):"; for(int x : mod) std::cout << x << ' '; std::cout << '\n';

    // Бенчмарк vector vs deque
    constexpr size_t N = 500000;
    std::vector<int> vb(N), db(N);
    std::iota(vb.begin(), vb.end(), 0); std::shuffle(vb.begin(), vb.end(), std::mt19937(42));
    db = vb;

    auto t1 = std::chrono::high_resolution_clock::now();
    sort(vb.begin(), vb.end(), std::less<int>());
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    sort(db.begin(), db.end(), std::less<int>());
    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout << "\nVector time: " << std::chrono::duration<double, std::milli>(t2-t1).count() << " ms\n";
    std::cout << "Deque  time: " << std::chrono::duration<double, std::milli>(t4-t3).count() << " ms\n";

    return 0;
}