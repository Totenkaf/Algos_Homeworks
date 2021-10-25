#include <iostream>
//#include <fstream>

struct CAVLNode {
	int key;
	int height;
	CAVLNode* left;
	CAVLNode* right;
	int sum;

	CAVLNode(int k): key(k), left(NULL), right(NULL), height(1), sum(1) {;}
};

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

int height(CAVLNode* p) { // безопасное получение высоты дерева
	return p ? p->height : 0;
}

int sum(CAVLNode* p) {
	return p ? p->sum : 0;
}

CAVLNode* findNode(CAVLNode *node, size_t num){
    size_t pos = sum(node->left);
    if (pos == num) return node;
    else{
        if (pos > num) return findNode(node->left, num);
        else return findNode(node->right, num - sum(node->left) - 1);
    }
}

int find(CAVLNode* node, int key) {
    if (!node)
        return NULL;

    if (key < node->key) {
        return findAux(key, node->left);
    } else if (key > node->key) {
        return findAux(key, node->right);
    }
    return node->value;
}

CAVLNode* insert(int key, CAVLNode* node) {
    if (!node) {
        nodes_count++;
        return new Node(key);
    }

    int res = comp(key, node->key);
    if (res == 1) {
        node->left = insert_aux(key, node->left);
    } else if (res == -1) {
        node->right = insert_aux(key, node->right);
    }

    return balance(node);
}

    Node* erase_aux(const int& key, Node* node) {
        if (!node) {
            return NULL;
        }

        int res = comp(key, node->key);
        if (res == 1) {
            node->left = erase_aux(key, node->left);
        } else if (res == -1) {
            node->right = erase_aux(key, node->right);
        } else {
            nodes_count--;

            Node* left = node->left;
            Node* right = node->right;

            delete node;

            if (!right) {
                return left;
            }

            if (left == NULL || right->height >= left->height) {
                Node *min_node = find_min(right);
                min_node->right = remove_min(right);
                min_node->left = left;

                return balance(min_node);
            } else {
                Node *max_node = find_max(left);
                max_node->left = remove_max(left);
                max_node->right = right;
                return balance(max_node);
            }
        }

        return balance(node);
    }

    Node* find_min(Node* node) {
        if (!node->left) {
            return node;
        }
        return find_min(node->left);
    }

    Node * find_max(Node* node){
        if (!node->right) {
            return node;
        }
        return find_max(node->right);
    }

    Node* remove_max(Node* node) {
        if (!node->right) {
            return node->left;
        }
        node->right = remove_max(node->right);
        return balance(node);
    }

    Node* remove_min(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = remove_min(node->left);
        return balance(node);
    }

    void fix_height(Node* node) {
        if (!node) {
            return;
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;
        node->sum = sum(node->left) + sum(node->right) + 1;
    }

    uint8_t bfactor(Node* node) {
        return height(node->right) - height(node->left);
    }

    Node* balance(Node* node) {
        fix_height(node);

        int bf = bfactor(node);
        if (bf == 2) {
            if (bfactor(node->right) < 0)  {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        } else if (bf == -2) {
            if (bfactor(node->left) > 0)  {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }

    Node* rotate_left(Node* p) {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        fix_height(p);
        fix_height(q);
        return q;
    }

    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        size_t sum = this->sum(p);
        fix_height(p);
        fix_height(q);
        return q;
    }

    Node* root;
    size_t nodes_count;

};


size_t find_place(int key, CAVLNode &tree ){
    typename AVLTree<int, Comparator>::Node* node;
    node = tree.get_root();
    if (!node){
        return -1;
    }
    size_t place = 0;
    while (node) {
        int res = tree.comp(key, node->key);
        if (res == 1) {
            node = node->left;
        } else if (res == -1) {
            place = place + tree.sum(node->left) + 1;
            node = node->right;
        } else {
            place = place + tree.sum(node->right);
            return place;
        }
    }
}

int main() {
    //std::ifstream answers("4_test7_answ");
    //std::ifstream asserts("4_test7");

    size_t N;
    //asserts >> N;
    std::cin >> N;

    int num, stat, answer;
    //answers >> answer;
    //asserts >> num >> stat;
    std::cin >> cmnd >> num;
    CAVLNode* head = new struct CAVLNode(num);
    //std::cout << sortedint(head, stat) << " ";
    print(head);
	for (size_t i = 0; i < N-1; i++) {
        //answers >> answer;
        //asserts >> cmnd >> num;

        std::cin >> num >> stat;
        if (cmnd == 1)
            insert(head, key);
            std::cout << find_place(head, key) << std::endl;
        else {
            int k = find_node(head, key)->key;
            erase(tree, k);
        }
        /*
        fixall(head);
        std::cout << i << ": ";
        print(head);
        if (sortedint(head, stat) != answer) {
            std::cout << "Command: " << num << " " << stat << std::endl;
            std::cout << "Id: " << i << ". Answer is: " << sortedint(head, stat) << " but must be: " << answer << std::endl;
        }
		//std::cout << sortedint(head, stat) << " ";
		*/
	}

	del(head);
	return 0;
}

