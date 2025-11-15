template<typename T>
class subforwardlist {
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* begin;
    unsigned int list_size;

public:
    subforwardlist() : begin(nullptr), list_size(0) {}

    ~subforwardlist() {
        clear();
    }

    subforwardlist(const subforwardlist& other) : begin(nullptr), list_size(0) {
        Node** current = &begin;
        for (Node* node = other.begin; node != nullptr; node = node->next) {
            *current = new Node(node->data);
            current = &((*current)->next);
            list_size++;
        }
    }

    subforwardlist& operator=(const subforwardlist& other) {
        if (this != &other) {
            clear();
            Node** current = &begin;
            for (Node* node = other.begin; node != nullptr; node = node->next) {
                *current = new Node(node->data);
                current = &((*current)->next);
                list_size++;
            }
        }
        return *this;
    }

    subforwardlist(subforwardlist&& other) noexcept : begin(other.begin), list_size(other.list_size) {
        other.begin = nullptr;
        other.list_size = 0;
    }

    subforwardlist& operator=(subforwardlist&& other) noexcept {
        if (this != &other) {
            clear();
            begin = other.begin;
            list_size = other.list_size;
            other.begin = nullptr;
            other.list_size = 0;
        }
        return *this;
    }

    void push_back(const T& data) {
        Node* new_node = new Node(data);
        if (!begin) {
            begin = new_node;
        } else {
            Node* current = begin;
            while (current->next) current = current->next;
            current->next = new_node;
        }
        list_size++;
    }

    T pop_back() {
        if (!begin) return T{};
        if (!begin->next) {
            T data = begin->data;
            delete begin;
            begin = nullptr;
            list_size--;
            return data;
        }

        Node* current = begin;
        while (current->next->next) current = current->next;
        T data = current->next->data;
        delete current->next;
        current->next = nullptr;
        list_size--;
        return data;
    }

    void push_forward(const T& data) {
        Node* new_node = new Node(data);
        new_node->next = begin;
        begin = new_node;
        list_size++;
    }

    T pop_forward() {
        if (!begin) return T{};
        Node* temp = begin;
        T data = begin->data;
        begin = begin->next;
        delete temp;
        list_size--;
        return data;
    }

    void push_where(unsigned int where, const T& data) {
        if (where == 0) {
            push_forward(data);
            return;
        }
        if (where > list_size) return;

        Node* current = begin;
        for (unsigned int i = 0; i < where - 1; i++) {
            current = current->next;
        }
        Node* new_node = new Node(data);
        new_node->next = current->next;
        current->next = new_node;
        list_size++;
    }

    T erase_where(unsigned int where) {
        if (where >= list_size) return T{};
        if (where == 0) {
            return pop_forward();
        }

        Node* current = begin;
        for (unsigned int i = 0; i < where - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        T data = temp->data;
        current->next = temp->next;
        delete temp;
        list_size--;
        return data;
    }

    unsigned int size() const {
        return list_size;
    }

    void clear() {
        while (begin) {
            Node* temp = begin;
            begin = begin->next;
            delete temp;
        }
        list_size = 0;
    }
};