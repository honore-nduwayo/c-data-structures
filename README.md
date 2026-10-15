# c-data-structures

Data structures built from scratch in C, with manual memory management
and no memory leaks. Built to learn how pointers, `malloc` and `free` work.

| Project | Status |
|---|---|
| [Linked list](linked_list/) | Done |
| Stack and queue | Planned |
| Mini-shell | Planned |

## Linked list

A singly linked list of `int`s.

**Operations:** create, push front, push back, contains, remove (first
match), get by index, length, print, destroy.

**Design decisions**
- Each node holds a value and a pointer to the next node. The list holds
  a pointer to the first node and a length counter.
- The list owns its nodes. `list_remove` frees the node it removes and
  `list_destroy` frees everything else.
- Functions that allocate return an error code (`-1`) if `malloc` fails.
  Removing a value that is not there returns `0` and changes nothing.
- `list_push_back` walks the whole list, so it is O(n). Keeping a pointer
  to the last node would make it O(1); I left that out to keep v1 simple.

### Build and test
```
cd linked_list
make test      # build and run the tests
make asan      # same tests with AddressSanitizer (memory errors, and leaks on Linux)
make leaks     # leak check: `leaks` on macOS, valgrind on Linux
make clean
```

### What the tests cover
Empty list, push front and back, remove from the first, middle and last
position, remove a missing value, remove from an empty list, duplicate
values, reuse after emptying, and 1000 nodes created then destroyed.

### What I learned
malloc is very crucial because when building programs, C allocates memory to the variables, functins, and other thing created and when we want to use them back, C creates a copy of them which is another memory taken hence using pointers also becomes crucial for malloc
