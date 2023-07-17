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

int main() {
    Node* head = createListFromFile("bubblesort.txt");
    printf("Before sorting:\n");
    printList(head);

    bubbleSort(head);

    printf("After sorting:\n");
    printList(head);

    writeListToFile(head, "sortedbubble.txt");

    return 0;
}
