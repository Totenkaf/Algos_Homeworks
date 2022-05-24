// Copyright 2022 by Artem Ustsov

// Задача 3. Выведите элементы B-дерева по слоям.
/*
* Постройте B-дерево минимального порядка t и выведите его по слоям.
* В качестве ключа используются числа, лежащие в диапазоне 0..232 -1
*
* Требования: 
* B-дерево должно быть реализовано в виде шаблонного класса.
* Решение должно поддерживать передачу функции сравнения снаружи.
*
* Формат входных данных
* Сначала вводится минимальный порядок дерева t.
* Затем вводятся элементы дерева.
*
* Формат выходных данных
* Программа должна вывести B-дерево по слоям. Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.
* 
*/

#include <assert.h>
#include <iostream>
#include <queue>
#include <vector>

template <class T, class Comparator = std::less<T>>
class BTree {
public:
    BTree(const int& inp_t, const Comparator& cmp)
    : t(inp_t), cmp(cmp), root(nullptr), node_numbers(0)
    {}
    BTree(const BTree& tree) = delete;
    BTree &operator=(const BTree& root) = delete;
    ~BTree();

    void add(const T &key);
    void BFS_traverse(void (*visit)(const std::string& key)) const;

private:
    struct Node {
        Node()
        : is_leaf(true), key(0), children(0)
        {}
        Node(const Node& node) = delete;
        Node &operator=(const Node& node) = delete;
        ~Node();

        bool is_leaf;
        std::vector<T> key;
        std::vector<Node*> children;
    };

    Node *root;
    size_t t;
    Comparator cmp;
    size_t node_numbers;

    void split_child(Node* node, const size_t& index);
    void add_in_non_full(Node* node, const T& key);
};

template <class T, class Comparator>
BTree<T, Comparator>::Node::~Node() {
    for(Node* child : children){
        delete child;    
    }
}

template <class T, class Comparator>
BTree<T, Comparator>::~BTree() {
    if (root) {
        delete root;
    }
}

template <class T, class Comparator>
void BTree<T, Comparator>::split_child(Node* node, const size_t& index) { 
    Node* children = node->children[index];
    T mid = children->key[t - 1]; // медианный ключ

    Node* temp = new Node();
    temp->is_leaf = children->is_leaf;

    // перемещаем вторую половину объектов в temp (без медианного ключа) через итератор
    temp->key = std::vector<T>(children->key.begin() + t,children->key.end());
    
    children->key.resize(t - 1); // удаляем медианный ключ.
    if(!(children->is_leaf)) {
        temp->children = std::vector<Node*>(children->children.begin() + t, children->children.end());
        children->children.resize(t);
    }

    node->key.resize(node->key.size() + 1); // увеличиваем размер векторов на 1
    node->children.resize(node->children.size() + 1);

    for(size_t i = (node->children.size() - 1); i > index + 1; --i) {
        node->children[i] = node->children[i - 1];
    };
    node->children[index + 1] = temp;

    for(size_t i = (node->key.size() - 1); i > index; --i) {
        node->key[i] = node->key[i - 1];
    };
    node->key[index] = mid;
    return;
}

template <class T, class Comparator>
void BTree<T, Comparator>::add(const T& key) {
    if(root == nullptr) {
        root = new Node();    
    }
    // если нода полная, делаем разбиение
    if(root->key.size() == (2 * t - 1)) {
        Node* temp = new Node();
        temp->is_leaf = false;
        temp->Node::children.push_back(root);
        root = temp;
        split_child(root, 0);
    }
    add_in_non_full(root, key);
    return;
}

template <class T, class Comparator>
void BTree<T, Comparator>::add_in_non_full(Node* node, const T& key) {
    while(!(node->is_leaf)) {
        size_t i = node->children.size() - 1;
        while(i > 0 && cmp(key, node->key[i - 1])) {
            i--;
        }
        if (node->children[i]->key.size() == 2 * t - 1) {
            split_child(node, i);
            if (key > node->key[i]) { // если ключ больше медианного
                i++;
            }
        }        
        node = node->children[i];
    }
    node->key.resize(node->key.size() + 1);
    size_t i = node->key.size() - 1;

    while(i > 0 && cmp(key, node->key[i - 1])) {
        node->key[i] = node->key[i - 1];
        i--;
    }
    node->key[i] = key;
    return;
}

template <class T, class Comparator>
void BTree<T, Comparator>::BFS_traverse(void (*visit)(const std::string& key)) const {
    std::queue<Node*> children_queue;
    children_queue.push(root);
    size_t endl_pos = children_queue.size();

    while(children_queue.size() > 0) {
        Node* node = children_queue.front();
        children_queue.pop();
        for(size_t i = 0; i < node->key.size(); ++i) {
            visit(std::to_string(node->key[i]) + " ");
        }
        for(size_t i = 0; i < node->children.size(); ++i) {
            children_queue.push(node->children[i]);
        }
        endl_pos--;
        if(endl_pos == 0) {
            visit(std::string("\n"));
            endl_pos = children_queue.size();
        }
    }
    return;
}


int main(int argc, char const *argv[]) {
    std::less<int> cmp;
    int t = 0;
    std::cin >> t;

    BTree<int> btree(t, cmp);
    int key = 0;
    while (std::cin >> key) {
        btree.add(key);
    }

    btree.BFS_traverse([](const std::string& key) {std::cout << key;}); 
    return 0;
}
