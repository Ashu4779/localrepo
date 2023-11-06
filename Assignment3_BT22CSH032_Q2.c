#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a linked list
struct Node
{
    int data;
    struct Node *next;
};

// Function to create a new node with a given data value
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of a linked list
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print a linked list
void printLinkedList(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to add two long integers represented as linked lists
struct Node *addLongIntegers(struct Node *num1, struct Node *num2)
{
    struct Node *result = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry != 0)
    {
        int sum = carry;
        if (num1 != NULL)
        {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL)
        {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        int digit = sum % 10;
        insertAtEnd(&result, digit);
    }

    return result;
}

int main()
{
    // Input two long integers as linked lists
    struct Node *num1 = NULL;
    struct Node *num2 = NULL;

    // You can populate num1 and num2 with digits here using insertAtEnd function

    // Example:
    insertAtEnd(&num1, 3);
    insertAtEnd(&num1, 2);
    insertAtEnd(&num1, 1);

    insertAtEnd(&num2, 5);
    insertAtEnd(&num2, 4);
    insertAtEnd(&num2, 9);

    // Add the long integers and store the result in a linked list
    struct Node *result = addLongIntegers(num1, num2);

    // Print the result
    printf("Result: ");
    printLinkedList(result);

    // Free the allocated memory for the linked lists
    while (num1 != NULL)
    {
        struct Node *temp = num1;
        num1 = num1->next;
        free(temp);
    }

    while (num2 != NULL)
    {
        struct Node *temp = num2;
        num2 = num2->next;
        free(temp);
    }

    while (result != NULL)
    {
        struct Node *temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}
