#include "list.h"
#include <stdexcept>
#include <unordered_set>
#include <vector>

List::List() {
    head = nullptr;
    tail = nullptr;
    _size = 0;
}

List::List(const List& other) {
    head = tail = nullptr;
    _size = 0;
    Node* cur = other.head;
    while (cur) {
        push_back(cur->value);
        cur = cur->next;
    }
}

List::List(std::vector<int> array) {
    head = tail = nullptr;
    _size = 0;
    for (int v : array) {
        push_back(v);
    }
}

List::~List() {
    clear();
}

int List::front() {
    if (empty()) {
        throw std::runtime_error("Accessing empty list");
    }
    return head->value;
}

int List::back() {
    if (empty()) {
        throw std::runtime_error("Accessing empty list");
    }
    return tail->value;
}

void List::push_back(int value) {
    Node* node = new Node(value);
    if (empty()) {
        head = tail = node;
    } else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    ++_size;
}

void List::push_front(int value) {
    Node* node = new Node(value);
    if (empty()) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    ++_size;
}

void List::insert(Node* pos, int value) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    Node* cur = head;
    bool found = false;
    while (cur) {
        if (cur == pos) { found = true; break; }
        cur = cur->next;
    }
    if (!found) {
        throw std::runtime_error("Incorrect position!");
    }

    if (pos == tail) {
        push_back(value);
        return;
    }

    Node* node = new Node(value);
    Node* nxt = pos->next;
    node->prev = pos;
    node->next = nxt;
    pos->next = node;
    if (nxt) nxt->prev = node;
    ++_size;
}

void List::pop_front() {
    if (empty()) {
        throw std::runtime_error("Deleting in empty list");
    }
    Node* to_delete = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete to_delete;
    --_size;
}

void List::pop_back() {
    if (empty()) {
        throw std::runtime_error("Deleting in empty list");
    }
    Node* to_delete = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete to_delete;
    --_size;
}

void List::erase(Node* pos) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    Node* cur = head;
    bool found = false;
    while (cur) {
        if (cur == pos) { found = true; break; }
        cur = cur->next;
    }
    if (!found) {
        throw std::runtime_error("Incorrect position!");
    }

    if (pos == head) {
        pop_front();
        return;
    }
    if (pos == tail) {
        pop_back();
        return;
    }
    Node* p = pos->prev;
    Node* n = pos->next;
    if (p) p->next = n;
    if (n) n->prev = p;
    delete pos;
    --_size;
}

void List::clear() {
    if (!head) {
        head = tail = nullptr;
        _size = 0;
        return;
    }

    if (!check_cycle()) {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    } else {
        std::unordered_set<Node*> visited;
        Node* cur = head;
        while (cur && visited.find(cur) == visited.end()) {
            visited.insert(cur);
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    head = tail = nullptr;
    _size = 0;
}


void List::reverse() {
    if (empty() || head == tail) return;

    Node* cur = head;
    while (cur) {
        Node* tmp = cur->next;
        cur->next = cur->prev;
        cur->prev = tmp;
        cur = tmp;
    }
    Node* tmp = head;
    head = tail;
    tail = tmp;
}

void List::remove_duplicates() {
    if (empty() || head == tail) return;
    std::unordered_set<int> seen;
    Node* cur = head;
    while (cur) {
        if (seen.find(cur->value) != seen.end()) {
            Node* to_delete = cur;
            Node* nxt = cur->next;
            Node* prv = cur->prev;
            if (prv) prv->next = nxt;
            if (nxt) nxt->prev = prv;
            if (to_delete == head) head = nxt;
            if (to_delete == tail) tail = prv;
            cur = nxt;
            delete to_delete;
            --_size;
        } else {
            seen.insert(cur->value);
            cur = cur->next;
        }
    }
}

void List::replace(int old_value, int new_value) {
    Node* cur = head;
    while (cur) {
        if (cur->value == old_value) cur->value = new_value;
        cur = cur->next;
    }
}

void List::copy(const List& other) {
    if (&other == this) return;
    clear();
    Node* cur = other.head;
    while (cur) {
        push_back(cur->value);
        cur = cur->next;
    }
}

void List::merge(const List& other) {
    Node* cur = other.head;
    while (cur) {
        push_back(cur->value);
        cur = cur->next;
    }
}

bool List::check_cycle() const {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const {
    return _size == 0;
}
