#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

void preOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->data);
        preOrder(root->left, file);
        preOrder(root->right, file);
    }
}

void postOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        postOrder(root->left, file);
        postOrder(root->right, file);
        fprintf(file, "%d ", root->data);
    }
}

void inOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        inOrder(root->left, file);
        fprintf(file, "%d ", root->data);
        inOrder(root->right, file);
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    FILE* inputFile = fopen("random_numbers.txt", "w");
    if (inputFile == NULL) {
        printf("Error opening file.");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < 99999; i++) {
        int randomNumber = rand() % 100;
        fprintf(inputFile, "%d ", randomNumber);
    }

    fclose(inputFile);

    FILE* inputFileRead = fopen("random_numbers.txt", "r");
    if (inputFileRead == NULL) {
        printf("Error opening file.");
        return 1;
    }

    struct Node* root = NULL;
    int data;

    while (fscanf(inputFileRead, "%d", &data) != EOF) {
        root = insert(root, data);
    }

    fclose(inputFileRead);

    FILE* preOrderFile = fopen("pre_order.txt", "w");
    if (preOrderFile == NULL) {
        printf("Error opening file.");
        return 1;
    }

    start = clock();
    preOrder(root, preOrderFile);
    end = clock();

    fclose(preOrderFile);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Pre-order traversal time: %f seconds\n", cpu_time_used);

    FILE* postOrderFile = fopen("post_order.txt", "w");
    if (postOrderFile == NULL) {
        printf("Error opening file.");
        return 1;
    }

    start = clock();
    postOrder(root, postOrderFile);
    end = clock();

    fclose(postOrderFile);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Post-order traversal time: %f seconds\n", cpu_time_used);

    FILE* inOrderFile = fopen("in_order.txt", "w");
    if (inOrderFile == NULL) {
        printf("Error opening file.");
        return 1;
    }

    start = clock();
    inOrder(root, inOrderFile);
    end = clock();

    fclose(inOrderFile);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("In-order traversal time: %f seconds\n", cpu_time_used);

    return 0;
}
