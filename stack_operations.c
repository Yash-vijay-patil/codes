#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STACK_SIZE 100

// Stack structure
struct Stack {
    int arr[STACK_SIZE];
    int top;
};

// Initialize stack
void init_stack(struct Stack* stack) {
    stack->top = -1;
}

// Push an element onto the stack
void push(struct Stack* stack, int element) {
    if (stack->top == STACK_SIZE - 1) {
        printf("Error: Stack overflow\n");
        return;
    }
    stack->top++;
    stack->arr[stack->top] = element;
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Error: Stack underflow\n");
        return -1;
    }
    int element = stack->arr[stack->top];
    stack->top--;
    return element;
}

// Check if the stack is empty
int is_empty(struct Stack* stack) {
    return (stack->top == -1);
}

// Display the stack elements
void display(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->arr[i]);
    }
}

// Save the stack elements to a file
void save_stack(struct Stack* stack) {
    char filename[100];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(filename, 100, "stack-%Y-%m-%d-%H-%M-%S.txt", timeinfo);

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }
    if (stack->top == -1) {
        fprintf(fp, "Stack is empty\n");
    } else {
        for (int i = stack->top; i >= 0; i--) {
            fprintf(fp, "%d\n", stack->arr[i]);
        }
    }
    fclose(fp);
    printf("Stack elements saved to file %s\n", filename);
}

// Generate random numbers and push them onto the stack
void generate_numbers(struct Stack* stack, int count) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int num = rand() % 100;
        push(stack, num);
    }
}

// Main function
int main() {
    struct Stack stack;
    init_stack(&stack);

    int numOperations;
    int choice, count;

    printf("Enter the number of times to perform push and pop operations: ");
    scanf("%d", &numOperations);

    for (int i = 0; i < numOperations; i++) {
        printf("\nOperation %d\n", i + 1);
        printf("1. Push element\n");
        printf("2. Pop element\n");
        printf("3. Generate random numbers\n");
        printf("4. Display\n");
        printf("5. Save to file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                int element;
                scanf("%d", &element);
                push(&stack, element);
                break;
            case 2:
                if (is_empty(&stack)) {
                    printf("Stack is empty\n");
                } else {
                    int popped = pop(&stack);
                    printf("Popped element: %d\n", popped);
                }
                break;
            case 3:
                printf("Enter the number of random numbers to generate: ");
                scanf("%d", &count);
                generate_numbers(&stack, count);
                break;
            case 4:
                display(&stack);
                break;
            case 5:
                save_stack(&stack);
                break;
            case 6:
                printf("Exiting program\n");
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}

