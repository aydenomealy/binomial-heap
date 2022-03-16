#include <iostream>
using namespace std;

//Max size 20 nodes
template<class T>
class heapArray {
public:
    T array[20];
    int size;

    explicit heapArray(int x) {
        size = x;

        for(auto & i : array) {
            i = 0;
        }

    }

    void insert(T x) {
        for (int i = 0; i < size; i++) {
            if (array[i] == 0) {
                array[i] = x;
                i = size;
            }
        }
    }

    T min() {
        return array[0];
    }

    void heapify(int x) {
        if (array[2 * x + 2] == 0) {
            if(array[2 * x + 1] < array[x]) {
                T temp = array[2 * x + 1];
                array[2 * x + 1] = array[x];
                array[x] = temp;
            }
        }
        else {
            if (array[2 * x + 1] < array[2 * x + 2] && array[2 * x + 1] < array[x]) {
                T temp = array[2 * x + 1];
                array[2 * x + 1] = array[x];
                array[x] = temp;

                if(array[4 * x + 3] != 0)
                    heapify(2 * x + 1);
            }
            else if (array[2 * x + 1] > array[2 * x + 2] && array[2 * x + 2] < array[x]) {
                T temp = array[2 * x + 2];
                array[2 * x + 2] = array[x];
                array[x] = temp;

                if(array[4 * x + 3] != 0)
                    heapify(2 * x + 2);
            }
        }
        print();
        cout << endl << "-------------------" << endl;
    }

    void deleteMin() {
        array[0] = array[size - 1];
        array[size - 1] = 0;
        size -= 1;

        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    void buildHeap() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    void recPrint(int indent, int pos) {
        for (int j = 0; j <= indent; j++) cout << "\t";

        cout << array[pos] << endl;

        if(2 * pos + 1 < size)
            recPrint(indent + 1, 2 * pos + 1);

        if(2 * pos + 2 < size)
            recPrint(indent + 1, 2 * pos + 2);

    }

    void print() {
        recPrint(0,0);
    }
};

template <class T>
class Node {
public:
    T data;
    Node *sibling;
    Node *child;
    int degree;

    explicit Node(T d) {
        degree = 0;
        data = d;
        sibling = child = nullptr;
    }
};

template <class T>
class binomialHeap {
private:
    int size = 0;
    Node<T> *root;

public:
    explicit binomialHeap(T x) {
        root = new Node<T>(x);
        size++;
    }

    void insert(T x) {
        size++;

        if(size % 2 == 0)
            this->merge(new binomialHeap<T>(x));

        else {
            auto node = new Node<T>(x);
            node->sibling = root;
            root = node;
        }
    }

    void merge(binomialHeap<T> *h) {
        auto node1 = root;
        auto node2 = h->root;
        Node<T> *current = nullptr;
        Node<T> *temp = nullptr;

        if(node1->degree <= node2->degree) {
            current = node1;
            node1 = node1->sibling;
        } else {
            current = node2;
            node2 = node2->sibling;
        }

        temp = current;

        while(node1 != nullptr && node2 != nullptr) {
            if (node1->degree <= node2->degree) {
                current->sibling = node1;
                node1 = node1->sibling;
            } else {
                current->sibling = node2;
                node2 = node2->sibling;
            }

            current = current->sibling;
        }

        if (node1 != nullptr) {
            while(node1 != nullptr) {
                current->sibling = node1;
                node1 = node1->sibling;
                current = current->sibling;
            }
        }

        if (node2 != nullptr) {
            while(node2 != nullptr) {
                current->sibling = node2;
                node2 = node2->sibling;
                current = current->sibling;
            }
        }

        current = temp;
        Node<T> *prev = nullptr;
        auto next = current->sibling;

        while (next != nullptr) {
           if ((current->degree != next->degree ) || (next->sibling != nullptr && current->degree == next->sibling->degree)) {
                prev = current;
               current = next;
            } else {
                if (current->data <= next->data) {
                    current->sibling = next->sibling;
                    next->sibling = current->child;
                    current->child = next;
                    current->degree += 1;
                } else {
                    if (prev == nullptr) {
                        temp = next;
                    } else {
                        prev->sibling = next;
                    }

                    current->sibling = next->child;
                    next->child = current;
                    next->degree += 1;
                    current = next;
                }
            }
            next = current->sibling;
        }
        root = temp;
    }

    T min() {
        auto current = root->sibling;
        T m = root->data;
        while (current != nullptr) {
            if (m > current->data)
                m = current->data;

            current = current->sibling;
        }

        return m;
    }
};

int main() {
    int x;
    cout << "Enter number of nodes in heap:";
    cin >> x;

    auto *heap = new heapArray<int>(x);

    for(int i = 0; i < x; i++) {
        int y;
        cout << "Enter a value:";
        cin >> y;
        heap->insert(y);
    }
    cout << endl << "Current tree:" << endl;
    heap->print();
    heap->buildHeap();
    cout << endl << "Current heap:" << endl;
    heap->print();
    cout << endl << "Delete min heap:" << endl;
    heap->deleteMin();
    heap->print();

//    auto binomial = new binomialHeap<int>(6);
//    binomial->insert(4);
//    binomial->insert(8);
//    binomial->insert(2);
//    binomial->insert(1);
//    binomial->insert(9);
//    binomial->insert(5);

    return 0;
}
