#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a term of the polynomial
typedef struct Node
{
    float coefficient;
    int exponent;
    struct Node *next;
} Node;

// Function to read and create a polynomial using circular linked list
Node *Pread()
{
    int n;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    Node *header = (Node *)malloc(sizeof(Node)); // Header node
    header->next = header;                       // Circular linking

    Node *current = header;

    for (int i = 0; i < n; i++)
    {
        Node *term = (Node *)malloc(sizeof(Node));
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%f %d", &term->coefficient, &term->exponent);

        current->next = term;
        term->next = header; // Circular linking
        current = term;
    }

    return header;
}

// Function to output the polynomial in mathematical form
void Pwrite(Node *header)
{
    Node *current = header->next;

    while (current != header)
    {
        printf("%.2fx^%d", current->coefficient, current->exponent);

        current = current->next;

        if (current != header)
        {
            if (current->coefficient >= 0)
            {
                printf(" + ");
            }
            else
            {
                printf(" - ");
            }
        }
    }

    printf("\n");
}

// Function to compute c = a + b
Node *Padd(Node *a, Node *b)
{
    Node *cHeader = (Node *)malloc(sizeof(Node));
    cHeader->next = cHeader;

    Node *ca = a->next;
    Node *cb = b->next;

    while (ca != a && cb != b)
    {
        Node *term = (Node *)malloc(sizeof(Node));

        if (ca->exponent > cb->exponent)
        {
            term->coefficient = ca->coefficient;
            term->exponent = ca->exponent;
            ca = ca->next;
        }
        else if (cb->exponent > ca->exponent)
        {
            term->coefficient = cb->coefficient;
            term->exponent = cb->exponent;
            cb = cb->next;
        }
        else
        {
            term->coefficient = ca->coefficient + cb->coefficient;
            term->exponent = ca->exponent;
            ca = ca->next;
            cb = cb->next;
        }

        cHeader->next = term;
        term->next = cHeader;
        cHeader = term;
    }

    while (ca != a)
    {
        Node *term = (Node *)malloc(sizeof(Node));
        term->coefficient = ca->coefficient;
        term->exponent = ca->exponent;
        ca = ca->next;

        cHeader->next = term;
        term->next = cHeader;
        cHeader = term;
    }

    while (cb != b)
    {
        Node *term = (Node *)malloc(sizeof(Node));
        term->coefficient = cb->coefficient;
        term->exponent = cb->exponent;
        cb = cb->next;

        cHeader->next = term;
        term->next = cHeader;
        cHeader = term;
    }

    return cHeader;
}

// Function to compute c = a - b
Node *Psub(Node *a, Node *b)
{
    Node *cHeader = (Node *)malloc(sizeof(Node));
    cHeader->next = cHeader;

    Node *ca = a->next;
    Node *cb = b->next;

    while (ca != a && cb != b)
    {
        Node *term = (Node *)malloc(sizeof(Node));

        if (ca->exponent > cb->exponent)
        {
            term->coefficient = ca->coefficient;
            term->exponent = ca->exponent;
            ca = ca->next;
        }
        else if (cb->exponent > ca->exponent)
        {
            term->coefficient = -cb->coefficient;
            term->exponent = cb->exponent;
            cb = cb->next;
        }
        else
        {
            term->coefficient = ca->coefficient - cb->coefficient;
            term->exponent = ca->exponent;
            ca = ca->next;
            cb = cb->next;
        }

        cHeader->next = term;
        term->next = cHeader;
        cHeader = term;
    }

    while (ca != a)
    {
        Node *term = (Node *)malloc(sizeof(Node));
        term->coefficient = ca->coefficient;
        term->exponent = ca->exponent;
        ca = ca->next;

        cHeader->next = term;
        term->next = cHeader;
        cHeader = term;
    }

    while (cb != b)
    {
        Node *term = (Node *)malloc(sizeof(Node));
        term->coefficient = -cb->coefficient;
        term->exponent = cb->exponent;
        cb = cb->next;

        cHeader->next = term;
        term->next = cHeader;
        cHeader = term;
    }

    return cHeader;
}

// Function to compute c = a * b
Node *Pmult(Node *a, Node *b)
{
    Node *cHeader = (Node *)malloc(sizeof(Node));
    cHeader->next = cHeader;

    Node *ca = a->next;

    while (ca != a)
    {
        Node *cb = b->next;

        while (cb != b)
        {
            Node *term = (Node *)malloc(sizeof(Node));
            term->coefficient = ca->coefficient * cb->coefficient;
            term->exponent = ca->exponent + cb->exponent;

            // Insert the term into c polynomial
            Node *cCurrent = cHeader;
            while (cCurrent->next != cHeader && cCurrent->next->exponent > term->exponent)
            {
                cCurrent = cCurrent->next;
            }

            term->next = cCurrent->next;
            cCurrent->next = term;

            cb = cb->next;
        }

        ca = ca->next;
    }

    return cHeader;
}

// Function to evaluate the polynomial at a point
float Peval(Node *header, float a)
{
    Node *current = header->next;
    float result = 0.0;

    while (current != header)
    {
        result += current->coefficient * pow(a, current->exponent);
        current = current->next;
    }

    return result;
}

// Function to erase a certain term of the polynomial
void Perase(Node *header, int exponent)
{
    Node *current = header->next;
    Node *previous = header;

    while (current != header)
    {
        if (current->exponent == exponent)
        {
            previous->next = current->next;
            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }
}

// Function to free memory allocated for the linked list
void Pdestroy(Node *header)
{
    Node *current = header->next;

    while (current != header)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    free(header);
}

int main()
{
    Node *a = Pread();
    Node *b = Pread();

    printf("Polynomial A: ");
    Pwrite(a);

    printf("Polynomial B: ");
    Pwrite(b);

    Node *c = Padd(a, b);
    printf("Polynomial C (A + B): ");
    Pwrite(c);

    Node *d = Psub(a, b);
    printf("Polynomial D (A - B): ");
    Pwrite(d);

    Node *e = Pmult(a, b);
    printf("Polynomial E (A * B): ");
    Pwrite(e);

    float evalPoint;
    printf("Enter a point for polynomial evaluation: ");
    scanf("%f", &evalPoint);
    printf("Evaluation of A at %.2f: %.2f\n", evalPoint, Peval(a, evalPoint));
    printf("Evaluation of B at %.2f: %.2f\n", evalPoint, Peval(b, evalPoint));
    printf("Evaluation of C at %.2f: %.2f\n", evalPoint, Peval(c, evalPoint));

    int eraseExponent;
    printf("Enter the exponent to erase from polynomial A: ");
    scanf("%d", &eraseExponent);
    Perase(a, eraseExponent);
    printf("Polynomial A after erasing term with exponent %d: ", eraseExponent);
    Pwrite(a);

    // Free memory
    Pdestroy(a);
    Pdestroy(b);
    Pdestroy(c);
    Pdestroy(d);
    Pdestroy(e);

    return 0;
}
