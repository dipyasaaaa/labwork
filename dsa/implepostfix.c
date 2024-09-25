#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
int stack[MAX];
int top = -1;

void push(int val) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = val;
    }
}

int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        return stack[top--];
    }
}

int evaluatePostfix(char* exp) {
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i])) {
            push(exp[i] - '0');  // Convert char to int
        } else {
            int val1 = pop();
            int val2 = pop();
            
            switch (exp[i]) {
                case '+': push(val2 + val1); break;
                case '-': push(val2 - val1); break;
                case '*': push(val2 * val1); break;
                case '/': push(val2 / val1); break;
            }
        }
    }
    return pop();
}

int main() {
    char exp[MAX];  // Define a buffer to store user input

    printf("Enter a postfix expression: ");
    scanf("%s", exp);  // Read user input (postfix expression)

    printf("Postfix expression: %s\n", exp);
    printf("Evaluation result: %d\n", evaluatePostfix(exp));

    return 0;
}
