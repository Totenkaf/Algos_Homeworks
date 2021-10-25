/** Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”). **/

#include <iostream>
#include <vector>

// Узел двоичного дерева с данными типа int.
struct CBinaryNode{
    CBinaryNode(int val): data(val), left(NULL), right(NULL), parent(NULL) {;}
    int data;
    CBinaryNode* left = NULL; // NULL, если нет.
    CBinaryNode* right = NULL; // NULL, если нет.
    CBinaryNode* parent = NULL; // NULL, если корень.
};

// Вставка. Не указываем parent.
void add( CBinaryNode* node, int value, bool (*compare)(int, int) ) {
    CBinaryNode* parentNode;
    while ( node != NULL ) {
        parentNode = node;
        if (compare(node->data, value))
            node = node->left;
        else
            node = node->right;
    }
    node = new struct CBinaryNode(value);
    node->parent = parentNode;
    if (compare(parentNode->data, value))
        parentNode->left = node;
    else
        parentNode->right = node;
};

void print( CBinaryNode* node ) {
    std::vector<CBinaryNode*> nowNodes;
    std::vector<CBinaryNode*> nextNodes{node};
    do {
        nowNodes = nextNodes;
        nextNodes.clear();
        for (auto nnode: nowNodes) {
            if (nnode != NULL) {
                std::cout << nnode->data << " ";
                nextNodes.push_back(nnode->left);
                nextNodes.push_back(nnode->right);
            }
        }
        //std::cout << std::endl << "----" << std::endl;
    } while (nextNodes.size() != 0);
    //std::cout << std::endl;
}

void del( CBinaryNode* node ) {
    std::vector<CBinaryNode*> nowNodes;
    std::vector<CBinaryNode*> nextNodes{node};
    do {
        nowNodes = nextNodes;
        nextNodes.clear();
        for (auto nnode: nowNodes) {
            if (nnode != NULL) {
                nextNodes.push_back(nnode->left);
                nextNodes.push_back(nnode->right);
                delete nnode;
            }
        }
    } while (nextNodes.size() != 0);
}

bool isHigher(int a, int b) {
    return a > b;
}

int main() {
    size_t N;
    std::cin >> N;

    int num;
    std::cin >> num;
    CBinaryNode* head = new struct CBinaryNode(num);

    for (size_t i = 0; i < N - 1; i++) {
        std::cin >> num;
        add(head, num, isHigher);
        //print(head);
    }

    print(head);

    del(head);
    return 0;
}
