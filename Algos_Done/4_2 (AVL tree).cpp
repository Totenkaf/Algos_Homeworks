/**ƒано число N и N строк.  ажда€ строка содержащит команду
добавлени€ или удалени€ натуральных чисел,
а также запрос на получение k-ой пор€дковой статистики.
 оманда добавлени€ числа A задаетс€ положительным числом A,
команда удалени€ числа A задаетс€ отрицательным числом У-AФ.
«апрос на получение k-ой пор€дковой статистики задаетс€ числом k.
“ребуема€ скорость выполнени€ запроса - O(log n).**/

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

struct CAVLNode {
	int key;
	int height;
	CAVLNode* left;
	CAVLNode* right;
	int childs;

	CAVLNode(int k): key(k), left(NULL), right(NULL), height(1), childs(1) {;}
};

int height(CAVLNode* p) { // безопасное получение высоты дерева
	return p ? p->height : 0;
}

int childs(CAVLNode* p) {
	return p ? p->childs : 0;
}

void fixheight(CAVLNode* p) { // суммирование высот поддеревьев
    if (!p)
        return;
	int hl;
	int hr;
	hl = height(p->left);
	hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}
void fixchilds(CAVLNode* p) {
    if (!p)
        return;
	p->childs = childs(p->left) + childs(p->right) + 1;
}
void fixall(CAVLNode* node) {
    fixheight(node);
    fixchilds(node);
}

void rotateright(CAVLNode*& p) { // правый поворот вокруг p
	CAVLNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixall(p);
	fixall(q);
	p = q;
}

void rotateleft(CAVLNode*& q) { // левый поворот вокруг q
	CAVLNode* p = q->right;
	q->right = p->left;
	p->left = q;
	fixall(q);
	fixall(p);
	q = p;
}

void balance(CAVLNode*& p) { // балансировка узла p
    if (!p)
        return;
    fixall(p);
	if (height(p->right) - height(p->left) == 2) {
		if (height(p->right->right) - height(p->right->left) < 0) {
			rotateright(p->right);
		}
		rotateleft(p);
	}
	if (height(p->right) - height(p->left) == -2) {
		if ((height(p->left->right) - height(p->left->left)) > 0) {
			rotateleft(p->left);
		}
		rotateright(p);
	}
}

void add(CAVLNode*& p, int k) { // вставка ключа k в дерево с корнем p
	if (!p)
        p = new CAVLNode(k);
	else if (k < p->key)
		add(p->left, k);
	else
		add(p->right, k);
	balance(p);
	fixall(p);
}

CAVLNode* find(CAVLNode* node, int value) {
    std::vector<CAVLNode*> nowNodes;
    std::vector<CAVLNode*> nextNodes{node};
    do {
        nowNodes = nextNodes;
        nextNodes.clear();
        for (auto nnode: nowNodes) {
            if (nnode != NULL) {
                if (nnode->key == value)
                    return nnode;
                nextNodes.push_back(nnode->left);
                nextNodes.push_back(nnode->right);
            }
        }
    } while (nextNodes.size() != 0);
    return NULL;
}

void deleteNode(CAVLNode*& node) {
    if (!node)
        return;
    CAVLNode* r = node->right;
    CAVLNode* l = node->left;

    if (!l) {
        delete node;
        node = r;
    } else if (!r) {
        delete node;
        node = l;
    } else {
		CAVLNode* parent = node;
		CAVLNode* minNode = r;
		while (minNode->left) {
			parent = minNode;
			minNode = minNode->left;
		}
		node->key = minNode->key;
		if (parent->left == minNode)
            parent->left = minNode->right;
        else
            parent->right = minNode->right;
		delete minNode;
		fixall(parent);
	}
	balance(node);
}

/*void remove(CAVLNode*& node, int value) { // удаление ключа k из дерева node
    if (!node)
        return;
    if (node->key == value) {
        deleteNode(node);
        return;
    }
    if (node->key > value)
        remove (node->left, value);
    else
        remove (node->right, value);
    balance(node);
    return;
}*/

void remove(CAVLNode*& q, int k, CAVLNode* parent = NULL) {
    if (!q)
        return;

    if (k < childs(q->right))
		remove(q->right, k, q);
	else if (k > childs(q->right))
		remove(q->left, k - childs(q->right) - 1, q);
    else {
        deleteNode(q);
    }

    /*if (parent) {
        balance(parent->left);
        balance(parent->right);
    }*/
    //balance(parent);
    balance(q);
    return;
}

/*CAVLNode* findmin(CAVLNode* p) { // поиск узла с минимальным ключом в дереве p
    if (p->left)
        return findmin(p->left);
    return p;
}

CAVLNode* removemin(CAVLNode* p) { // удаление узла с минимальным ключом из дерева p
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	balance(p);
	return p;
}

void remove(CAVLNode*& p, int k) { // удаление ключа k из дерева p
	if( !p )
        return;

	if( k > p->key )
		remove(p->left,k);
	else if( k < p->key )
		remove(p->right,k);
	else { //  k == p->key
		CAVLNode* q = p->left;
		CAVLNode* r = p->right;
		delete p;
		if( !r ) {
            p = q;
            return;
		}
		CAVLNode* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}*/

int sortedKey(const CAVLNode* q, int k, int childs) {
    if (!q)
        return -1;

    if (k < q->key)
        return sortedKey(q->left, k, childs+height(q->right)+1);
    else if (k > q->key)
		return sortedKey(q->right, k, childs);
	else
		return childs+height(q->right);
}

void print( CAVLNode* node ) {
    std::vector<CAVLNode*> nowNodes;
    std::vector<CAVLNode*> nextNodes{node};
    do {
        nowNodes = nextNodes;
        nextNodes.clear();
        int i = 0;
        for (auto nnode: nowNodes) {
            if (i % 2 == 0)
                std::cout << "|";
            i++;
            if (nnode != NULL) {
                std::cout << std::setw(2) << nnode->key << "," << std::setw(2) << nnode->childs << " ";
                nextNodes.push_back(nnode->left);
                nextNodes.push_back(nnode->right);
            } else
                std::cout << "..,.." << " ";
        }
        std::cout << std::endl << "----------------" << std::endl;
    } while (nextNodes.size() != 0);
    std::cout << std::endl;
}

void del(const CAVLNode* node) {
    std::vector<const CAVLNode*> nowNodes;
    std::vector<const CAVLNode*> nextNodes{node};
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


int main() {
    //std::ifstream answers("4_test7_answ");
    //std::ifstream asserts("4_test7");

    size_t N;
    //asserts >> N;
    std::cin >> N;

    int num, cmnd, answer;
    //answers >> answer;
    //asserts >> num >> stat;
    std::cin >> cmnd >> num;
    CAVLNode* head = new struct CAVLNode(num);
    std::cout << sortedKey(head, num, 0) << " ";
    //print(head);
	for (size_t i = 0; i < N-1; i++) {
        //answers >> answer;
        //asserts >> num >> stat;

        std::cin >> cmnd >> num;
        if (cmnd == 1) {
            add(head, num);
            std::cout << sortedKey(head, num, 0) << std::endl;
        } else {
            remove(head, num);
        }
        fixall(head);
        //std::cout << i << ": ";

        /*if (sortedKey(head, stat) != answer) {
            std::cout << "Command: " << num << " " << stat << std::endl;
            std::cout << "Id: " << i << ". Answer is: " << sortedKey(head, stat) << " but must be: " << answer << std::endl;
        }*/
		//print(head);
	}

	del(head);
	return 0;
}
