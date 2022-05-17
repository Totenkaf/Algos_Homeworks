// Copyright 2022 by Artem Ustsov


// Задача 4_2. Найдите k-ю порядковую статистику в AVL дереве.
/*
 * Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел, 
 * а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, 
 * команда удаления числа A задается отрицательным числом “-A”. 
 * Запрос на получение k-ой порядковой статистики задается числом k. 
 * Требуемая скорость выполнения запроса - O(log n).
 */

#include <iostream>

template <typename T, typename Comparator=std::less<T>>
class AvlTree {
private:
    struct Node {
        Node(const T& key) 
        : key(key), left(nullptr), right(nullptr), height(1), count(1)
        {}
        T key;
        Node* left;
        Node* right;
        uint8_t height; // микрооптимизация, так как высота дерева ограничена сверху log(N)
        size_t count; // число узлов в дереве с корнем в данной вершине
    };
    Node* root;

    Node* add_internal(Node* node, const T& key, Comparator cmp = Comparator());
    Node* delete_internal(Node* node, const T& key, Comparator cmp = Comparator());

    Node* do_balance(Node* node);
    int getBalance(Node* node);

    uint8_t get_height(Node* node);
    size_t get_count(Node* node);

    void fix_height(Node* node);
    void fix_count(Node* node);

    std::pair<Node*, Node*> find_and_remove_min(Node* node);

    Node* do_left_rotate(Node* node);
    Node* do_right_rotate(Node* node);

    void destroy_tree(Node* node);
public:
    AvlTree() : root(nullptr) {}
    ~AvlTree() {destroy_tree(root);}

    void add(const T& key);
    bool has(const T& key, Comparator cmp = Comparator());
    void delete_at(const T& key);

    T find_kth_statistic(int k, Comparator cmp = Comparator());
};

// рекурсивно, так как дерево сбалансировано и глубина не бесконечна
template <typename T, typename Comparator>
void AvlTree<T, Comparator>::destroy_tree(Node* node) {
    if (!node) { // обработка nullptr для избежания segmentation fault
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
    return;
}

template <typename T, typename Comparator>
bool AvlTree<T, Comparator>::has(const T& key, Comparator cmp) {
    Node *tmp = root;
    while (tmp) {
        if (tmp->key == key) {
            return true;
        }
        else if (cmp(tmp->key, key)) {
            tmp = tmp->right;
        }
        else {
            tmp = tmp->left;
        }
    }
    return false;
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::add(const T& key) {
    root = add_internal(root, key);
    return;
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node* AvlTree<T, Comparator>::add_internal(Node* node, const T& key, Comparator cmp) {
    if (!node) {
        return new Node(key);
    }
    // наивное сравнение, пробрасываем в левое поддерево, так как std::less
    if (cmp(key, node->key)) {
        node->left = add_internal(node->left, key);
    }
    else { // иначе пробрасываем в правое поддерево
        node->right = add_internal(node->right, key);
    }
    return do_balance(node); // подняться от листа к корню и проверить дисбалансы высот
}


template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node* AvlTree<T, Comparator>::delete_internal(Node* node, const T& key, Comparator cmp) {
    if (!node) { // нода пустая, удалять нечего
        return nullptr;
    }
    if (cmp(node->key, key)) { // node->key < key, наивное сравнение
        node->right = delete_internal(node->right, key);
    }
    else if (node->key != key) { 
        node->left = delete_internal(node->left, key);
    }
    else {
        Node *left = node->left;
        Node *right = node->right;
        delete node;

        if (!right) { // проверка на оставшиеся потомки
            return left;
        }  
        std::pair<Node*, Node*> min_pair = find_and_remove_min(right);
        Node* min = min_pair.second;
        min->right = min_pair.first;
        min->left = left;
        return do_balance(min);
    }
    return do_balance(node);
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::delete_at(const T& key) {
    root = delete_internal(root, key);
    return;
}

template <typename T, typename Comparator>
std::pair<typename AvlTree<T, Comparator>::Node*, typename AvlTree<T, Comparator>::Node*> 
AvlTree<T, Comparator>::find_and_remove_min(Node* node) {
    if (node->left == nullptr) {
        return {node->right, node};
    }
    std::pair<Node*, Node*> min_pair = find_and_remove_min(node->left);
    node->left = min_pair.first;
    return {do_balance(node), min_pair.second};
}

// возвращает разницу высот поддеревьев 
template <typename T, typename Comparator>
int AvlTree<T, Comparator>::getBalance(Node* node) {
    return get_height(node->right) - get_height(node->left);
}

// общая функция добавления в дерево
template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node* AvlTree<T, Comparator>::do_balance(Node* node) {
    fix_height(node);
    fix_count(node);

    switch (getBalance(node)) {
        case 2: {
            // дисбаланс в правом поддереве
            if (getBalance(node->right) < 0) { 
                node->right = do_right_rotate(node->right); 
            }
            return do_left_rotate(node);
        }
        case -2: {
            // дисбаланс в левом поддереве
            if (getBalance(node->left) > 0) {
                node->left = do_left_rotate(node->left);
            }
            return do_right_rotate(node);
        }
        default: // дисбаланса нет
            return node;
    }
}

// получение высоты дерева из узла
template <typename T, typename Comparator>
uint8_t AvlTree<T, Comparator>::get_height(Node* node) {
    return node ? node->height : 0;
}

template <typename T, typename Comparator>
size_t AvlTree<T, Comparator>::get_count(Node* node) {
    return node ? node->count : 0;
}

// обновление значение высоты в текущем узле
template <typename T, typename Comparator>
void AvlTree<T, Comparator>::fix_height(Node* node) {
    node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
    return;
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::fix_count(Node* node) {
    node->count = get_count(node->left) + get_count(node->right) + 1;
    return;
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node* AvlTree<T, Comparator>::do_left_rotate(Node* node) {
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    fix_height(node);
    fix_count(node);

    fix_height(tmp);
    fix_count(tmp);
    return tmp;
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node* AvlTree<T, Comparator>::do_right_rotate(Node* node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    fix_height(node);
    fix_count(node);

    fix_height(tmp);
    fix_count(tmp);
    return tmp;
}

template <typename T, typename Comparator>
T AvlTree<T, Comparator>::find_kth_statistic(int k, Comparator cmp) {
    T result;
	Node* node = root;
	size_t index = get_count(root->left);
	while (index != k) {
		if (cmp(index, k)) { // k > index
			node = node->right;
			index += get_count(node->left) + 1;
		} else {
			node = node->left;
			index -= get_count(node->right) + 1;
		}
	}
	result = node->key;
    return result;
}

int main() {
    AvlTree<int> tree;
    size_t N = 0;
    std::cin >> N;
    for (size_t i = 0; i < N; ++i) {
        int value = 0;
        int k = 0;
        std::cin >> value >> k;
        if (value < 0) {
            tree.delete_at(-value);
        }
        else {
            tree.add(value);
        }
        std::cout << tree.find_kth_statistic(k) << std::endl;
    }
    return 0;
}


// Splitting by two find_min and remove_min
// Node* find_min(Node* node);
// Node* remove_min(Node* node);

// template <typename T, typename Comparator>
// typename AvlTree<T, Comparator>::Node* AvlTree<T, Comparator>::find_min(Node* node) {
//     while (node->left) {
//         node = node->left;
//     }
//     return node;
// }

// template <typename T, typename Comparator>
// typename AvlTree<T, Comparator>::Node* AvlTree<T, Comparator>::remove_min(Node* node) {
//     if (!node->left) {
//         return node->right;
//     }
//     node->left = remove_min(node->left);
//     return do_balance(node);
// }
