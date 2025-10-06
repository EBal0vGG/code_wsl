#include <iostream>

struct Node {
    Node* parent;
    Node* left;
    Node* right;
};

// Function to get depth of a node from root
int getDepth(Node* node) {
    int depth = 0;
    while (node->parent != nullptr) {
        depth++;
        node = node->parent;
    }
    return depth;
}

// Function to move a node up by k levels
Node* moveUp(Node* node, int k) {
    while (k > 0) {
        node = node->parent;
        k--;
    }
    return node;
}

Node* lca(Node* a, Node* b) {
    if (a == nullptr || b == nullptr) return nullptr;
    
    // Get depths of both nodes
    int depthA = getDepth(a);
    int depthB = getDepth(b);
    
    // Move the deeper node up until both nodes are at the same level
    if (depthA > depthB) {
        a = moveUp(a, depthA - depthB);
    } else if (depthB > depthA) {
        b = moveUp(b, depthB - depthA);
    }
    
    // Move both nodes up until they meet
    while (a != b) {
        a = a->parent;
        b = b->parent;
    }
    
    return a;
}

// Helper function to create a test tree
Node* createTestTree() {
    Node* root = new Node{nullptr, nullptr, nullptr};
    Node* left = new Node{root, nullptr, nullptr};
    Node* right = new Node{root, nullptr, nullptr};
    root->left = left;
    root->right = right;
    
    Node* leftLeft = new Node{left, nullptr, nullptr};
    left->left = leftLeft;
    
    return root;
}

int main() {
    // Create a test tree
    Node* root = createTestTree();
    
    // Test LCA
    Node* a = root->left->left;  // leftLeft
    Node* b = root->right;       // right
    
    Node* result = lca(a, b);
    std::cout << "LCA is: " << (result == root ? "root" : "not root") << std::endl;
    
    // Clean up (in a real application, you'd want to properly delete all nodes)
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;
    
    return 0;
}
