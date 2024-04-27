#include <iostream>
#include <stdexcept>

// Объявление класса LinkedList, который будет использован как основа для адаптера
class LinkedList {
protected:
    struct Node {
        Node* next;
        void* data;

        Node(void* data, Node* next) : data(data), next(next) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void addToFront(void* element) {
        head = new Node(element, head);
    }

    void* removeFromFront() {
        if (isEmpty()) {
            throw std::logic_error("List is empty");
        }
        void* element = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return element;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    ~LinkedList() {
        while (!isEmpty()) {
            removeFromFront();
        }
    }
};

class Stack {
public:
    virtual void push(void* element) = 0;
    virtual void* pop() = 0;
    virtual bool isEmpty() const = 0;

    virtual ~Stack() {}
};

// Адаптер стека, основанный на классе LinkedList
class LinkedListToStackAdapter : public LinkedList, public Stack {
public:
    // Методы интерфейса Stack, адаптированные к методам LinkedList
    void push(void* element) override {
        addToFront(element);
    }

    void* pop() override {
        return removeFromFront();
    }

    bool isEmpty() const override {
        return LinkedList::isEmpty();
    }
};

// Пример использования адаптера LinkedListToStackAdapter
int main() {
    LinkedListToStackAdapter stackAdapter;

    stackAdapter.push(new int(5));
    stackAdapter.push(new int(10));

    std::cout << "Pop: " << *(static_cast<int*>(stackAdapter.pop())) << std::endl;
    std::cout << "Pop: " << *(static_cast<int*>(stackAdapter.pop())) << std::endl;

    return 0;
}