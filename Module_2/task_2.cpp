// Copyright 2022 by Artem Ustsov

// Задача 2_2. Выведите элементы в порядке pre-order (сверху вниз).


/*
 * Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 *
 * Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
 *
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

template <typename T, typename Comparator = std::less<T>>
class TBinaryTree {
public:
    TBinaryTree()
    : root(nullptr)
    {}

    ~TBinaryTree();

    void add(const T& new_key);
    void pre_order_traverse(void (*visit)(const T& key)) const;

private:
    struct TreeNode {
        T key;
        TreeNode* right_child;
        TreeNode* left_child;

        explicit TreeNode(const T& key_)
        : key(key_), right_child(nullptr), left_child(nullptr)
        {}

        ~TreeNode() = default;
    };

    TreeNode *root;
    Comparator cmp;
    void delete_node(TreeNode* node);
};

template <typename T, typename Comparator>
TBinaryTree<T, Comparator>::~TBinaryTree() {
    delete_node(root);
}

template <typename T, typename Comparator> /*POST ORDER TRAVERSAL*/
void TBinaryTree<T, Comparator>::delete_node(TreeNode* node) {
    if(node == nullptr) {
        return;
    }
    std::stack<TreeNode*> delete_stack_1;
    std::stack<TreeNode*> delete_stack_2;

    delete_stack_1.push(node);
    while(!delete_stack_1.empty()) {
        delete_stack_2.push(delete_stack_1.top());
        delete_stack_1.pop();
        if(delete_stack_2.top() == nullptr) {
            continue;
        }
        delete_stack_1.push(delete_stack_2.top()->left_child);
        delete_stack_1.push(delete_stack_2.top()->right_child);
    }
    
    while (!delete_stack_2.empty()) {
        delete delete_stack_2.top();
        delete_stack_2.pop();
    }
}

template <typename T, typename Comparator>
void TBinaryTree<T, Comparator>::pre_order_traverse(void (*visit)(const T& key)) const {
    std::stack<TreeNode*> tree_stack;
    TreeNode* current_root = root;
 
    while (!tree_stack.empty() || current_root != nullptr) {
        if (current_root) {
            visit(current_root->key);

            if (current_root->right_child) {
                tree_stack.push(current_root->right_child);
            }
            current_root = current_root->left_child;
        }
        else {
            current_root = tree_stack.top();
            tree_stack.pop();
        }
    }
    return;
}


template <typename T, typename Comparator>
void TBinaryTree<T, Comparator>::add(const T& new_key) {
    TreeNode* new_node = new TreeNode(new_key);
    if(root == nullptr) {
        root = new_node;
        return;
    }
    TreeNode* next_node = root;

    while (true) {
        if (cmp(new_key, next_node->key)) {
            if (next_node->left_child != nullptr) {
                next_node = next_node->left_child;
                continue;
            }
            else {
                next_node->left_child = new_node;
                return;
            }
        }
        else {
            if (next_node->right_child != nullptr) {
                next_node = next_node->right_child;
                continue;
            }
            else {
                next_node->right_child = new_node;
                return;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    TBinaryTree<int> tree;
    int N = 0;
    std::cin >> N;

    for (size_t i = 0; i < N; ++i) {
        int key = 0;
        std::cin >> key;
        tree.add(key);
    }

    tree.pre_order_traverse([](const int& key) {std::cout << key << " ";});
    return 0;
}
