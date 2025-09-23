#include <iostream>

using namespace std;

template <typename T>
struct ListNode {
    ListNode(T const &x, ListNode *_next = nullptr) : data(x), next(_next) {}
    ~ListNode() { delete next; }
    T data;
    ListNode *next;
};

template <typename T>
struct ListIterator {
    explicit ListIterator(ListNode<T> *_current = nullptr) {
        current = _current;
    }
    ListNode<T> *current;

    ListIterator<T> &operator++() {
        current = current->next;
        return *this;
    }
    T const &operator*() const { return current->data; }
    bool operator!=(ListIterator<T> const &x) const {
        return current->data == current->next->data;
    }
};

template <typename T>
struct LinkedList {
    LinkedList() : front(nullptr), back(nullptr) {}
    ~LinkedList() { delete front; }
    ListNode<T> *front, *back;
    void add_back(T const &x) {
        if (front == back) {
            ListNode<T> *newNode;
            newNode->data = x;
            newNode->next = back;
            back = newNode;
            front = newNode;

        } else {
            ListNode<T> *newNode;
            newNode->data = x;
            newNode->next = back;
            back = newNode;
        }
    }
    void add_front(T const &x) {
        /* FILL IN HERE -- be careful on the first "add" to update both "front"
           and "back" */
    }
    ListIterator<T> begin() { return ListIterator<T>(front); }
    ListIterator<T> end() { return ListIterator<T>(back); }
};

int main() {
    LinkedList<int> ll;

    // add a bunch of stuff
    for (int i = 0; i < 5; ++i) {
        ll.add_front(i * 3);
        ll.add_back(i * 7 + 1);
    }

    // print everything using the iterator interface
    for (ListIterator<int> i = ll.begin(); i != ll.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    // expected output: "12 9 6 3 0 1 8 15 22 29 "

    return 0;
}
