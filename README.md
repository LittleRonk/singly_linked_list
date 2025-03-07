# Singly Linked List in C

A simple and efficient implementation of a singly linked list in C.

## Features
- Add elements at any position.
- Remove elements by index.
- Sort the list using a custom comparison function.
- Iterate over the list with a callback function.

## Usage

### Building the Project

```bash
mkdir build
cd build
cmake ..
make
```

### Running the Example

After building the project, you can run the example driver program:

```bash
./driver
```

### Example Code

Here is an example of how to use the doubly linked list:

```c
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <singly_linked_list.h>

void *copy_item(const void *);
void destroy_item(void *);
void print_item(void *, void *arg);
int cmp(const void *, const void *);

int main(void)
{
    int x = 30;
    int y = 20;
    int z = 10;
    int f = 5;

    SinglyLinkedList *list = list_create(copy_item, destroy_item);
    if (!list)
    {
        fprintf(stderr, "failed to creare list");
        return 1;
    }

    list_add(list, &x, 0);
    list_add(list, &y, 1);
    list_add(list, &z, 2);
    list_add(list, &f, 3);

    list_foreach(list, print_item, NULL); // 30 20 10 5
    putchar('\n');

    list_add(list, &x, 2);
    list_sort(list, cmp);
    printf("\nthe list has been sorted\n");
    list_foreach(list, print_item, NULL); // 5 10 20 30 30
    putchar('\n');
    printf("list size: %zu\n", list_size(list));

    destroy_item(list_remove(list, 3));
    printf("\nthe element at index 3 was deleted\n");
    list_foreach(list, print_item, NULL);
    putchar('\n');
    printf("list size: %zu\n", list_size(list));

    list_clear(list);
    printf("\nthe list has been cleared\n");
    printf("list size: %zu\n", list_size(list));
    list_destroy(list);
}

void *copy_item(const void *data)
{
    int *copy = calloc(1, sizeof(int));
    if (!copy)
        return NULL;
    *copy = *((int *) data);

    return copy;
}

void destroy_item(void *data)
{
    free((int *) data);
}

void print_item(void *data, void *arg)
{
    printf("%d ", *((int *) data));
}

int cmp(const void *data_1, const void *data_2)
{
    if (*(int *) data_1 > *(int *) data_2)
        return 1;
    else if (*(int *) data_1 < *(int *) data_2)
        return -1;
    return 0;
}
```

## API Documentation

### Structures

- **ListNode**: Represents a node in the singly linked list.
- **SinglyLinkedList**: Represents singly linked list itself.

### Functions

- **list_create**: Creates a new singly linked list.
- **list_clear**: Clears all element from the list.
- **list_destroy**: Destroys the list and frees all allocated memory.
- **list_add**: Inserts an element at a specified index.
- **list_remove**: Removes and returns an element at a specified index.
- **list_get**: Retrieves the element at a specified index.
- **list_size**: Returns the number of elements in the list.
- **list_is_empty**: Returns 'true' if the list is empty, otherwise 'false'.
- **list_sort**: Sort the list using merge sort.
- **list_foreach**: Applies a function to each element in the list.
