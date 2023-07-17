#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Stack structure
struct Stack {
    struct Node* top;
};

// Initialize stack
void init_stack(struct Stack* stack) {
    stack->top = NULL;
}

// Push an element onto the stack
void push(struct Stack* stack, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = element;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Error: Stack underflow\n");
        return -1;
    }
    struct Node* temp = stack->top;
    int element = temp->data;
    stack->top = temp->next;
    free(temp);
    return element;
}

// Check if the stack is empty
int is_empty(struct Stack* stack) {
    return (stack->top == NULL);
}

// Display the stack elements
void display(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements:\n");
    struct Node* current = stack->top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// Save the stack elements to a file
void save_stack(struct Stack* stack) {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char filename[100];
    strftime(filename, 100, "stack-%Y-%m-%d-%H-%M-%S.txt", timeinfo);

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }
    if (stack->top == NULL) {
        fprintf(fp, "Stack is empty\n");
    } else {
        struct Node* current = stack->top;
        while (current != NULL) {
            fprintf(fp, "%d\n", current->data);
            current = current->next;
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

    int choice, count;

    do {
        printf("1. Generate random numbers\n");
        printf("2. Display\n");
        printf("3. Save to file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter number of random numbers to generate: ");
            scanf("%d", &count);
            generate_numbers(&stack, count);
            break;
        case 2:
            display(&stack);
            break;
        case 3:
            save_stack(&stack);
            break;
        case 4:
            printf("Exiting program\n");
                 break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 4);

    // Clean up the stack
    struct Node* current = stack.top;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
