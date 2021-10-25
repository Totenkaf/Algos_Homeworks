/**���� ����� N < 10^6 � ������������������ ��� ����� ����� �� [-2^31, 2^31] ������ N.
��������� ��������� ������ �� N �����, ����������������� ������ ����� (Xi, Yi).
������ ���� ����� (Xi, Yi) ���������� ���� Xi � ��������� Yi � ���������� ������.
���������� ���� � ��������� ������ ���������� ������ ������� ���������, ������������� �� ������:
��� ���������� ���� (x, y) ���������� ����� �� ����� �� ���� P � ������� �����������.
����� �������� ��������� ��������� �� ����� x ���, ����� � ������ ��������� ��� ����� ������ x,
� �� ������ ������ ��� ����� x. ������������ ��� ������ �������� ��������� ��� ������ ���� (x, y).
����� ���� �������� �� ����� ���� P. ��������� ����� ������� ������ ������ �� ������ Xi.
������ ����� ���������� � ������ ���������. ��������� ���������� ����� � ����� ������� ����
����������� ������ � ���������� ����� � ����� ������� ���� �������� ������ ������.
������� �� �������. ������� ����� ���� ������������.**/

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

namespace BinaryTree {
    // ���� ��������� ������ � ������� ���� int.
    struct CBinaryNode{
        CBinaryNode(int val): data(val), left(NULL), right(NULL), parent(NULL) {;}
        int data;
        CBinaryNode* left = NULL; // NULL, ���� ���.
        CBinaryNode* right = NULL; // NULL, ���� ���.
        CBinaryNode* parent = NULL; // NULL, ���� ������.
    };

    // �������. �� ��������� parent.
    void add( CBinaryNode* node, int value ) {
        CBinaryNode* parentNode;
        while ( node != NULL ) {
            parentNode = node;
            if ( node->data > value )
                node = node->left;
            else
                node = node->right;
        }
        node = new struct CBinaryNode(value);
        node->parent = parentNode;
        if ( parentNode->data > value )
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
                    std::cout << std::setw(2) << nnode->data << " ";
                    nextNodes.push_back(nnode->left);
                    nextNodes.push_back(nnode->right);
                } else
                    std::cout << ".." << " ";
            }
            std::cout << std::endl << "------------" << std::endl;
        } while (nextNodes.size() != 0);
        std::cout << std::endl;
    }

    int count( CBinaryNode* node ) {
        std::vector<CBinaryNode*> nowNodes;
        std::vector<CBinaryNode*> nextNodes{node};
        int maxCount = 1, nowCount = 1;
        do {
            if (nowCount > maxCount)
                maxCount = nowCount;
            nowNodes = nextNodes;
            nextNodes.clear();
            nowCount = 0;
            for (auto nnode: nowNodes) {
                if (nnode != NULL) {
                    nowCount++;
                    nextNodes.push_back(nnode->left);
                    nextNodes.push_back(nnode->right);
                }
            }
        } while (nextNodes.size() != 0);
        return maxCount;
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
}

struct CTreapNode{
    int data;
    int priority;
    CTreapNode* left;
    CTreapNode* right;

    CTreapNode(int value, int priority): data(value), priority(priority), left(NULL), right(NULL) {;}
};

// ���������� ����������� ������ �� �����.
void split( CTreapNode* node, int value, CTreapNode*& left, CTreapNode*& right ) {
    if( node == NULL ) {
        left = right = NULL;
    } else if( node->data <= value ) {
        split( node->right, value, node->right, right );
        left = node;
    } else {
        split( node->left, value, left, node->left );
        right = node;
    }
}

void add(CTreapNode*& node, int value, int priority) {
    CTreapNode* nnode = node;
    CTreapNode* parent = NULL;
    while (nnode->priority > priority) {
        parent = nnode;
        if (nnode->data > value) {
            if (nnode->left == NULL) {
                nnode->left = new CTreapNode(value, priority);
                return;
            }
            nnode = nnode->left;
        } else {
            if (nnode->right == NULL) {
                nnode->right = new CTreapNode(value, priority);
                return;
            }
            nnode = nnode->right;
        }
    }

    CTreapNode *l, *r;
    split(nnode, value, l, r);
    nnode = new CTreapNode(value, priority);
    nnode->left = l;
    nnode->right = r;
    if (!parent)
        node = nnode;
    else if (parent->data > value)
        parent->left = nnode;
    else
        parent->right = nnode;
}

void del( CTreapNode* node ) {
    std::vector<CTreapNode*> nowNodes;
    std::vector<CTreapNode*> nextNodes{node};
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

void print( CTreapNode* node ) {
    std::vector<CTreapNode*> nowNodes;
    std::vector<CTreapNode*> nextNodes{node};
    do {
        nowNodes = nextNodes;
        nextNodes.clear();
        for (auto nnode: nowNodes) {
            if (nnode != NULL) {
                std::cout << std::setw(2) << nnode->data << ","<< std::setw(2) << nnode->priority << " ";
                nextNodes.push_back(nnode->left);
                nextNodes.push_back(nnode->right);
            } else
                std::cout << "..,.." << " ";
        }
        std::cout << std::endl << "----------------" << std::endl;
    } while (nextNodes.size() != 0);
    std::cout << std::endl;
}

int count( CTreapNode* node ) {
    std::vector<CTreapNode*> nowNodes;
    std::vector<CTreapNode*> nextNodes{node};
    int maxCount = 1, nowCount = 1;
    do {
        if (nowCount > maxCount)
            maxCount = nowCount;
        nowNodes = nextNodes;
        nextNodes.clear();
        nowCount = 0;
        for (auto nnode: nowNodes) {
            if (nnode != NULL) {
                nowCount++;
                nextNodes.push_back(nnode->left);
                nextNodes.push_back(nnode->right);
            }
        }
    } while (nextNodes.size() != 0);
    return maxCount;
}

int main() {
    size_t N;
    std::cin >> N;

    int num, priority;
    std::cin >> num >> priority;
    BinaryTree::CBinaryNode* binHead = new struct BinaryTree::CBinaryNode(num);
    CTreapNode* treapHead = new struct CTreapNode(num, priority);

    for (size_t i = 0; i < N - 1; i++) {
        std::cin >> num >> priority;
        BinaryTree::add(binHead, num);
        add(treapHead, num, priority);
        //BinaryTree::print(binHead);
        //std::cout << ": " <<  BinaryTree::count(binHead) << std::endl;
        //print(treapHead);

        //std::cout << ": " <<  count(treapHead) << std::endl;
        //std::cout << std::endl;
    }

    std::cout << -BinaryTree::count(binHead) + count(treapHead) << std::endl;

    BinaryTree::del(binHead);
    del(treapHead);
    return 0;
}
