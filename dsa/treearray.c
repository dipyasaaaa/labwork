#include <stdio.h>

#define MAX_SIZE 100

// Global array to represent the binary tree
int tree[MAX_SIZE];
int size = 0; // Current size of the tree

// Function to insert a value into the tree
void insert(int x) {
    if (size >= MAX_SIZE) {
        printf("Tree is full!\n");
        return;
    }
    tree[size] = x;
    size++;
    printf("Inserted %d into the tree.\n", x);
}

// Function to delete a node with a given value
void deleteNode(int x) {
    int f = 0;
    for (int i = 0; i < size; i++) {
        if (tree[i] == x) {
            f = 1;
            // Shift all elements to the left from the position of the deleted node
            for (int j = i; j < size - 1; j++) {
                tree[j] = tree[j + 1];
            }
            size--;  // Reduce the size after deleting
            printf("Deleted node %d\n", x);
            break;
        }
    }
    
    if (f == 0) {
        printf("Node with value %d not found!\n", x);
    }
}

// Function to print the parent of a node at a given index
void printParent(int x) {
    int f=0;
    for(int i=0; i<size;i++){
        if(tree[i]==x){
            f=1;
            if (i==0) {
                printf("Node %d has no parent (it might be the root or invalid index).\n", x);
                return;}
            else{
                int pidx=(i-1)/2;
                printf("Parent of node %d is %d\n",x,tree[pidx]);
            }
    }
        }
    }

// Function to print the tree (Level-order traversal)
void printTree() {
    if (size == 0) {
        printf("Tree is empty.\n");
        return;
    }
    printf("Tree elements (Level-order): ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

int main() {
    int ch, val;

    while(1){
        printf("\nMenu:\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Print tree\n");
        printf("4. Print parent of a node\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        if(ch==5){
            return 0;}

        switch (ch) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(val);
                break;
            case 2:
                printf("Enter value of the node to delete: ");
                scanf("%d", &val);
                deleteNode(val);
                break;
            case 3:
                printTree();
                break;
            case 4:
                printf("Enter child node value: ");
                scanf("%d", &val);
                printParent(val);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}