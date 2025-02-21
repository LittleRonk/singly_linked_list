#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "singly_linked_list.h"

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
    if (!list)
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
    if (!list || !data)
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
    //printf("start: %d - stop: %d\n", *((int *) start->data), *((int *) end->data));
    if (len == 1)
        return start;

    size_t l_len = len / 2;
    size_t r_len = len - l_len;
    ListNode *l_end_node = start;

    for (int i = 0; i < l_len - 1; ++i)
        l_end_node = l_end_node->next;
    ListNode *r_start_node = l_end_node->next;

    ListNode *l_part = merge_sort(start, l_end_node, l_len, cmp);
    ListNode *r_part = merge_sort(r_start_node, end, r_len, cmp);
    ListNode *new_part = NULL;
    ListNode *cur_node = NULL;

    //printf("l_part: %d - r_part: %d\n", *((int *) l_part->data), *((int *) r_part->data));
    for (int i = 0; i < len; ++i)
    {
        if (l_len == 0)
        {
            cur_node->next = r_part;
            cur_node = r_part;
            r_part = r_part->next;
            continue;
        }
        if (r_len == 0)
        {
            cur_node->next = l_part;
            cur_node = l_part;
            l_part = l_part->next;
            continue;
        }

        if (cmp(l_part->data, r_part->data) == -1)
        {
            if (i == 0)
            {
                new_part = r_part;
                cur_node = new_part;
            }
            else
            {
                cur_node->next = r_part;
                cur_node = r_part;
            }
            --r_len;
            r_part = r_part->next;
        }
        else if (cmp(l_part->data, r_part->data) >= 0)
        {
            if (i == 0)
            {
                new_part = l_part;
                cur_node = new_part;
            }
            else
            {
                cur_node->next = l_part;
                cur_node = l_part;
            }
            --l_len;
            l_part = l_part->next;
        }
    }

    return new_part;
}

void list_sort(SinglyLinkedList *list, int (*cmp) (const void *data_1, const void *data_2))
{
    if (!list || !cmp)
        return;
    
    ListNode *end = list->head;
    while (end->next != NULL)
        end = end->next;

    list->head = merge_sort(list->head, end, list->size, cmp);
    ListNode *tail = list->head;
    for (int i = 0; i <= list->size; ++i)
        tail = tail->next;

    tail->next = NULL;
}

void list_foreach(SinglyLinkedList *list, void (*func) (void *data, void *arg), void *arg)
{
    ListNode *cur_node = list->head;
    while (cur_node)
    {
        func(cur_node->data, arg);
        cur_node = cur_node->next;
    }
}
