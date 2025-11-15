template<typename T>
class subvector {
    T* mas;
    unsigned int top;
    unsigned int capacity;
     
public:
    subvector() : mas(nullptr), top(0), capacity(0) {}

    ~subvector() {
        delete[] mas;
    }

    subvector(const subvector& other) : top(other.top), capacity(other.capacity) {
        mas = new T[capacity];
        for(unsigned int i = 0; i < top; i++) {
            mas[i] = other.mas[i];
        }
    }

    subvector& operator=(const subvector& other) {
        if (this != &other) {
            delete[] mas;
            top = other.top;
            capacity = other.capacity;
            mas = new T[capacity];
            for(unsigned int i = 0; i < top; i++) {
                mas[i] = other.mas[i];
            }
        }
        return *this;
    }

    subvector(subvector&& other) noexcept : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }

    subvector& operator=(subvector&& other) noexcept {
        if (this != &other) {
            delete[] mas;
            mas = other.mas;
            top = other.top;
            capacity = other.capacity;
            other.mas = nullptr;
            other.top = 0;
            other.capacity = 0;
        }
        return *this;
    }

    bool push_back(const T& d) {
        if (top >= capacity) {
            unsigned int new_cap = (capacity == 0) ? 1 : capacity * 2;
            if (!resize(new_cap)) return false;
        }
        mas[top++] = d;
        return true;
    }

    T pop_back() {
        if (top == 0) return T{};
        return mas[--top];
    }

    bool resize(unsigned int new_capacity) {
        if (new_capacity < top) {
            top = new_capacity;
        }
        T* new_mas = new T[new_capacity];
        for(unsigned int i = 0; i < top; i++) {
            new_mas[i] = mas[i];
        }
        delete[] mas;
        mas = new_mas;
        capacity = new_capacity;
        return true;
    }

    void shrink_to_fit() {
        if (top < capacity) {
            resize(top);
        }
    }

    void clear() {
        top = 0;
    }

    unsigned int get_size() const { return top; }
    unsigned int get_capacity() const { return capacity; }
};