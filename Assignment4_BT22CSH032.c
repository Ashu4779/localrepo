#include <stdio.h>
#include <stdlib.h>

// Structure for a doubly linked list node
struct Node
{
    int data;          // 4-digit number
    struct Node *next; // Pointer to the next node
    struct Node *prev; // Pointer to the previous node
};

// Function to create a new node with a 4-digit number
struct Node *createNode(int num)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = num;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to add two numbers represented by linked lists
struct Node *addNumbers(struct Node *num1, struct Node *num2)
{
    struct Node *result = NULL;
    struct Node *carryNode = NULL;
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

        carry = sum / 10000;     // Calculate carry for the next iteration
        int digit = sum % 10000; // Store the 4-digit result

        // Create a new node for the result and add it to the front of the result list
        struct Node *newNode = createNode(digit);
        newNode->next = result;
        if (result != NULL)
        {
            result->prev = newNode;
        }
        result = newNode;
    }

    return result;
}

// Function to print a number represented by a linked list
void printNumber(struct Node *num)
{
    while (num != NULL)
    {
        printf("%04d -> ", num->data);
        num = num->next;
    }
    printf("NULL\n");
}

int main()
{
    // Input two numbers as strings
    char num1Str[] = "681325468132";
    char num2Str[] = "123456789012";

    // Initialize pointers for the linked lists
    struct Node *num1 = NULL;
    struct Node *num2 = NULL;

    // Convert the input strings into linked lists
    for (int i = 0; num1Str[i] != '\0'; i += 4)
    {
        int num;
        sscanf(&num1Str[i], "%4d", &num);
        struct Node *newNode = createNode(num);
        newNode->next = num1;
        if (num1 != NULL)
        {
            num1->prev = newNode;
        }
        num1 = newNode;
    }

    for (int i = 0; num2Str[i] != '\0'; i += 4)
    {
        int num;
        sscanf(&num2Str[i], "%4d", &num);
        struct Node *newNode = createNode(num);
        newNode->next = num2;
        if (num2 != NULL)
        {
            num2->prev = newNode;
        }
        num2 = newNode;
    }

    // Print the original numbers
    printf("Number 1: ");
    printNumber(num1);
    printf("Number 2: ");
    printNumber(num2);

    // Add the numbers and print the result
    struct Node *result = addNumbers(num1, num2);
    printf("Sum: ");
    printNumber(result);

    // Free memory for the linked lists
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
