#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

Node* createListFromFile(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    Node* head = NULL;
    Node* tail = NULL;
    int value;

    while (fscanf(fp, "%d", &value) == 1) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = value;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    fclose(fp);
    return head;
}
void writeListToFile(Node* head, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (head != NULL) {
        fprintf(fp, "%d ", head->data);
        head = head->next;
    }

    fclose(fp);
}

void insertionSort(Node** head_ref) {
    Node* sorted = NULL;
    Node* current = *head_ref;

    while (current != NULL) {
        Node* next = current->next;
        Node** ptr = &sorted;

        while (*ptr != NULL && (*ptr)->data < current->data) {
            ptr = &((*ptr)->next);
        }

        current->next = *ptr;
        *ptr = current;
        current = next;
    }

    *head_ref = sorted;
}

int main() {
    Node* head = createListFromFile("insert.txt");
    printf("Original List:\n");
    printList(head);

    insertionSort(&head);
    printf("Sorted List:\n");
    printList(head);

    writeListToFile(head, "inserted.txt");

    return 0;
}
