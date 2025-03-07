#include <stddef.h>
#include <stdlib.h>
#include <singly_linked_list.h>

SinglyLinkedList *list_create(void *(*copy) (const void *data), void (*destroy) (void *data))
{
    if ((copy && !destroy) || (!copy && destroy))
        return NULL;

    SinglyLinkedList *new_list = calloc(1, sizeof(SinglyLinkedList));
    if (!new_list)
        return NULL;

    new_list->head = NULL;
    new_list->copy = copy;
    new_list->destroy = destroy;
    new_list->size = 0;

    return new_list;
}

void list_clear(SinglyLinkedList *list)
{
    if (!list || list->size == 0)
        return;

    ListNode *temp = NULL;
    ListNode *node = list->head;

    while (node)
    {
        temp = node;
        node = node->next;
        if (list->destroy)
            list->destroy(temp->data);
        free(temp);
    }
    list->size = 0;
    list->head = NULL;
}

void list_destroy(SinglyLinkedList *list)
{
    if (!list)
        return;

    list_clear(list);
    free(list);
}

bool list_add(SinglyLinkedList *list, const void *data, size_t index)
{
    if (!list)
        return false;

    if (index > list->size)
        index = list->size;

    ListNode *new_node = calloc(1, sizeof(ListNode));
    if (!new_node)
        return false;

    if (list->copy)
    {
        new_node->data = list->copy(data);
        if (!new_node->data)
        {
            free(new_node);
            return false;
        }
    }
    else
        new_node->data = (void *) data;

    ListNode *node = list->head;

    if (index == 0)
    {
        new_node->next = list->head;
        list->head = new_node;
    }
    else
    {
        int iter = index - 1;
        for (int i = 0; i < iter; ++i)
            node = node->next;

        new_node->next = node->next;
        node->next = new_node;
    }
    ++list->size;

    return true;
}

void *list_remove(SinglyLinkedList *list, size_t index)
{
    if (!list || index >= list->size)
        return NULL;

    void *data = NULL;
    ListNode *node = list->head;

    if (index == 0)
    {
        list->head = node->next;
    }
    else
    {
        ListNode *last_node = NULL;
        for (int i = 0; i < index; ++i)
        {
            last_node = node;
            node = node->next;
        }
        last_node ->next = node->next;
    }

    data = node->data;
    free(node);
    --list->size;

    return data;
}

void *list_get(const SinglyLinkedList *list, size_t index)
{
    if (!list || index >= list->size)
        return NULL;

    ListNode *node = list->head;

    for (int i = 0; i < index; ++i)
        node = node->next;
    return node->data;
}

size_t list_size(const SinglyLinkedList *list)
{
    return list->size;
}

bool list_is_empty(const SinglyLinkedList *list)
{
    return list->size == 0;
}

ListNode *merge_sort(ListNode *start, ListNode *end, size_t len,
        int (*cmp) (const void *data_1, const void *data_2))
{
    if (len == 1)
        return start;

    size_t l_len = len / 2;
    size_t r_len = len - l_len;

    // Find the final node of the left part and
    // the first node of the right part.
    ListNode *l_end_node = start;
    for (int i = 0; i < l_len - 1; ++i)
        l_end_node = l_end_node->next;
    ListNode *r_start_node = l_end_node->next;

    // Recursively sort the left and right parts of the list
    ListNode *l_part = merge_sort(start, l_end_node, l_len, cmp);
    ListNode *r_part = merge_sort(r_start_node, end, r_len, cmp);

    // The start and end node of the sorted list.
    ListNode *new_list = NULL;
    ListNode *new_list_end = NULL;

    // Combine the right and left parts
    for (int i = 0; i < len; ++i)
    {
        // If one part runs out of elements, we simply connect
        // the other without any extra checks.
        if (l_len == 0)
        {
            new_list_end->next = r_part;
            new_list_end = r_part;
            r_part = r_part->next;
            continue;
        }
        if (r_len == 0)
        {
            new_list_end->next = l_part;
            new_list_end = l_part;
            l_part = l_part->next;
            continue;
        }

        // Compare elements from both parts using the cmp function
        // and add the smaller one to the new sorted list.
        if (cmp(l_part->data, r_part->data) == 1)
        {
            if (i == 0)
            {
                new_list = r_part;
                new_list_end = new_list;
            }
            else
            {
                new_list_end->next = r_part;
                new_list_end = r_part;
            }
            --r_len;
            r_part = r_part->next;
        }
        else
        {
            if (i == 0)
            {
                new_list = l_part;
                new_list_end = new_list;
            }
            else
            {
                new_list_end->next = l_part;
                new_list_end = l_part;
            }
            --l_len;
            l_part = l_part->next;
        }
    }

    return new_list;
}

void list_sort(SinglyLinkedList *list, int (*cmp) (const void *data_1, const void *data_2))
{
    if (!list || !cmp || list->size == 0)
        return;
    
    ListNode *end = list->head;
    while (end->next != NULL)
        end = end->next;

    list->head = merge_sort(list->head, end, list->size, cmp);

    // Set the next pointer of the last element to NULL
    ListNode *tail = list->head;
    for (int i = 0; i < list->size - 1; ++i)
        tail = tail->next;

    tail->next = NULL;
}

void list_foreach(SinglyLinkedList *list, void (*func) (void *data, void *arg), void *arg)
{
    if (!list || !func)
        return;

    ListNode *cur_node = list->head;
    while (cur_node)
    {
        func(cur_node->data, arg);
        cur_node = cur_node->next;
    }
}
