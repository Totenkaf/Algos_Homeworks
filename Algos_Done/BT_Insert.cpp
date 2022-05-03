#include <iostream>



struct CBinaryNode{
    CBinaryNode(int val): data(val), left(NULL), right(NULL), parent(NULL) {;}
    int data;
    CBinaryNode* left = NULL; // NULL, если нет.
    CBinaryNode* right = NULL; // NULL, если нет.
    CBinaryNode* parent = NULL; // NULL, если корень.
};


void Insert(CBinaryNode*& node, int value) {
    if (node == nullptr) {
        node = new CBinaryNode(value);
        return;
    }
    if (node->data > value) {
        Insert(node->left, value);
    }
    else {
        Insert(node->right, value);
    }
}



int main() {

    size_t N;
    std::cin >> N;

    int num;
    std::cin >> num;
    CBinaryNode* head = nullptr;

    for (size_t i = 0; i < N - 1; i++) {
        std::cin >> num;
        Insert(head, num);
    }
    return 0;
}