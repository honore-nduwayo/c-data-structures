#include "list.h"

#include <stdio.h>
#include <stdlib.h>

/* One "box" in the chain: a value plus an arrow to the next box. */
typedef struct node {
    int value;
    struct node *next;   /* NULL means "this is the last box" */
} node;

/* The list itself: an arrow to the first box, and a count. */
struct list {
    node *head;          /* NULL means "the list is empty" */
    size_t length;
};

list *list_create(void)
{
    list *l = malloc(sizeof *l);
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;      /* empty list: no first box yet */
    l->length = 0;
    return l;
}

int list_push_front(list *l, int value)
{
    node *n = malloc(sizeof *n);
    if (n == NULL) {
        return -1;
    }
    n->value = value;

    /* Order matters. First, the new box grabs the hand of the old first box... */
    n->next = l->head;
    /* ...and only then does the "start here" arrow move to the new box.
     * Doing these two lines the other way round would lose the whole list. */
    l->head = n;

    l->length++;
    return 0;
}

int list_push_back(list *l, int value)
{
    node *n = malloc(sizeof *n);
    if (n == NULL) {
        return -1;
    }
    n->value = value;
    n->next = NULL;      /* the new box will be last, so it points nowhere */

    if (l->head == NULL) {
        l->head = n;     /* empty list: the new box is also the first box */
    } else {
        node *cur = l->head;
        while (cur->next != NULL) {   /* walk to the last box */
            cur = cur->next;
        }
        cur->next = n;   /* hook the new box onto the end */
    }

    l->length++;
    return 0;
}

int list_contains(const list *l, int value)
{
    for (const node *cur = l->head; cur != NULL; cur = cur->next) {
        if (cur->value == value) {
            return 1;
        }
    }
    return 0;
}

int list_remove(list *l, int value)
{
    node *prev = NULL;   /* the box just before cur (NULL if cur is the first) */
    node *cur = l->head;

    while (cur != NULL) {
        if (cur->value == value) {
            /* Rewire first: make the chain skip over cur. */
            if (prev == NULL) {
                l->head = cur->next;     /* removing the first box: move the start arrow */
            } else {
                prev->next = cur->next;  /* removing a later box: previous box skips it */
            }
            /* Only now is cur disconnected, so it is safe to free it. */
            free(cur);
            l->length--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;            /* walked off the end: value was not there */
}

int list_get(const list *l, size_t index, int *out)
{
    if (index >= l->length) {
        return -1;
    }
    const node *cur = l->head;
    for (size_t i = 0; i < index; i++) {
        cur = cur->next;
    }
    *out = cur->value;
    return 0;
}

size_t list_length(const list *l)
{
    return l->length;
}

void list_print(const list *l)
{
    if (l->head == NULL) {
        printf("(empty)\n");
        return;
    }
    for (const node *cur = l->head; cur != NULL; cur = cur->next) {
        printf("%d", cur->value);
        if (cur->next != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void list_destroy(list *l)
{
    node *cur = l->head;
    while (cur != NULL) {
        node *next = cur->next;  /* save the arrow BEFORE freeing the box */
        free(cur);               /* after this, cur->next would be invalid */
        cur = next;
    }
    free(l);                     /* finally free the list itself */
}
