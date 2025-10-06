#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* prev;
    Node* next;
    Node(int v) : val(v), prev(nullptr), next(nullptr) {}
};

struct Queue {
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* mid  = nullptr;
    int sz = 0;

    void push_back(int x) {
        Node* node = new Node(x);
        if (!head) {
            head = tail = mid = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
            if (sz % 2 == 0) mid = mid->next;
        }
        sz++;
    }

    void push_middle(int x) {
        Node* node = new Node(x);
        if (!head) {
            head = tail = mid = node;
        } else {
            node->next = mid->next;
            node->prev = mid;
            if (mid->next) mid->next->prev = node;
            mid->next = node;
            if (mid == tail) tail = node;

            if (sz % 2 == 0) { 
                mid = mid->next;
            }
        }
        sz++;
    }

    int pop_front() {
        int res = head->val;
        Node* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = mid = nullptr;

        int old_size = sz;
        sz--;
        if (sz == 0) {
            mid = nullptr;
        } else if (old_size % 2 == 0) {
            if (mid && mid->next) mid = mid->next;
        }
        delete tmp;
        return res;
    }

    // void print() {
    //     cout << "Текущее состояние списка" << endl;
    //     Node* cur = head;
    //     while (cur) {
    //         if (cur != mid) {
    //             cout << cur->val << " ";
    //         } else {
    //             cout << "Mid-> " << cur->val << " ";
    //         }
    //         cur = cur->next;
    //     }
    //     cout << endl;
    // }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    Queue q;

    while (T--) {
        char type;
        cin >> type;
        if (type == '+') {
            int x; cin >> x;
            q.push_back(x);
        } else if (type == '*') {
            int x; cin >> x;
            q.push_middle(x);
        } else {
            cout << q.pop_front() << endl;
        }
    }

    return 0;
}