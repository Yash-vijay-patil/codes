#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insertNode(Node* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && data < node->left->data)
        return rotateRight(node);

    if (balanceFactor < -1 && data > node->right->data)
        return rotateLeft(node);

    if (balanceFactor > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void inOrderTraversal(Node* root, FILE* file) {
    if (root != NULL) {
        inOrderTraversal(root->left, file);
        fprintf(file, "%d ", root->data);
        inOrderTraversal(root->right, file);
    }
}

void preOrderTraversal(Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->data);
        preOrderTraversal(root->left, file);
        preOrderTraversal(root->right, file);
    }
}

void postOrderTraversal(Node* root, FILE* file) {
    if (root != NULL) {
        postOrderTraversal(root->left, file);
        postOrderTraversal(root->right, file);
        fprintf(file, "%d ", root->data);
    }
}

void generateRandomNumbers(int count) {
    FILE* inputFile = fopen("input.txt", "w");

    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int num = rand() % 100;
        fprintf(inputFile, "%d ", num);
    }

    fclose(inputFile);
    printf("%d random numbers generated and stored in 'input.txt'.\n", count);
}

Node* readDataFromFile(FILE* file) {
    int data;
    Node* root = NULL;

    while (fscanf(file, "%d", &data) != EOF) {
        root = insertNode(root, data);
    }

    return root;
}

void displayTree(struct Node* root, int space) {
    if (root == NULL)
        return;
    space += 10;

    displayTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    displayTree(root->left, space);
}

int main() {
    Node* root = NULL;
    int choice, data, count;
    FILE* inputFile = fopen("input.txt", "r");
    FILE* inOrderFile = fopen("inorder.txt", "w");
    FILE* preOrderFile = fopen("preorder.txt", "w");
    FILE* postOrderFile = fopen("postorder.txt", "w");

    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return 0;
    }

    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &count);

    generateRandomNumbers(count);

    inputFile = fopen("input.txt", "r");

    root = readDataFromFile(inputFile);
    fclose(inputFile);

    do {

        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. In-order traversal\n");
        printf("4. Pre-order traversal\n");
        printf("5. Post-order traversal\n");
        printf("6. Display the AVL tree\n");
        printf("7. Save traversal data\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                printf("Node inserted successfully.\n");
                break;
            case 2:
                // Implement delete operation if needed
                break;
            case 3:
                printf("In-order traversal: ");
                inOrderTraversal(root, stdout);
                printf("\n");
                break;
            case 4:
                printf("Pre-order traversal: ");
                preOrderTraversal(root, stdout);
                printf("\n");
                break;
            case 5:
                printf("Post-order traversal: ");
                postOrderTraversal(root, stdout);
                printf("\n");
                break;
            case 6:
                printf("AVL Tree:\n");
                displayTree(root, 0);
                break;
            case 7:
                inOrderTraversal(root, inOrderFile);
                preOrderTraversal(root, preOrderFile);
                postOrderTraversal(root, postOrderFile);
                printf("Traversal data saved to files: 'inorder.txt', 'preorder.txt', 'postorder.txt'\n");
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 8);

    fclose(inOrderFile);
    fclose(preOrderFile);
    fclose(postOrderFile);

    return 0;
}
