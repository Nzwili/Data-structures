#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100


typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void push(Stack *stack, char c);
char pop(Stack *stack);
char peek(Stack *stack);
int isEmpty(Stack *stack);
int precedence(char c);
void infixToPrefix(char *infix, char *prefix);
void reverseString(char *str);

int main() {
    char infix[MAX_SIZE];
    char prefix[MAX_SIZE];

    printf("Enter the infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strlen(infix) - 1] = '\0';r

    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    return 0;
}

void push(Stack *stack, char c) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = c;
}

char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    Stack stack;
    stack.top = -1;

    reverseString(infix); // Reverse the infix expression

    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                prefix[j++] = infix[i++];
            }
            prefix[j++] = ' ';
        } else if (infix[i] == ')') {
            push(&stack, infix[i++]);
        } else if (infix[i] == '(') {
            while (!isEmpty(&stack) && peek(&stack) != ')') {
                prefix[j++] = pop(&stack);
            }
            pop(&stack); // Pop '('
            i++;
        } else {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(infix[i])) {
                prefix[j++] = pop(&stack);
            }
            push(&stack, infix[i++]);
        }
    }
    while (!isEmpty(&stack)) {
        prefix[j++] = pop(&stack);
    }
    prefix[j] = '\0';

    reverseString(prefix);
}

void reverseString(char *str) {
    int len = strlen(str);
    int i, j;
    char temp;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
