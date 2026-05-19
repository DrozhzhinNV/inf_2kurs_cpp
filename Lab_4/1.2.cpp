#include <iostream>
#include <deque>
#include <string>

template<typename T, typename Container = std::deque<T>>
class MyStack {
    Container data;
public:
    void push(const T& val) { data.push_back(val); }
    void pop() { if (!data.empty()) data.pop_back(); }
    T& top() { return data.back(); }
    const T& top() const { return data.back(); }
    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }
};

template<>
class MyStack<char, std::string> {
    std::string data;
public:
    void push(char val) { data.push_back(val); }
    void pop() { if (!data.empty()) data.pop_back(); }
    char& top() { return data.back(); }
    const char& top() const { return data.back(); }
    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }
};

int main() {
    // Стандартный стек
    MyStack<int> st;
    st.push(10); st.push(20); st.push(30);
    std::cout << "Top: " << st.top() << ", Size: " << st.size() << '\n';
    st.pop();
    std::cout << "After pop: " << st.top() << ", Size: " << st.size() << '\n';

    // Стек из char
    MyStack<char, std::string> char_st;
    char_st.push('H'); char_st.push('i');
    std::cout << "\nChar stack top: " << char_st.top() << ", Size: " << char_st.size() << '\n';
    return 0;
}