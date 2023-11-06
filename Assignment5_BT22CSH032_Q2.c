#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to delete the maximum element from a min-max heap
void delete_max(int heap[], int *heapSize)
{
    if (*heapSize == 0)
    {
        printf("Heap is empty. Cannot delete.\n");
        return;
    }

    // Find the index of the maximum element (odd-level node)
    int maxIndex = 1; // Assume it's the left child of the root
    if (*heapSize >= 3 && heap[2] > heap[maxIndex])
    {
        maxIndex = 2; // Right child of the root has a greater value
    }

    // Swap the maximum element with its parent until it reaches the root
    while (maxIndex > 0)
    {
        int parentIndex = (maxIndex - 1) / 2;
        swap(&heap[maxIndex], &heap[parentIndex]);
        maxIndex = parentIndex;
    }

    // Remove the maximum element (now at the root)
    int maxElement = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;

    // Restore the min-max heap properties
    int currentIndex = 0;
    int child1, child2;
    while (1)
    {
        child1 = 2 * currentIndex + 1;
        child2 = 2 * currentIndex + 2;

        // Find the index of the minimum child
        int minChildIndex = child1;
        if (child2 < *heapSize && heap[child2] < heap[child1])
        {
            minChildIndex = child2;
        }

        // If the min-max heap property is violated, swap with the smaller child
        if (minChildIndex < *heapSize && heap[minChildIndex] < heap[currentIndex])
        {
            swap(&heap[currentIndex], &heap[minChildIndex]);
            currentIndex = minChildIndex;
        }
        else
        {
            break;
        }
    }

    printf("Deleted max element: %d\n", maxElement);
}

// Function to print the min-max heap
void printMinMaxHeap(int heap[], int heapSize)
{
    printf("Min-Max Heap: ");
    for (int i = 0; i < heapSize; i++)
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main()
{
    int maxSize;
    printf("Enter the maximum number of elements in the min-max heap: ");
    scanf("%d", &maxSize);

    int minMaxHeap[maxSize];
    int heapSize = 0;

    printf("Enter the elements to build the min-max heap (Enter -1 to stop):\n");
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
            minMaxHeap[heapSize++] = element;
            printMinMaxHeap(minMaxHeap, heapSize);
        }
        else
        {
            printf("Heap is full. Cannot insert more elements.\n");
            break;
        }
    }

    // Delete the maximum element from the min-max heap
    delete_max(minMaxHeap, &heapSize);
    printMinMaxHeap(minMaxHeap, heapSize);

    return 0;
}
