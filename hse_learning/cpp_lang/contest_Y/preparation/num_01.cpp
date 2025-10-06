#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

class SegTree {
    struct Node {
        long long product;
        int add;
        Node() : product(1), add(0) {}
    };

    int size;
    std::vector<Node> tree;
    std::vector<int> initial;

    void build(int node, int left, int right) {
        if (left == right) {
            if (left < initial.size()) {
                tree[node].product = initial[left] % MOD;
            }
            return;
        }
        int mid = (left + right) / 2;
        build(2*node, left, mid);
        build(2*node+1, mid+1, right);
        tree[node].product = (tree[2*node].product * tree[2*node+1].product) % MOD;
    }

    void push(int node, int left, int right) {
        if (tree[node].add == 0) return;

        // Применяем добавку к произведению: (a+add) * (b+add) = a*b + add*(a+b) + add²
        // Но проще пересчитать для листьев
        if (left == right) {
            tree[node].product = (tree[node].product + tree[node].add) % MOD;
            tree[node].add = 0;
            return;
        }

        // Проталкиваем добавку детям
        int mid = (left + right) / 2;
        tree[2*node].add = (tree[2*node].add + tree[node].add) % MOD;
        tree[2*node+1].add = (tree[2*node+1].add + tree[node].add) % MOD;
        tree[node].add = 0;

        // Пересчитываем произведение
        push(2*node, left, mid);
        push(2*node+1, mid+1, right);
        tree[node].product = (tree[2*node].product * tree[2*node+1].product) % MOD;
    }

public:
    SegTree(const std::vector<int>& data) : initial(data) {
        size = 1;
        while (size < data.size()) size <<= 1;
        tree.resize(2*size);
        build(1, 0, size-1);
    }

    void rangeAdd(int l, int r, int val = 1) {
        rangeAdd(1, 0, size-1, l, r, val);
    }

    void rangeAdd(int node, int node_l, int node_r, int l, int r, int val) {
        push(node, node_l, node_r);
        if (r < node_l || l > node_r) return;
        if (l <= node_l && node_r <= r) {
            tree[node].add = (tree[node].add + val) % MOD;
            push(node, node_l, node_r);
            return;
        }
        int mid = (node_l + node_r) / 2;
        rangeAdd(2*node, node_l, mid, l, r, val);
        rangeAdd(2*node+1, mid+1, node_r, l, r, val);
        tree[node].product = (tree[2*node].product * tree[2*node+1].product) % MOD;
    }

    long long rangeProduct(int l, int r) {
        return rangeProduct(1, 0, size-1, l, r);
    }

    long long rangeProduct(int node, int node_l, int node_r, int l, int r) {
        push(node, node_l, node_r);
        if (r < node_l || l > node_r) return 1;
        if (l <= node_l && node_r <= r) return tree[node].product;
        int mid = (node_l + node_r) / 2;
        return (rangeProduct(2*node, node_l, mid, l, r) *
                rangeProduct(2*node+1, mid+1, node_r, l, r)) % MOD;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    SegTree st(a);

    int q;
    std::cin >> q;
    std::vector<long long> answers;
    answers.reserve(q);

    while (q--) {
        int type, l, r;
        std::cin >> type >> l >> r;
        --l; --r;

        if (type == 0) {
            st.rangeAdd(l, r);
        } else {
            answers.push_back(st.rangeProduct(l, r));
        }
    }

    for (long long ans : answers) {
        std::cout << ans << '\n';
    }

    return 0;
}