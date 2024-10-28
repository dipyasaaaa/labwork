#include <stdio.h>
#include <stdlib.h>

typedef struct BTreeNode {
    int *keys;                // Array of keys
    struct BTreeNode **C;     // Array of child pointers
    int n;                    // Current number of keys
    int leaf;                 // 1 if leaf node, 0 otherwise
    int m;                    // Order of the B-tree
} BTreeNode;

// Function to create a new B-tree node
BTreeNode *createNode(int m, int leaf) {
    BTreeNode *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    newNode->keys = (int *)malloc((m - 1) * sizeof(int));   // Maximum of m-1 keys
    newNode->C = (BTreeNode **)malloc(m * sizeof(BTreeNode *));  // Maximum of m children
    newNode->n = 0;      // Initially, the node has no keys
    newNode->leaf = leaf; // 1 for leaf node, 0 for internal node
    newNode->m = m;      // Store the order of the B-tree
    return newNode;
}

// Function to split a full child
void splitChild(BTreeNode *parent, int i) {
    BTreeNode *fullChild = parent->C[i];        // Full child node to be split
    BTreeNode *newChild = createNode(parent->m, fullChild->leaf);  // New child node after splitting

    int medianIndex = (parent->m - 1) / 2;  // Index of the median key

    // New child gets the right half of the keys from fullChild
    newChild->n = medianIndex;  // Number of keys in the new child
    for (int j = 0; j < newChild->n; j++) {
        newChild->keys[j] = fullChild->keys[j + medianIndex + 1]; // Copy keys to newChild
    }

    // Move the child pointers if it's not a leaf node
    if (!fullChild->leaf) {
        for (int j = 0; j <= newChild->n; j++) {
            newChild->C[j] = fullChild->C[j + medianIndex + 1];  // Copy child pointers
        }
    }

    // Update the number of keys in the original full child
    fullChild->n = medianIndex;  // Keep the left half keys in fullChild

    // Shift children of the parent to make space for the new child
    for (int j = parent->n; j >= i + 1; j--) {
        parent->C[j + 1] = parent->C[j];
    }
    parent->C[i + 1] = newChild;

    // Shift the parent's keys to make space for the median key
    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }

    // Move the median key of fullChild to the parent
    parent->keys[i] = fullChild->keys[medianIndex];
    parent->n++;  // Update the number of keys in the parent
}

// Insert a key in a non-full node
void insertNonFull(BTreeNode *node, int k) {
    int i = node->n - 1;

    // If this is a leaf node, insert the key directly
    if (node->leaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        // Locate the child which is going to have the new key
        while (i >= 0 && k < node->keys[i]) i--;

        // Check if the child is full (has m-1 keys)
        if (node->C[i + 1]->n == node->m - 1) {
            splitChild(node, i + 1);
            if (k > node->keys[i + 1]) i++;
        }
        insertNonFull(node->C[i + 1], k);
    }
}

// Insert a new key into the B-tree
void insert(BTreeNode **root, int k) {
    BTreeNode *r = *root;

    // If the root is full, the tree grows in height
    if (r->n == r->m - 1) {
        BTreeNode *s = createNode(r->m, 0);   // Create a new root
        s->C[0] = r;                    // Old root becomes the child of the new root
        splitChild(s, 0);               // Split the old root
        insertNonFull(s, k);            // Insert in the new root
        *root = s;                      // Update the root
    } else {
        insertNonFull(r, k);            // Insert in the existing root
    }
}

// Function to print the B-tree (level order)
void printTree(BTreeNode *root, int level) {
    if (root == NULL) return;

    printf("Level %d: ", level);
    for (int i = 0; i < root->n; i++) {
        printf("%d ", root->keys[i]);
    }
    printf("\n");

    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++) {
            printTree(root->C[i], level + 1);
        }
    }
}

// Main function with a switch case for operations
int main() {
    int m;
    printf("Enter the order of the B-tree (m): ");
    scanf("%d", &m);

    BTreeNode *root = createNode(m, 1);  // Start with a new leaf node
    int choice, num;

    do {
        printf("\nB-Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Traverse (Print Tree)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to insert: ");
                scanf("%d", &num);
                insert(&root, num);
                break;
            case 2:
                printf("B-tree structure:\n");
                printTree(root, 0);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}