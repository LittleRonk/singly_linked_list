#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Definition of a singly linked list node.
 */
typedef struct ListNode {
    void *data;              ///< Pointer to the stored data.
    struct ListNode *next;   ///< Pointer to the next node.
} ListNode;

/**
 * @brief Definition of a singly linked list.
 */
typedef struct {
    ListNode *head;           ///< Pointer to the first node.
    size_t size;              ///< Number of elements in the list.
    void *(*copy)(const void *);  ///< Function for copying data (can be NULL for shallow copy).
    void (*destroy)(void *);      ///< Function for freeing data (can be NULL if no special cleanup is needed).
} SinglyLinkedList;

/**
 * @brief Initializes an empty singly linked list.
 *
 * @param copy Function pointer for copying data (optional, can be NULL).
 * @param destroy Function pointer for destroying data (optional, can be NULL).
 * @return Pointer to the initialized list or NULL on failure.
 */
SinglyLinkedList *list_create(void *(*copy)(const void *), void (*destroy)(void *));

/**
 * @brief Clears all elements from the list without destroying the list itself.
 *
 * This function removes all elements, applying the `destroy` function if provided.
 * The list remains valid for future use.
 *
 * @param list Pointer to the list.
 */
void list_clear(SinglyLinkedList *list);

/**
 * @brief Destroys the list and frees all allocated memory.
 *
 * The user is responsible for ensuring that all references to stored data are cleared.
 *
 * @param list Pointer to the list.
 */
void list_destroy(SinglyLinkedList *list);

/**
 * @brief Adds an element at the specified index in the list.
 *
 * If the index is greater than the current size, the element is added at the end.
 *
 * @param list Pointer to the list.
 * @param data Pointer to the data to insert.
 * @param index Position to insert at (0-based).
 * @return true on success, false on failure.
 */
bool list_add(SinglyLinkedList *list, const void *data, size_t index);

/**
 * @brief Removes an element from the specified index in the list.
 *
 * The user is responsible for freeing the returned data if necessary.
 *
 * @param list Pointer to the list.
 * @param index Position of the element to remove (0-based).
 * @return Pointer to the removed data, or NULL if index is invalid.
 */
void *list_remove(SinglyLinkedList *list, size_t index);

/**
 * @brief Retrieves an element at the specified index in the list.
 *
 * @param list Pointer to the list.
 * @param index Position of the element to retrieve (0-based).
 * @return Pointer to the data, or NULL if index is invalid.
 */
void *list_get(const SinglyLinkedList *list, size_t index);

/**
 * @brief Returns the number of elements in the list.
 *
 * @param list Pointer to the list.
 * @return The number of elements in the list.
 */
size_t list_size(const SinglyLinkedList *list);

/**
 * @brief Checks if the list is empty.
 *
 * @param list Pointer to the list.
 * @return true if empty, false otherwise.
 */
bool list_is_empty(const SinglyLinkedList *list);

/**
 * @brief Sorts the list using a comparison function.
 *
 * The comparison function should follow the convention of `qsort`:
 * - Returns a negative value if a < b
 * - Returns 0 if a == b
 * - Returns a positive value if a > b
 *
 * @param list Pointer to the list.
 * @param cmp Comparison function.
 */
void list_sort(SinglyLinkedList *list, int (*cmp)(const void *, const void *));

/**
 * @brief Iterates over each element in the list and applies a given function.
 *
 * The function receives a pointer to each element's data and an optional user-provided argument.
 *
 * @param list Pointer to the list.
 * @param func Function to apply to each element.
 * @param arg Optional user-provided argument passed to the function (can be NULL).
 */
void list_foreach(SinglyLinkedList *list, void (*func)(void *, void *), void *arg);

#endif // SINGLY_LINKED_LIST_H
