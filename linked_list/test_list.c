#include "list.h"

#include <assert.h>
#include <stdio.h>

/* Check that the list holds exactly the values in expected[] (in order). */
static void expect(const list *l, const int *expected, size_t n)
{
    assert(list_length(l) == n);
    for (size_t i = 0; i < n; i++) {
        int v;
        assert(list_get(l, i, &v) == 0);
        assert(v == expected[i]);
    }
}

static void test_empty(void)
{
    list *l = list_create();
    assert(l != NULL);
    assert(list_length(l) == 0);
    assert(!list_contains(l, 1));
    assert(list_remove(l, 1) == 0);      /* removing from empty: no crash */
    int v;
    assert(list_get(l, 0, &v) == -1);
    list_print(l);
    list_destroy(l);
}

static void test_push(void)
{
    list *l = list_create();
    list_push_back(l, 2);
    list_push_back(l, 3);
    list_push_front(l, 1);
    list_push_front(l, 0);
    int expected[] = {0, 1, 2, 3};
    expect(l, expected, 4);
    assert(list_contains(l, 3));
    assert(!list_contains(l, 9));
    list_print(l);
    list_destroy(l);
}

static void test_remove(void)
{
    list *l = list_create();
    for (int i = 1; i <= 5; i++) {
        list_push_back(l, i);            /* 1 2 3 4 5 */
    }
    assert(list_remove(l, 1) == 1);      /* first  */
    assert(list_remove(l, 5) == 1);      /* last   */
    assert(list_remove(l, 3) == 1);      /* middle */
    assert(list_remove(l, 99) == 0);     /* missing */
    int expected[] = {2, 4};
    expect(l, expected, 2);
    assert(list_remove(l, 2) == 1);
    assert(list_remove(l, 4) == 1);      /* now empty again */
    assert(list_length(l) == 0);
    list_push_back(l, 7);                /* still usable after emptying */
    int again[] = {7};
    expect(l, again, 1);
    list_destroy(l);
}

static void test_duplicates(void)
{
    list *l = list_create();
    list_push_back(l, 5);
    list_push_back(l, 5);
    list_push_back(l, 5);
    assert(list_remove(l, 5) == 1);      /* removes only the first match */
    assert(list_length(l) == 2);
    list_destroy(l);
}

static void test_many(void)
{
    list *l = list_create();
    for (int i = 0; i < 1000; i++) {
        assert(list_push_front(l, i) == 0);
    }
    assert(list_length(l) == 1000);
    list_destroy(l);                     /* leak check should stay clean */
}

int main(void)
{
    test_empty();
    test_push();
    test_remove();
    test_duplicates();
    test_many();
    printf("All tests passed.\n");
    return 0;
}
