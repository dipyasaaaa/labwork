#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        // If the tree is empty, return a new node
        return createNode(data);
    }

    if (data < root->data) {
        // If data is smaller, insert into the left subtree
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        // If data is larger, insert into the right subtree
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Function to perform inorder traversal of the BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to search for a node in the BST
struct Node* searchNode(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return searchNode(root->left, data);
    }

    return searchNode(root->right, data);
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n2. Inorder Traversal\n3. Search\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (searchNode(root, value)) {
                    printf("%d found in the tree.\n", value);
                } else {
                    printf("%d not found in the tree.\n", value);
                }

                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}