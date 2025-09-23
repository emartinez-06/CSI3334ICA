#include <iostream>
using namespace std;

template <typename T>
struct BSTNode {
    T data;
    BSTNode *left;
    BSTNode *right;

    BSTNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
   private:
    BSTNode<T> *root;

   public:
    BST() : root(nullptr) {}

    // Basic insert (for testing)
    void insert(T val) { root = insertHelper(root, val); }

    void remove(T val) {
        // Locate parent and toRemove
        BSTNode<T> *parent = nullptr;
        BSTNode<T> *toRemove = root;

        // iterate tree until toRemove found
        while (toRemove && toRemove->data != val) {
            parent = toRemove;
            if (val < toRemove->data) {
                toRemove = toRemove->left;
            } else {
                toRemove = toRemove->right;
            }
        }

        if (!toRemove) {
            cout << "Value not found.\n";
            return;
        }
        // Exercise 1: Removing a leaf node
        if (toRemove->left == nullptr && toRemove->right == nullptr) {
            if (parent->left == toRemove) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }

            //           parent->left == nullptr ? parent->right = nullptr
            //                                 : parent->left = nullptr;
            delete toRemove;
        }
        // Exercise 2: Removing a node with one child
        else if (toRemove->left == nullptr || toRemove->right == nullptr) {
            /*
            // remove is on left of parent
            toRemove->left == nullptr ? parent->left = toRemove->right
                                      : parent->left = toRemove->left;
            // remove is on the right of parent
            toRemove->left == nullptr ? parent->right = toRemove->right
                                      : parent->right = toRemove->left;

            // for both
            toRemove->left = toRemove->right = nullptr;
            */
            BSTNode<T> *child =
                (toRemove->left != nullptr) ? toRemove->left : toRemove->right;

            if (parent->left == toRemove) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            delete toRemove;

        }
        // Exercise 3: Removing a node with two children
        else {
            // Find leftmost node of right subtree (inorder successor)
            BSTNode<T> *leftMostParent = toRemove;
            BSTNode<T> *leftMost = toRemove->right;

            while (leftMost->left != nullptr) {
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }

            // Copy successor's data into toRemove
            toRemove->data = leftMost->data;

            // Fix links
            if (leftMostParent->left == leftMost) {
                leftMostParent->left = leftMost->right;
            } else {
                leftMostParent->right = leftMost->right;
            }

            delete leftMost;
        }
    }

    // Simple inorder traversal
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

   private:
    BSTNode<T> *insertHelper(BSTNode<T> *node, T val) {
        if (!node)
            return new BSTNode<T>(val);
        if (val < node->data)
            node->left = insertHelper(node->left, val);
        else
            node->right = insertHelper(node->right, val);
        return node;
    }

    void inorderHelper(BSTNode<T> *node) {
        if (!node)
            return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
};

int main() {
    BST<int> tree;

    // Insert test data
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder before removal: ";
    tree.inorder();

    // TODO: Test removals
    tree.remove(20); // Leaf case
    tree.remove(30); // One child case
    tree.remove(50); // Two children case

    cout << "Inorder after removal: ";
    tree.inorder();

    return 0;
}
