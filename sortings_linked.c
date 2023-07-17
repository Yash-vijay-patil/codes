#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node* next;
} Node;
void swap(Node* a, Node* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
void bubbleSort(Node* head) {
    int swapped, i;
    Node* ptr1;
    Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
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
void selectionSort(Node** head) {
    Node* current = *head;
    Node* min;

    while (current != NULL) {
        min = current;

        Node* ptr = current->next;
        while (ptr != NULL) {
            if (ptr->data < min->data) {
                min = ptr;
            }
            ptr = ptr->next;
        }

        if (min != current) {
            swap(current, min);
        }
        current = current->next;
    }
}

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
    if (fp == NULL)
        {
        printf("Error opening file\n");
    }
}

