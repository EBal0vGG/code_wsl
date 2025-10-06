#include <iostream>
#include <vector>
#include <set>
#include <functional>
using namespace std;

struct Node {
    char letter;
    Node* left;
    Node* right;
    
    Node(char c) : letter(c), left(nullptr), right(nullptr) {}
};

// Function to get set of letters in a subtree
set<char> getSubtreeLetters(Node* root) {
    set<char> result;
    if (!root) return result;
    
    result.insert(root->letter);
    set<char> leftSet = getSubtreeLetters(root->left);
    set<char> rightSet = getSubtreeLetters(root->right);
    
    result.insert(leftSet.begin(), leftSet.end());
    result.insert(rightSet.begin(), rightSet.end());
    
    return result;
}

// Function to find a pair of equivalent vertices
pair<Node*, Node*> findEquivalentVertices(Node* root) {
    if (!root) return {nullptr, nullptr};
    
    // Check current node with all other nodes
    set<char> currentSet = getSubtreeLetters(root);
    
    // Helper function to check a node against all other nodes
    function<pair<Node*, Node*>(Node*, Node*)> checkNode = 
        [&](Node* current, Node* other) -> pair<Node*, Node*> {
        if (!other) return {nullptr, nullptr};
        
        if (current != other) {
            set<char> otherSet = getSubtreeLetters(other);
            if (currentSet == otherSet) {
                return {current, other};
            }
        }
        
        auto leftResult = checkNode(current, other->left);
        if (leftResult.first) return leftResult;
        
        auto rightResult = checkNode(current, other->right);
        if (rightResult.first) return rightResult;
        
        return {nullptr, nullptr};
    };
    
    // Check current node against all other nodes
    auto result = checkNode(root, root);
    if (result.first) return result;
    
    // Recursively check left and right subtrees
    auto leftResult = findEquivalentVertices(root->left);
    if (leftResult.first) return leftResult;
    
    auto rightResult = findEquivalentVertices(root->right);
    if (rightResult.first) return rightResult;
    
    return {nullptr, nullptr};
}

// Function to build a tree from input
Node* buildTree() {
    char c;
    cin >> c;
    if (c == '.') return nullptr;
    
    Node* root = new Node(c);
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

int main() {
    Node* root = buildTree();
    
    auto result = findEquivalentVertices(root);
    if (result.first) {
        cout << "Found equivalent vertices with letters: " 
             << result.first->letter << " and " 
             << result.second->letter << endl;
    } else {
        cout << "No equivalent vertices found" << endl;
    }
    
    return 0;
}
