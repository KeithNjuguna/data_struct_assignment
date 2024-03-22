/*
SCT221-0217/2022 Keith Kihara
SCT221-0218/2022 Kepha Weru
*/

#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (!root) return createNode(data);
    if (data < root->data) root->left = insert(root->left, data);
    else if (data > root->data) root->right = insert(root->right, data);
    return root;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (!root) return root;

    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int height(struct Node* root) {
    if (!root) return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

void printLevelAndHeight(struct Node* root, int key, int level) {
    if (!root) printf("Node not found.\n");
    else if (root->data == key) printf("Level: %d, Height: %d\n", level, height(root));
    else if (key < root->data) printLevelAndHeight(root->left, key, level + 1);
    else printLevelAndHeight(root->right, key, level + 1);
}

void printLevelOrder(struct Node* root) {
    if (!root) return;
    struct Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct Node* temp = queue[front++];
        printf("%d ", temp->data);
        if (temp->left) queue[rear++] = temp->left;
        if (temp->right) queue[rear++] = temp->right;
    }
    printf("\n");
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = NULL;
    for (int i = 0; i < n; i++) root = insert(root, arr[i]);

    printf("Level-order traversal of the tree: ");
    printLevelOrder(root);

    int keyToDelete = 25;
    root = deleteNode(root, keyToDelete);
    printf("After deleting node with value %d: ", keyToDelete);
    printLevelOrder(root);

    printf("Height of the tree: %d\n", height(root));

    int keyToFind = 40;
    printLevelAndHeight(root, keyToFind, 0);

    return 0;
}
