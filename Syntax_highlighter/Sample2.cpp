#include <iostream>
#include <stdexcept>

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        this->data = val;
        this->next = nullptr;
    }
};


class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList() {
        this->head = nullptr;
        this->size = 0;
    }

   
    void push_front(int val) {
        Node* new_node = new Node(val);
        new_node->next = head;
        head = new_node;
        size++;
    }

   
    void push_back(int val) {
        Node* new_node = new Node(val);
        if (head == nullptr) {
            head = new_node;
        } else {
            Node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = new_node;
        }
        size++;
    }

    
    void remove(int val) {
        if (head == nullptr) return;

        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        Node* curr = head;
        while (curr->next != nullptr) {
            if (curr->next->data == val) {
                Node* temp = curr->next;
                curr->next = temp->next;
                delete temp;
                size--;
                return;
            }
            curr = curr->next;
        }
    }

  
    int search(int val) {
        Node* curr = head;
        int index = 0;
        while (curr != nullptr) {
            if (curr->data == val) return index;
            curr = curr->next;
            index++;
        }
        return -1;
    }

    
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        while (curr != nullptr) {
            next       = curr->next;
            curr->next = prev;
            prev       = curr;
            curr       = next;
        }
        head = prev;
    }

    void print() {
        Node* curr = head;
        while (curr != nullptr) {
            std::cout << curr->data;
            if (curr->next != nullptr) std::cout << " -> ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    int get_size() { return size; }

 
    ~LinkedList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);
    list.push_front(1);

    std::cout << "List: ";
    list.print();
    std::cout << "Size: " << list.get_size() << std::endl;

    int target = 20;
    int idx = list.search(target);
    if (idx != -1) {
        std::cout << target << " found at index " << idx << std::endl;
    } else {
        std::cout << target << " not found" << std::endl;
    }

    list.remove(20);
    std::cout << "After remove(20): ";
    list.print();

    list.reverse();
    std::cout << "After reverse: ";
    list.print();

    return 0;
}


//Sample 2

/* Multi linie commment 
lal  
lal
lala
*/