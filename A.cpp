#include <iostream>

const int INF = 2e9 + 179;

using namespace std;

struct node {
    int key;
    int height;
    node* left;
    node* right;

    node(int k) {
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVL_tree {
private:
    int height(node*);
    int balance_factor(node*);
    void fix_height(node*);
    node* rotate_right(node*);
    node* rotate_left(node*);
    node* balance(node*);
    node* do_insert(node*, int);
    node* find_min(node*);
    node* remove_min(node*);
    node* do_remove(node*, int);
    node* root = new node(INF);
//public:
    void remove(node*&, int);
    bool find(node*, int);
    void insert(node*&, int);
    node* find_next(node*, int);
    node* find_prev(node*, int);
public:
    void Remove(int);
    bool Find(int);
    void Insert(int);
    int Find_next(int);
    int Find_prev(int);

};

int AVL_tree::height(node* p) {
    return (p ? p->height : 0);
}

int AVL_tree::balance_factor(node* p) {
    return height(p->right) - height(p->left);
}

void AVL_tree::fix_height(node* p) {
    int height_left = height(p->left);
    int height_right = height(p->right);
    p->height = (height_left > height_right ? height_left : height_right) + 1;
}

node* AVL_tree::rotate_right(node* p) {
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

node* AVL_tree::rotate_left(node* q) {
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

node* AVL_tree::balance(node* p) {
    fix_height(p);
    if (balance_factor(p) == 2) {
        if (balance_factor(p->right) < 0)p->right = rotate_right(p->right);
        return rotate_left(p);
    }
    else if (balance_factor(p) == -2) {
        if (balance_factor(p->left) > 0)p->left = rotate_left(p->left);
        return rotate_right(p);
    }
    else return p;
}

node* AVL_tree::do_insert(node* p, int k) {
    if (!p)return new node(k);
    if (k < p->key)p->left = do_insert(p->left, k);
    else p->right = do_insert(p->right, k);
    return balance(p);
}

node* AVL_tree::find_min(node* p) {
    return (p->left ? find_min(p->left) : p);
}

node* AVL_tree::remove_min(node* p) {
    if (!p) return nullptr;
    if (!(p->left))return p->right;
    p->left = remove_min(p->left);
    return balance(p);
}

node* AVL_tree::do_remove(node* p, int k) {
    if (!p)return nullptr;
    if (k < p->key)p->left = do_remove(p->left, k);
    else if (k > p->key)p->right = do_remove(p->right, k);
    else {
        node* L = p->left;
        node* R = p->right;
        delete p;
        if (!R)return L;
        if (!L)return R;
        node* minimum = find_min(R);
        minimum->right = remove_min(R);
        minimum->left = L;
        return balance(minimum);
    }
    return balance(p);
}


void AVL_tree::remove(node*& p, int k) {
    if (find(p, k))p = do_remove(p, k);
}

bool AVL_tree::find(node* p, int k) {
    if (!p)return false;
    if (p->key == k)return true;
    if (p->key > k)return find(p->left, k);
    return find(p->right, k);

}

void AVL_tree::insert(node*& p, int k) {
    if (!find(p, k))p = do_insert(p, k);
}

node* AVL_tree::find_next(node* p, int k) {
    node* cur = p;
    node* successor = nullptr;
    while (cur != nullptr) {
        if (cur->key > k) {
            successor = cur;
            cur = cur->left;
        }
        else cur = cur->right;
    }
    return successor;
}

node* AVL_tree::find_prev(node* p, int k) {
    node* cur = p;
    node* successor = nullptr;
    while (cur != nullptr) {
        if (cur->key < k) {
            successor = cur;
            cur = cur->right;
        }
        else cur = cur->left;
    }
    return successor;
}
void AVL_tree::Remove(int k) {
    remove(root, k);
}

bool AVL_tree::Find(int k) {
    return find(root, k);

}

void AVL_tree::Insert( int k) {
    insert(root, k);
}

int AVL_tree::Find_next( int k) {
    node* tmp = find_next(root, k);
    if (tmp != nullptr)return tmp->key;
    else return INF;
}

int AVL_tree::Find_prev(int k) {
    node* tmp = find_prev(root, k);
    if (tmp != nullptr)return tmp->key;
    else return INF;
}




int main() {
    AVL_tree tree;
    string s;
    int x;
    while (cin >> s >> x) {
        if (s == "insert") tree.Insert(x);
        else if (s == "delete") tree.Remove(x);
        else if (s == "exists") cout << (tree.Find(x) ? "true" : "false") << '\n';
        else if (s == "next") {
            int tmp = tree.Find_next(x);
            if (tmp == INF)cout << "none" << '\n';
            else cout << tmp << '\n';
        }
        else if (s == "prev") {
            int tmp = tree.Find_prev(x);
            if (tmp == INF)cout << "none" << '\n';
            else cout << tmp << '\n';
        }
    }
}
