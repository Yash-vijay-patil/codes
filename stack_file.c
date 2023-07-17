#include<stdio.h>
#include<stdlib.h>

struct Stack
{
int arr[100];
int top;
};

void init_stack(struct Stack* stack)
{
    stack->top = -1;
}
void push(struct Stack* stack, int element) {
    if (stack->top == 100 - 1) {
        printf("Error: Stack overflow\n");

        return;
    }

    stack->top++;
    stack->arr[stack->top] = element;
}
int pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Error: Stack underflow\n");
        return -1;
    }
    int element = stack->arr[stack->top];
    stack->top--;
    return element;
}
void display(struct Stack* stack)
{
   if (stack->top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->arr[i]);
    }
}
void generate_numbers(struct Stack* stack, int count)
 {
    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
     // if (stack->top == -1)
    //{
        int num = rand() % 100;
        push(stack, num);
    //}
    //else
    //{
      //  int num = rand() % 100;
        //pop(stack, num);
    //}

    }
}
void save_stack(struct Stack* stack, char* filename,int e) {
    FILE* fp = fopen("stack.txt", "w");
    time_t t;
    time(&t);
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
        fprintf(fp,"%s pushed data: %d \n\n\n",ctime(&t),e);
    }
    fclose(fp);
    printf("Stack elements saved to file %s\n", "stack.txt");
}
void load_stack(struct Stack* stack, char* filename) {
    FILE* fp = fopen("pushstack.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }
    int element;
    while (fscanf(fp, "%d", &element) == 1) {
        push(stack, element);
    }
    fclose(fp);
    printf("Stack elements loaded from file %s\n", "pushstack.txt");
}

int main() {
    struct Stack stack;
    init_stack(&stack);


    int choice, element,count,e,no;
    char filename[100];

    do {
        printf("1.generate random numbers\n");
        printf("2. Push\n");
        printf("3. Pop\n");
        printf("4. Display\n");
        printf("5.save to file\n");
        printf("6.load from file\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
         case 1:
            printf("Enter number of random numbers to generate: ");
            scanf("%d", &count);
            generate_numbers(&stack, count);
            break;
        case 2:
            printf("Enter no of times to perform the operation:");
            scanf("%d",&no);
            for(int i=1;i<=no;i++)
            {
            printf("Enter element to push: ");
            scanf("%d", &element);
            push(&stack, element);
            }
            break;
        case 3:
               printf("Enter no of times to perform the operation:");
            scanf("%d",&no);
            for(int i=1;i<=no;i++)
            {
            element = pop(&stack);
            if (element != -1) {
                printf("Popped element: %d\n", element);
            }
            }
            break;
        case 4:
            display(&stack);
            break;
       case 5:
          //  printf("Enter filename to save: ");
           // scanf("%s", filename);
            save_stack(&stack,"stack.txt",e);
            break;
        case 6:
          //  printf("Enter filename to load: ");
           // scanf("%s", filename);
            load_stack(&stack, "pushstack.txt");
           // pop(&stack,"stack.txt");
            break;
        case 7:
            printf("Exiting program\n");
            break;
        default:
            printf("wrong choice\n");
            break;
        }
    } while (choice != 7);

    return 0;
}
