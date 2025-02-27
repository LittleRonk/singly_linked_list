#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <singly_linked_list.h>

// Comparison function for sorting
int cmp(const void *data_1, const void *data_2);

// Function to print an element
void el_print(void *data, void *arg);

int main(void)
{
    // Test data
    int x = 7;
    int y = 3;
    int z = 2;
    int a = 5;
    int b = 9;
    int c = 8;
    int d = 1;
    int e = 4;
    int f = 0;
    int g = 6;

    // Creating a list with shallow copying of elements
    SinglyLinkedList *list = list_create(NULL, NULL);
    if (!list)
    {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    // Add elements to the list
    list_add(list, &g, 0);
    list_add(list, &f, 0);
    list_add(list, &e, 0);
    list_add(list, &d, 0);
    list_add(list, &c, 0);
    list_add(list, &b, 0);
    list_add(list, &a, 0);
    list_add(list, &z, 0);
    list_add(list, &y, 0);
    list_add(list, &x, 0);
    list_add(list, &x, 0);

    // Print the initial list
    printf("Initial list:\n");
    printf("List size: %zu\n", list_size(list));
    list_foreach(list, el_print, NULL);
    printf("**********\n");

    // Sorte the list
    list_sort(list, cmp);

    // Print the sorted list
    printf("Sorted list (descending order):\n");
    printf("List size: %zu\n", list_size(list));
    list_foreach(list, el_print, NULL);

    // Clean up
    list_destroy(list);
    return 0;
}

// Comparison function for sorting in descending order
int cmp(const void *data_1, const void *data_2)
{
    int *d_1 = (int *) data_1;
    int *d_2 = (int *) data_2;

    if (*d_1 > *d_2)
        return -1; // Sort in descending order
    else if (*d_1 < *d_2)
        return 1;
    return 0;
}

// Function to print an element
void el_print(void *data, void *arg)
{
    printf("%d\n", *((int *) data));
}
