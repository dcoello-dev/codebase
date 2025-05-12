// sandbox_idea: cpp/ideas
// sandbox_name: preallocated_vector
// sandbox_description:
// sandbox_env: cpp

#include <iostream>
#include <array>

struct Elem {
    Elem () {
        std::cout << "Elem ctor" << std::endl;
    }
    ~Elem () {
        std::cout << "Elem dtor" << std::endl;
    }
    int a;
};

template<typename T, size_t N>
class List {
    struct Node {
        uint8_t * buffer;
        bool in_use = false;
        Node * next = nullptr;
    };

    List(){
        uint8_t * ptr = buffer.data();
        Node * current_node = nullptr;
        for (int i = 0 ; i < N ; i++) {
            ptr = ptr + (i * sizeof(T));
            current_node = static_cast<Node*>(ptr);
            current_node->buffer = ptr;
            current_node->in_use = false;
            current_node->next = nullptr;
            // new (ptr->buffer)();
        }
        head = &nodes[0];
    }

    Node* available_node() {
        for (auto & node: nodes) {
            if (!node.in_use) {
                return &node;
            }
        }
        return nullptr;
    }

    void append_node(Node * node) {
        Node * ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = node;
    }

    bool push_back(T && elem) {
        Node * node = available_node();
        if (node) {
            T* emplaced_elem = static_cast<T*>(node->buffer);
            *emplaced_elem = std::move(elem);
            node->in_use = true;
            node->next = nullptr;
            append_node(node);
            return true;
        }
        return false;
    }

    template<typename Args...>
    bool emplace_back(Args && ... args) {

    }

private:
    std::array<uint8_t, sizeof(T) * N> buffer {};
    std::array<Node, N> nodes {};
    Node * head = nullptr;
};

int main(void) {
    std::cout << "Hello World!" << std::endl;
    return 0;
}
