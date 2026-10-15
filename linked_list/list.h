#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/* A singly linked list of ints.
 *
 * Ownership rule: the list owns every node it creates.
 * list_remove frees the node it removes; list_destroy frees all the rest.
 * After list_destroy(l), the pointer l must not be used again.
 */

typedef struct list list;

list  *list_create(void);                       /* NULL if out of memory   */
int    list_push_front(list *l, int value);     /* 0 = ok, -1 = no memory  */
int    list_push_back(list *l, int value);      /* 0 = ok, -1 = no memory  */
int    list_contains(const list *l, int value); /* 1 = found, 0 = not      */
int    list_remove(list *l, int value);         /* 1 = removed first match,
                                                   0 = value not in list   */
int    list_get(const list *l, size_t index, int *out); /* 0 = ok, -1 = bad index */
size_t list_length(const list *l);
void   list_print(const list *l);               /* prints: 1 -> 2 -> 3     */
void   list_destroy(list *l);                   /* frees every node + list */

#endif
