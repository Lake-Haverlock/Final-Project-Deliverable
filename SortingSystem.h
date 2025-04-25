#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Struct to represent book title, author, and if it is available
struct Book
{
    string title;
    string author;

    //Default constructor
    Book()
    {
        title = "";
        author = "";
    }

    //Constructor
    Book(string t, string a)
    {
        title = t;
        author = a;
    }

    //Comparison operators for ordering AVL tree
    //Sorts by author, and then title if author is the same

    bool operator<(const Book& other) const
    {
        if (author == other.author)
        {
            return title < other.title;
        }
        return author < other.author;
    }

    bool operator>(const Book& other) const
    {
        if (author == other.author)
        {
            return title > other.title;
        }
        return author > other.author;
    }

    bool operator==(const Book& other) const
    {
        return title == other.title && author == other.author;
    }
};

//Prints book information
ostream& operator<<(ostream& os, const Book& book)
{
    os << "Title: " << book.title << ", Author: " << book.author;
    return os;
}

//AVL tree node template class
template <typename T> class AVLNode
{
public:
    T key; //Book object
    AVLNode* left; //Pointer to the left child
    AVLNode* right; //Pointer to the right child
    int height; //Height of the node in the tree

    //Constructor initializes node with a book
    AVLNode(T k)
    {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

//AVL tree template class
template <typename T> class AVLTree
{
private:
    // Pointer to the root of AVL tree
    AVLNode<T>* root;

    //Gets height of the node
    int height(AVLNode<T>* node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    //Gets balance factor of the node
    int balanceFactor(AVLNode<T>* node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    //Performs right rotation on the subtree
    AVLNode<T>* rightRotate(AVLNode<T>* y)
    {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        //Updates heights
        y->height = max(height(y->left), height(y->right)) + 1;

        x->height = max(height(x->left), height(x->right)) + 1;

        //Returns new root
        return x;
    }

    //Performs left rotation on the subtree
    AVLNode<T>* leftRotate(AVLNode<T>* x)
    {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        //Updates heights
        x->height = max(height(x->left), height(x->right)) + 1;

        y->height = max(height(y->left), height(y->right)) + 1;

        //Returns new root
        return y;
    }

    //Inserts new key into the subtree
    AVLNode<T>* insert(AVLNode<T>* node, T key)
    {
        //Performs normal BST insertion
        if (node == nullptr)
        {
            return new AVLNode<T>(key);
        }

        if (key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            cout << "Book already exists: " << key << "\n";
            return node;
        }

        //Updates height of ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        //Get the balance factor of this ancestor node
        int balance = balanceFactor(node);

        //If this node becomes unbalanced, then there are 4 cases

        //Left Left Case
        if (balance > 1 && key < node->left->key)
        {
            return rightRotate(node);
        }

        //Right Right Case
        if (balance < -1 && key > node->right->key)
        {
            return leftRotate(node);
        }

        //Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    //Finds the node with the minimum key value
    AVLNode<T>* minValueNode(AVLNode<T>* node)
    {
        AVLNode<T>* current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    //Deletes a key from the subtree
    AVLNode<T>* deleteNode(AVLNode<T>* root, T key)
    {
        //Performs standard BST delete
        if (root == nullptr)
        {
            return root;
        }

        if (key < root->key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            //Node with only one or no child
            if ((root->left == nullptr) || (root->right == nullptr))
            {
                AVLNode<T>* temp = root->left ? root->left : root->right;
                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    *root = *temp;
                    delete temp;
                }
            }
            else
            {
                AVLNode<T>* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        //Updates height of the current node
        root->height = 1 + max(height(root->left), height(root->right));

        //Gets the balance factor of this node
        int balance = balanceFactor(root);

        //If this node becomes unbalanced, then there are 4 cases

        //Left Left Case
        if (balance > 1 && balanceFactor(root->left) >= 0)
        {
            return rightRotate(root);
        }

        //Left Right Case
        if (balance > 1 && balanceFactor(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        //Right Right Case
        if (balance < -1 && balanceFactor(root->right) <= 0)
        {
            return leftRotate(root);
        }

        //Right Left Case
        if (balance < -1 && balanceFactor(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    //Finds an exact node match and returns a pointer to it
    AVLNode<T>* findNode(AVLNode<T>* node, const T& key) {
        if (node == nullptr || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return findNode(node->left, key);
        }
        return findNode(node->right, key);
    }
    //Searches for a partial key match
    void searchNode(AVLNode<T>* node, const string& query, bool& found) {
        if (node == nullptr) return;

        searchNode(node->left, query, found);


        if (node->key.title.find(query) != string::npos || node->key.author.find(query) != string::npos) {
            cout << "Book Found: " << node->key << "\n";
            found = true;
        }
        searchNode(node->right, query, found);
    }

public:
    //Constructor to initialize the AVL tree
    AVLTree()
    {
        root = nullptr;
    }

    //Destructor
    ~AVLTree()
    {
        clear(root);
    }

    void clear(AVLNode<T>* node)
    {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    //Inserts a key into the AVL tree
    void insert(T key) 
    {
        root = insert(root, key);
    }

    //Updates an existing key from the AVL tree
    void update(T oldKey, T newKey) {
        AVLNode<T>* result = findNode(root, oldKey);
        if (result) {
            remove(oldKey);
            insert(newKey);
            cout << "Book updated successfully. \n";
        }
        else {
            cout << "Book not found. Update failed. \n";
        }
    }

    //Removes a key from the AVL tree
    void remove(T key)
    {
        root = deleteNode(root, key);
    }

    // Partial match search
    void search(string query) {
        bool found = false;
        cout << "Searching for: \"" << query << "\"...\n";
        searchNode(root, query, found);
        if (!found) cout << "No matching books found. \n";
    }
};
#endif