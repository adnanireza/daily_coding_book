#include <iostream>
#include <unordered_map>
using namespace std;

template <typename Tkey, typename Tvalue>
class LRU {
protected:
    struct Node {
        Tvalue data;
        Node *prev = nullptr;
        Node *next = nullptr;
        Node(Tvalue val) : data(val) {}
    };
    const int maxSize;
    int currentSize = 0;
    unordered_map<Tkey, Node *> cache;
    Node *head = nullptr, *tail = nullptr;
public:
    LRU(int maxSize) : maxSize(maxSize) {}
    void set(Tkey key, Tvalue value) {
        if (maxSize == 0) return;
        if (cache.count(key)) {
            get(key);
            tail->data = value;
        } else {
            if (tail) {
                tail->next = new Node (value);
                cache[key] = tail->next;
                tail->next->prev = tail;
                tail = tail->next;
                if (currentSize == maxSize) {
                    Node *temp = head;
                    head = head->next;
                    head->prev = nullptr;
                    delete temp;
                } else if (currentSize < maxSize) {
                    currentSize++;
                }
            } else {
                head = tail = new Node (value);
                cache[key] = head;
                currentSize++;
            }
        }

    }
    Tvalue get(Tkey key) {
        if (maxSize == 0) return 0;
        if (cache.count(key) == 0) return 0;
        Node *node = cache[key];
        if (node == tail) {
            return node->data;
        }
        else if (node == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (node != head) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        tail->next = node;
        node->prev = tail;
        node->next = nullptr;
        tail = node;
        return node->data;
    }
};

int main() {
    LRU<int, int> lru(3);
    lru.set(1, 11);
    lru.set(2, 22);
    lru.set(3, 33);
    lru.set(1, 111);
    lru.set(4, 44);

    cout << lru.get(1) << endl;
    cout << lru.get(2) << endl;
    cout << lru.get(3) << endl;
    cout << lru.get(4) << endl;


    return 0;
}