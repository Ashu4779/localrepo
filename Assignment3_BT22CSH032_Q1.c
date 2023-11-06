#include <stdio.h>
#include <stdlib.h>

// Structure to represent a non-zero element in the sparse matrix
struct Node
{
    int row;
    int col;
    int value;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int row, int col, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to display the linked list representation of the sparse matrix
void displaySparseMatrix(struct Node *head)
{
    struct Node *current = head;
    printf("Row\tColumn\tValue\n");

    while (current != NULL)
    {
        printf("%d\t%d\t%d\n", current->row, current->col, current->value);
        current = current->next;
    }
}

int main()
{
    int rows, cols;
    printf("Enter the number of rows and columns in the sparse matrix: ");
    scanf("%d %d", &rows, &cols);

    // Initialize a pointer to the head of the linked list
    struct Node *head = NULL;

    printf("Enter the elements of the sparse matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int element;
            scanf("%d", &element);

            // If the element is non-zero, add it to the linked list
            if (element != 0)
            {
                struct Node *newNode = createNode(i, j, element);
                newNode->next = head;
                head = newNode;
            }
        }
    }

    // Display the linked list representation of the sparse matrix
    printf("Linked List Representation of Sparse Matrix:\n");
    displaySparseMatrix(head);

    // Free the allocated memory for the linked list
    while (head != NULL)
    {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
