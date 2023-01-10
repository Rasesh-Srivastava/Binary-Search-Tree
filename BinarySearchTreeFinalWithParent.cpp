#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node *parent;
};
class BinarySearchTree
{
public:
    Node *newNode(int Data)
    {
        Node *node = new Node();
        node->data = Data;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        return (node);
    }
    void inorder(Node *n)
    {
        if (n == NULL)
        {
            return;
        }
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }
    void preorder(Node *n)
    {
        if (n == NULL)
        {
            return;
        }
        cout << n->data << " ";
        preorder(n->left);
        preorder(n->right);
    }
    void postorder(Node *n)
    {
        if (n == NULL)
        {
            return;
        }
        postorder(n->left);
        postorder(n->right);
        cout << n->data << " ";
    }
    Node *InsertNode(Node *node, int data)
    {
        if (node == NULL)
        {
            return newNode(data);
        }
        if (data < node->data)
        {
            node->left = InsertNode(node->left, data);
            node->left->parent = node;
        }
        else
        {
            node->right = InsertNode(node->right, data);
            node->right->parent = node;
        }
        return node;
    }
    Node *MinValue(Node *node)
    {
        Node *curr = node;
        while (curr && curr->left != NULL)
        {
            curr = curr->left;
        }
        return curr;
    }
    Node *DeleteNode(Node *root, int data)
    {
        if (root == NULL)
        {
            return root;
        }
        if (data < (root->data))
        {
            root->left = DeleteNode(root->left, data);
            if (root->left != NULL)
            {
                root->left->parent = root;
            }
        }
        else if (data > (root->data))
        {
            root->right = DeleteNode(root->right, data);
            if (root->right != NULL)
            {
                root->right->parent = root;
            }
        }
        else
        {
            if (root->left == NULL)
            {
                Node *temp = root->right;
                if (temp != NULL)
                {
                    temp->parent = root->parent;
                }
                free(root);
                return temp;
            }
            else if (root->right == NULL)
            {
                Node *temp = root->left;
                if (temp != NULL)
                {
                    temp->parent = root->parent;
                }
                free(root);
                return temp;
            }
            Node *temp = MinValue(root->right);
            Node *np_min = temp->parent;
            Node *np = root->parent;
            if (temp == np_min->left)
            {
                np_min->left = NULL;
            }
            else
            {
                np_min->right = NULL;
            }
            temp->parent = np;
            temp->left = root->left;
            temp->right = root->right;
            if (root == np->left)
            {
                np->left = temp;
            }
            else
            {
                np->right = temp;
            }
            root->data = temp->data;
            root->right = DeleteNode(root->right, temp->data);
        }
        return root;
    }
    Node *search(Node *node, int data)
    {
        Node *current = node;
        while (current->data != data)
        {
            if (current->data > data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
            if (current == NULL)
            {
                return NULL;
            }
        }
        return current;
    }
};
int main()
{
    BinarySearchTree Rasesh;
    Node *root = NULL;
    while (true)
    {
        cout << "1. Insert an element" << endl;
        cout << "2. Delete an element" << endl;
        cout << "3. Search an element" << endl;
        cout << "4. InOrder Traversal" << endl;
        cout << "5. PreOrder Traversal" << endl;
        cout << "6. PostOrder Traversal" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice" << endl;
        int n;
        cin >> n;
        switch (n)
        {
        default:
            cout << "Enter a valid choice" << endl;
            break;
        case 7:
            exit(0);
            break;
        case 6:
            Rasesh.postorder(root);
            cout << endl;
            break;
        case 5:
            Rasesh.preorder(root);
            cout << endl;
            break;
        case 4:
            Rasesh.inorder(root);
            cout << endl;
            break;
        case 1:
            cout << "Enter the element to be inserted" << endl;
            int a;
            cin >> a;
            root = Rasesh.InsertNode(root, a);
            break;
        case 2:
            cout << "Enter the element to be deleted" << endl;
            int b;
            cin >> b;
            root = Rasesh.DeleteNode(root, b);
            break;
        case 3:
            cout << "Enter the element to be searched" << endl;
            int c;
            cin >> c;
            Node *temp = Rasesh.search(root, c);
            if (temp == NULL)
            {
                cout << "Element Not Found" << endl;
            }
            else
            {
                cout << "Element Found" << endl;
                if (temp->parent != NULL)
                {
					cout << "Parent of " << temp->data << " is: ";
                    cout << temp->parent->data << endl;
                }
            }
            break;
        }
    }
    return 0;
}