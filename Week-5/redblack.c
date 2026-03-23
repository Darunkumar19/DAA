#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;

// Create new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

// Left rotate
void leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right rotate
void rightRotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix violations
void fixInsert(Node *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        Node *grandparent = z->parent->parent;

        if (z->parent == grandparent->left) {
            Node *uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                rightRotate(grandparent);
            }
        } else {
            Node *uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                leftRotate(grandparent);
            }
        }
    }
    root->color = BLACK;
}

// Insert
void insert(int data) {
    Node *z = newNode(data);
    Node *y = NULL;
    Node *x = root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(z);
}

// Level order print
void printLevelOrder() {
    if (root == NULL) return;

    Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        int size = rear - front;

        while (size--) {
            Node* temp = queue[front++];
            printf("%d(%c) ", temp->data,
                   temp->color == RED ? 'R' : 'B');

            if (temp->left)
                queue[rear++] = temp->left;
            if (temp->right)
                queue[rear++] = temp->right;
        }
        printf("\n");
    }
}

// Check root black
int isRootBlack() {
    return (root != NULL && root->color == BLACK);
}

// Check no red-red violation
int checkRedViolation(Node *node) {
    if (node == NULL) return 1;

    if (node->color == RED) {
        if ((node->left && node->left->color == RED) ||
            (node->right && node->right->color == RED))
            return 0;
    }

    return checkRedViolation(node->left) &&
           checkRedViolation(node->right);
}

// Main
int main() {
    int arr[] = {157, 110, 147, 122, 149, 151, 111, 141, 112, 123, 133, 117};
    int n = sizeof(arr)/sizeof(arr[0]);

    for (int i = 0; i < n; i++)
        insert(arr[i]);

    printf("Level Order Traversal (with colors):\n");
    printLevelOrder();

    printf("\nRoot is %s\n", isRootBlack() ? "BLACK ✔" : "NOT BLACK ✘");

    printf("No Red-Red violation: %s\n",
           checkRedViolation(root) ? "YES ✔" : "NO ✘");

    return 0;
}