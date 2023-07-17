#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, char data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

void preorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%c ", root->data);
        preorderTraversal(root->left, file);
        preorderTraversal(root->right, file);
    }
}

void inorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        inorderTraversal(root->left, file);
        fprintf(file, "%c ", root->data);
        inorderTraversal(root->right, file);
    }
}

void postorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        postorderTraversal(root->left, file);
        postorderTraversal(root->right, file);
        fprintf(file, "%c ", root->data);
    }
}

void generateRandomCharsToFile(const char* filename, int numChars) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    for (int i = 0; i < numChars; i++) {
        char randomChar = 'A' + rand() % 26;
        fprintf(file, "%c ", randomChar);
    }

    fclose(file);
}

int main() {
    const char* filename = "random_chars.txt";
    int numChars = 10;
    generateRandomCharsToFile(filename, numChars);

    FILE* inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    struct Node* root = NULL;
    char data;
    while (fscanf(inputFile, "%c ", &data) != EOF) {
        root = insert(root, data);
    }
    fclose(inputFile);

    clock_t startTime, endTime;
    double timeTaken;

    FILE* preorderFile = fopen("preorder_output.txt", "w");
    startTime = clock();
    preorderTraversal(root, preorderFile);
    endTime = clock();
    timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Pre-order traversal completed. Time taken: %lf seconds.\n", timeTaken);
    fclose(preorderFile);

    FILE* inorderFile = fopen("inorder_output.txt", "w");
    startTime = clock();
    inorderTraversal(root, inorderFile);
    endTime = clock();
    timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("In-order traversal completed. Time taken: %lf seconds.\n", timeTaken);
    fclose(inorderFile);

    FILE* postorderFile = fopen("postorder_output.txt", "w");
    startTime = clock();
    postorderTraversal(root, postorderFile);
    endTime = clock();
    timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Post-order traversal completed. Time taken: %lf seconds.\n", timeTaken);
    fclose(postorderFile);

    return 0;
}
