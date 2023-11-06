#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform heapify-up operation
void heapifyUp(int arr[], int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (arr[index] < arr[parentIndex])
        {
            swap(&arr[index], &arr[parentIndex]);
            index = parentIndex;
        }
        else
        {
            break;
        }
    }
}

// Function to insert an element into the min-heap
void insertIntoMinHeap(int arr[], int *heapSize, int element)
{
    // Increase the heap size and add the element at the end
    (*heapSize)++;
    int index = (*heapSize) - 1;
    arr[index] = element;

    // Perform heapify-up to maintain the min-heap property
    heapifyUp(arr, index);
}

// Function to print the min-heap
void printMinHeap(int arr[], int heapSize)
{
    printf("Min-Heap: ");
    for (int i = 0; i < heapSize; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int maxSize;
    printf("Enter the maximum number of elements in the heap: ");
    scanf("%d", &maxSize);

    int heap[maxSize];
    int heapSize = 0;

    printf("Enter the elements to build the min-heap (Enter -1 to stop):\n");
    int element;
    while (1)
    {
        scanf("%d", &element);
        if (element == -1)
        {
            break;
        }
        if (heapSize < maxSize)
        {
            insertIntoMinHeap(heap, &heapSize, element);
            printMinHeap(heap, heapSize);
        }
        else
        {
            printf("Heap is full. Cannot insert more elements.\n");
            break;
        }
    }

    return 0;
}
