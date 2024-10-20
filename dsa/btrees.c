#include <stdio.h>
#include <stdlib.h>

#define t 3  // Minimum degree of B-Tree

// B-Tree Node structure
struct BTreeNode {
    int keys[2 * t - 1];    // An array of keys
    struct BTreeNode* children[2 * t]; // An array of child pointers
    int n;                  // Current number of keys
    int leaf;               // 1 if leaf node, 0 otherwise
};

// Function to create a new B-Tree node
struct BTreeNode* createNode(int leaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->n = 0;
    newNode->leaf = leaf;
    return newNode;
}

// Function to traverse the B-Tree
void traverse(struct BTreeNode* node) {
    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->leaf)
            traverse(node->children[i]);
        printf("%d ", node->keys[i]);
    }
    if (!node->leaf)
        traverse(node->children[i]);
}

// Function to search a key in the B-Tree
struct BTreeNode* search(struct BTreeNode* node, int key) {
    int i = 0;
    while (i < node->n && key > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == key)
        return node;

    if (node->leaf)
        return NULL;

    return search(node->children[i], key);
}

// Function to split a full child node
void splitChild(struct BTreeNode* parent, int i, struct BTreeNode* fullChild) {
    struct BTreeNode* newChild = createNode(fullChild->leaf);
    newChild->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        newChild->keys[j] = fullChild->keys[j + t];

    if (!fullChild->leaf) {
        for (int j = 0; j < t; j++)
            newChild->children[j] = fullChild->children[j + t];
    }

    fullChild->n = t - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = newChild;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = fullChild->keys[t - 1];
    parent->n += 1;
}

// Function to insert a key into a non-full node
void insertNonFull(struct BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n += 1;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;

        if (node->children[i + 1]->n == 2 * t - 1) {
            splitChild(node, i + 1, node->children[i + 1]);

            if (key > node->keys[i + 1])
                i++;
        }
        insertNonFull(node->children[i + 1], key);
    }
}

// Function to insert a new key into the B-Tree
struct BTreeNode* insert(struct BTreeNode* root, int key) {
    if (root->n == 2 * t - 1) {
        struct BTreeNode* newRoot = createNode(0);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        insertNonFull(newRoot, key);
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// Driver code
int main() {
    struct BTreeNode* root = createNode(1); // Create an empty B-Tree

    int choice, key;
    while (1) {
        printf("\n1. Insert Key\n2. Search Key\n3. Traverse B-Tree\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                struct BTreeNode* result = search(root, key);
                if (result)
                    printf("Key %d found.\n", key);
                else
                    printf("Key %d not found.\n", key);
                break;
            case 3:
                printf("B-Tree Traversal: ");
                traverse(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}