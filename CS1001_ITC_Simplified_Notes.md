# CS1001 — Introduction to Computing (ITC)
## Minor 2 Revision Notes: Modules 3, 4 & 5

**Language:** C  
**Coverage:** Control flow and arrays; functions and recursion; pointers, dynamic memory, structures and unions.

> **How to revise:** Learn the rule, trace the example by hand, then cover the output and predict it yourself.

---

# Module 3 — Control Flow and Arrays

## 1. Conditions

In C, `0` means false. Any non-zero value means true.

```c
if (0)  printf("A");  // does not run
if (-1) printf("B");  // runs
if (5)  printf("C");  // runs
```
**Output:** `BC`

- `=` assigns a value: `if (x = 5)` assigns 5 and evaluates as true.
- `==` compares values: `if (x == 5)`.

### `if` statements

```c
if (condition) {
    // runs when true
} else {
    // runs when false
}
```

An `else if` ladder checks conditions from top to bottom. Only the **first true branch** runs.

```c
int marks = 82;
if (marks >= 90)      printf("A");
else if (marks >= 75) printf("B");
else if (marks >= 40) printf("C");
else                  printf("F");
```
**Output:** `B`

Use a nested `if` when the second check should happen only if the first condition succeeds.

## 2. `switch`

Use `switch` to compare **one integer or character expression** with constant `case` values.

```c
switch (choice) {
    case 1: printf("One"); break;
    case 2: printf("Two"); break;
    default: printf("Other");
}
```

Remember:
- `break` exits the switch.
- Without `break`, execution falls through into the next case.
- `default` is optional.
- Case labels must be constants; duplicate labels are invalid.
- `switch` cannot directly test ranges, strings, `float` or `double`.

```c
int x = 2;
switch (x) {
    case 1: printf("One ");
    case 2: printf("Two ");
    case 3: printf("Three "); break;
    default: printf("Other");
}
```
**Output:** `Two Three `

## 3. Ternary operator `?:`

A short way to choose between two values:

```c
int a = 10, b = 25;
int max = (a > b) ? a : b;
printf("%d", max);
```
**Output:** `25`

Use ordinary `if-else` if either branch needs several statements.

## 4. Loops

| Loop | When condition is checked | Minimum runs |
|---|---|---:|
| `while` | Before the body | 0 |
| `for` | Before the body | 0 |
| `do-while` | After the body | 1 |

### `while`

```c
int i = 1;
while (i <= 5) {
    printf("%d", i);
    i++;
}
```
**Output:** `12345`

### `do-while`

```c
int i = 1;
do {
    printf("%d", i);
    i++;
} while (i <= 3);
```
**Output:** `123`

A `do-while` body always runs at least once. Remember the semicolon after `while (condition);`.

### `for`

```c
for (initialisation; condition; update) {
    // body
}
```

Order: **initialise once → test → body → update → test again**.

```c
for (int i = 1; i <= 5; i++)
    printf("%d", i);
```
**Output:** `12345`

### Nested loops

The inner loop completes all its iterations for every outer-loop iteration.

```c
for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= 3; j++)
        printf("(%d,%d) ", i, j);
}
```
**Output:** `(1,1) (1,2) (1,3) (2,1) (2,2) (2,3)`

### `break` vs `continue`

- `break`: exits the nearest loop or `switch`.
- `continue`: skips the rest of the current loop iteration.
- In a `for` loop, `continue` still leads to the update expression.
- In a `while` loop, make sure `continue` does not skip the statement that updates the loop variable.
- In nested loops, `break` exits only the innermost loop.

```c
for (int i = 1; i <= 5; i++) {
    if (i == 3) continue;
    printf("%d", i);
}
```
**Output:** `1245`

### Output-tracing trap: post-increment in a condition

```c
int i;
for (i = 1; i++ <= 4; printf("%d", i));
```

`i++` tests the old value, then increments it. The `printf` is the update expression.

**Output:** `2345`

A semicolon immediately after a `for` or `while` header creates an empty loop body.

## 5. One-dimensional arrays

An array stores a fixed number of elements of the same type in consecutive memory locations.

```c
int a[5] = {10, 20, 30, 40, 50};
int b[5] = {1, 2};  // remaining elements are zero
```

Key rules:
- Indexing starts at `0`; for `n` elements, valid indices are `0` to `n-1`.
- C does not check array bounds. Out-of-range access is undefined behaviour.
- `int a[5];` has uninitialised elements if it is a local array.
- `int b[5] = {1, 2};` becomes `{1, 2, 0, 0, 0}`.
- Array names cannot be reassigned, so `a = b;` is invalid.
- For an actual array, element count = `sizeof(a) / sizeof(a[0])`.

### Common array patterns

```c
// Sum
int sum = 0;
for (int i = 0; i < n; i++)
    sum += a[i];

// Maximum (assumes n > 0)
int max = a[0];
for (int i = 1; i < n; i++)
    if (a[i] > max) max = a[i];

// Linear search
int found = 0;
for (int i = 0; i < n; i++) {
    if (a[i] == key) {
        found = 1;
        break;
    }
}
```

## 6. Two-dimensional arrays

A 2-D array is an array of rows.

```c
int m[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
printf("%d", m[1][2]);
```
**Output:** `6`

- Use `m[row][column]`.
- C stores 2-D arrays in **row-major order**: one row after another.
- `int m[2][3]` means 2 rows and 3 columns.
- When passing a 2-D array to a function, specify the column count, e.g. `int m[][3]`.

## 7. Character arrays and strings

A C string is a character array ending with the null character `'\0'`.

```c
char a[] = "Hello";               // 6 bytes, including '\0'
char b[] = {'H','i','\0'};        // valid string
char c[] = {'H','i'};             // not a valid C string
```

- `sizeof(string_array)` counts all array bytes, including `'\0'`.
- `strlen(string)` counts characters before `'\0'`.
- `scanf("%s", name)` reads one word and stops at whitespace.
- `fgets(name, sizeof name, stdin)` reads a line more safely.
- `%s` prints until `'\0'`; without a terminator, behaviour is undefined.
- Do not use `gets()`.

### Common `<string.h>` functions

| Function | Purpose |
|---|---|
| `strlen(s)` | Length excluding `'\0'` |
| `strcpy(dest, src)` | Copy string |
| `strcat(dest, src)` | Append string |
| `strcmp(a, b)` | Compare strings |
| `strchr(s, c)` | Find first occurrence of a character |
| `strncpy(dest, src, n)` | Copy up to `n` characters; may not add `'\0'` |

`strcmp(a, b)` returns:
- `0` if equal
- a negative value if `a` comes before `b`
- a positive value if `a` comes after `b`

**Never compare string contents with `==`.** Use `strcmp(a, b) == 0`. Ensure the destination has enough space for `strcpy` and `strcat`.

### Useful ASCII values

| Characters | ASCII range |
|---|---:|
| `'0'`–`'9'` | 48–57 |
| `'A'`–`'Z'` | 65–90 |
| `'a'`–`'z'` | 97–122 |
| `'\0'` | 0 |
| `'\n'` | 10 |

- Digit character to integer: `c - '0'`.
- In ASCII, lowercase to uppercase: `c - 32`; uppercase to lowercase: `c + 32`.

---

# Module 4 — Functions and Recursion

## 1. Functions

A function is a named block of code that performs a task.

```c
int add(int a, int b) {
    return a + b;
}

int main(void) {
    printf("%d", add(2, 3));
    return 0;
}
```
**Output:** `5`

- **Return type:** type of value returned (`void` means no value).
- **Parameters:** local variables receiving argument values.
- **Prototype:** declares a function before it is used, e.g. `int add(int, int);`.
- **Definition:** contains the function body.
- A function directly returns one value; pointers can be used to modify multiple outputs.

## 2. Call by value

C passes function arguments **by value**. The function receives copies, so changing a parameter does not change the caller's variable.

```c
void change(int x) {
    x = 99;
}

int main(void) {
    int n = 10;
    change(n);
    printf("%d", n);
}
```
**Output:** `10`

## 3. Functions with arrays

When an array is passed to a function, it behaves as a pointer to its first element. The function can change the original array.

```c
void change(int a[]) {
    a[0] = 99;
}

int main(void) {
    int nums[] = {1, 2, 3};
    change(nums);
    printf("%d", nums[0]);
}
```
**Output:** `99`

Important:
- Pass the array length separately.
- Inside the function, `sizeof(a)` gives the size of a pointer, not the original array.
- A 2-D array parameter must specify its column count, e.g. `int m[][3]`.

## 4. Scope and `static`

| Variable | Lifetime / default |
|---|---|
| Local variable | Exists within its block; uninitialised local variables have indeterminate values |
| Global variable | Exists for the program; zero-initialised by default |
| `static` local | Exists for the whole program and keeps its value between calls; zero-initialised by default |

```c
void counter(void) {
    static int c = 0;
    c++;
    printf("%d ", c);
}
// Calling counter() three times prints: 1 2 3
```

## 5. Recursion

Recursion happens when a function calls itself.

Every recursive function needs:
1. **Base case:** stops the recursion.
2. **Recursive case:** moves towards the base case.

### Factorial

```c
int fact(int n) {
    if (n <= 1) return 1;
    return n * fact(n - 1);
}
```
`fact(5)` = `5 × 4 × 3 × 2 × 1` = **120**

### Other examples

```c
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
// fib(6) = 8

int sumTo(int n) {
    return (n == 0) ? 0 : n + sumTo(n - 1);
}
// sumTo(5) = 15
```

Without a valid base case, recursion may continue until a stack overflow occurs.

## 6. Types of recursion

| Type | Meaning | Example idea |
|---|---|---|
| Direct | Function calls itself | `fact()` calls `fact()` |
| Indirect | Functions call each other in a cycle | `isEven()` calls `isOdd()` and vice versa |
| Tail | Recursive call is the final operation | `return f(n - 1);` |

Example of indirect recursion:

```c
int isOdd(int n);

int isEven(int n) {
    return n == 0 ? 1 : isOdd(n - 1);
}
int isOdd(int n) {
    return n == 0 ? 0 : isEven(n - 1);
}
```

Tail recursion can sometimes be optimised by a compiler, but do not assume that it always uses constant stack memory.

## 7. How to trace recursive output

Write down the order of operations carefully. A `printf` **before** a recursive call runs on the way down; a `printf` **after** it runs as calls return.

```c
void f(int n) {
    if (n <= 0) return;
    printf("%d", n);
    f(n - 1);
    printf("%d", n);
}
```
`f(3)` prints **`321123`**.

Another common pattern:

```c
void f(int n) {
    if (n <= 0) return;
    f(n - 1);
    printf("%d", n);
    f(n - 2);
}
```
`f(3)` prints **`1231`**.

For output questions, trace each call and concatenate characters in the exact order they print. Do not rely on a possibly incorrect answer key.

## 8. Recursion vs iteration

| Recursion | Iteration |
|---|---|
| Function calls itself | Uses loops such as `for` and `while` |
| Stops at a base case | Stops when loop condition becomes false |
| Uses stack frames for calls | Usually uses less extra memory |
| Has function-call overhead | Often faster |
| Useful for trees, divide-and-conquer and backtracking | Useful for straightforward repetition and array traversal |

---

# Module 5 — Pointers and Composite Data Types

## 1. Pointers

A pointer stores a memory address.

| Operator | Meaning |
|---|---|
| `&x` | Address of `x` |
| `*p` | Value at the address stored in `p` |

```c
int x = 42;
int *p = &x;
printf("%d", *p);  // 42
*p = 100;
printf("%d", x);   // 100
```

- `int *p` is a pointer to an integer.
- `char *p` points to a character.
- `int **p` points to an integer pointer.
- In `int *p, q;`, only `p` is a pointer; `q` is an ordinary integer.
- Initialise pointers to a valid address or `NULL`.
- Do not dereference uninitialised or `NULL` pointers.

## 2. Pointer arithmetic

Pointer arithmetic moves in units of the pointed-to type.

- `p + 1` points to the next element, not necessarily the next byte.
- For an `int *`, it advances by `sizeof(int)` bytes.
- `*(p + i)` accesses element `i`.
- `p[i]` is equivalent to `*(p + i)`.
- Subtracting pointers within the same array gives the number of elements between them.
- Pointer arithmetic outside the array and its one-past-the-end position is undefined.

```c
int a[] = {10, 20, 30, 40};
int *p = a;
printf("%d %d", p[2], *(p + 2));
```
**Output:** `30 30`

## 3. Arrays vs pointers

| Array | Pointer |
|---|---|
| Stores a sequence of elements | Stores an address |
| `sizeof(array)` is the total array size | `sizeof(pointer)` is the pointer size |
| Array name cannot be reassigned | Pointer can point elsewhere |
| `array++` is invalid | `p++` is valid when pointer arithmetic is valid |
| Usually allocates storage for all elements | Must point to valid storage before dereferencing |

For an array `a`:
- `a[i]` is equivalent to `*(a + i)`.
- `&a[i]` is equivalent to `a + i`.

### `char *` vs `char []`

```c
char *p = "Hello";  // points to a string literal; do not modify it
char a[] = "Hello"; // array copy; its characters can be changed
```

| `char *p = "Hello"` | `char a[] = "Hello"` |
|---|---|
| Pointer to string literal | Array containing a copy |
| Modifying the literal is undefined behaviour | `a[0] = 'h'` is valid |
| Pointer can be reassigned | Array name cannot be reassigned |

## 4. Modifying variables through pointers

C still passes arguments by value, but a pointer value can refer to the caller's variable.

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 8, y = 4;
    swap(&x, &y);
    printf("%d %d", x, y);
}
```
**Output:** `4 8`

| Call by value | Passing a pointer (often called call by reference) |
|---|---|
| Passes a copy of the value | Passes the address as a pointer value |
| Changing the parameter does not change the caller's variable | Dereferencing the pointer can change the caller's variable |
| Example: `f(x)` with parameter `int a` | Example: `f(&x)` with parameter `int *a` |

Pointers can also let a function produce multiple results, such as minimum and maximum.

## 5. Dynamic memory

Include `<stdlib.h>` to use dynamic memory functions.

| Function | Purpose |
|---|---|
| `malloc(bytes)` | Allocates memory; contents are uninitialised |
| `calloc(n, size)` | Allocates memory for `n` items and zero-initialises the bytes |
| `realloc(ptr, size)` | Resizes a block; it may move the block |
| `free(ptr)` | Releases allocated memory |

Allocation can fail and return `NULL`, so check the result.

```c
int *a = malloc(5 * sizeof *a);
if (a == NULL) {
    // handle allocation failure
    return 1;
}

for (int i = 0; i < 5; i++)
    a[i] = i * 10;

free(a);
a = NULL;
```

Safe habits:
1. Check allocation results.
2. Do not access memory outside the allocated block.
3. Free dynamically allocated memory when finished.
4. Set a freed pointer to `NULL` when appropriate.
5. Use a temporary pointer for `realloc`, so a failed resize does not lose the original block.

```c
int *tmp = realloc(a, new_count * sizeof *a);
if (tmp != NULL)
    a = tmp;
```

### Common memory errors

- **Memory leak:** allocated memory is never freed.
- **Dangling pointer:** pointer refers to memory that has been freed.
- **Double free:** the same allocation is freed twice.
- **Invalid/uninitialised pointer:** pointer is used without a valid target.
- **Out-of-bounds access:** accessing beyond allocated memory.

### Stack vs heap

| Stack | Heap |
|---|---|
| Commonly stores local variables and function-call data | Used for dynamic allocations |
| Managed automatically | Managed with allocation functions and `free` |
| Local variables usually stop existing when their block ends | Allocation remains until freed or program termination |

## 6. Structures

A structure groups related values, possibly of different types.

```c
struct Student {
    int roll;
    char name[30];
    float marks;
};

struct Student s = {101, "Aarav", 88.5};
printf("%d %s %.1f", s.roll, s.name, s.marks);
```
**Output:** `101 Aarav 88.5`

- Use `.` to access a member: `s.marks`.
- A structure definition ends with a semicolon.
- Whole structures of the same type can be assigned: `s2 = s1`.
- `sizeof(struct)` may include padding for alignment.

## 7. Pointers to structures

Use `->` to access a structure member through a pointer.

```c
struct Book {
    char title[50];
    float price;
};

struct Book b = {"C Programming", 299.0f};
struct Book *p = &b;

printf("%.2f", p->price);
```

`p->price` means the same as `(*p).price`.

## 8. Nested structures and arrays of structures

A structure can contain another structure:

```c
struct Author {
    char name[30];
};

struct Novel {
    struct Author author;
    int year;
};

struct Novel n = {{"Kernighan"}, 1978};
printf("%s %d", n.author.name, n.year);
```
**Output:** `Kernighan 1978`

An array can store multiple structures:

```c
struct Point {
    int x, y;
};

struct Point p[2] = {{1, 2}, {3, 4}};
printf("%d", p[1].y);
```
**Output:** `4`

A self-referential structure can contain a pointer to its own type, as used in linked lists:

```c
struct Node {
    int data;
    struct Node *next;
};
```

## 9. Unions

A union's members share the same memory. Writing to one member overwrites the stored representation used by the others.

```c
union Data {
    int i;
    float f;
    char c;
};
```

- `sizeof(union)` is large enough for its largest member, including alignment requirements.
- Unlike a structure, a union does not store separate independent copies of all members.
- Reading a different member from the one most recently written requires care; do not assume it is always meaningful or portable.

### Structure vs union

| Structure (`struct`) | Union (`union`) |
|---|---|
| Each member has its own storage | Members share storage |
| Members can hold values simultaneously | Typically use one member's value at a time |
| Size includes space for all members plus padding | Size is sufficient for the largest member plus alignment |

---

# High-Value Exam Comparisons

## `while` vs `do-while`

| `while` | `do-while` |
|---|---|
| Condition checked before body | Condition checked after body |
| May run zero times | Runs at least once |
| No semicolon after the condition's closing brace | Semicolon required after `while (condition);` |

## `break` vs `continue`

| `break` | `continue` |
|---|---|
| Exits the nearest loop or switch | Skips to the next loop iteration |
| Execution continues after the loop/switch | Loop proceeds with its next iteration |

## `malloc` vs `calloc`

| `malloc` | `calloc` |
|---|---|
| Takes total number of bytes | Takes item count and item size |
| Memory is uninitialised | Allocated bytes are zero-initialised |
| `malloc(n * sizeof *p)` | `calloc(n, sizeof *p)` |

## Recursion vs iteration

| Recursion | Iteration |
|---|---|
| Repeated function calls | Repetition using loops |
| Needs a base case | Needs a loop condition |
| Uses call-stack memory | Usually lower extra-memory overhead |
| Can be elegant for recursive problems | Often simpler for basic repetition |

## Array vs pointer

Remember: arrays often **decay to pointers** in expressions and function calls, but an array and a pointer are not the same thing. `sizeof` is a common way to spot the difference.

---

# Quick Syntax Reference

```c
// if
if (condition) { ... } else { ... }

// switch
switch (x) {
    case 1: ...; break;
    default: ...;
}

// for / while / do-while
for (int i = 0; i < n; i++) { ... }
while (condition) { ... }
do { ... } while (condition);

// function
return_type name(parameters) { ... }

// pointer
int x = 5;
int *p = &x;
printf("%d", *p);

// dynamic allocation
int *p = malloc(n * sizeof *p);
if (p != NULL) {
    /* use p */
    free(p);
    p = NULL;
}

// structure
struct Student {
    int roll;
};
struct Student s = {1};
printf("%d", s.roll);
```

## Common format specifiers

| Type | `printf` specifier |
|---|---|
| `int` | `%d` |
| `char` | `%c` |
| String (`char *`) | `%s` |
| `float` / `double` in `printf` | `%f` |
| `size_t` (e.g. result of `sizeof`) | `%zu` |
| Pointer address | `%p` (pass `(void *)p`) |

Use the matching format specifier for the value's type.

---

# Final Exam Checklist

- [ ] `=` assigns; `==` compares.
- [ ] `switch` needs `break` to avoid fall-through.
- [ ] `do-while` runs at least once.
- [ ] Check loop updates, stray semicolons, and `continue`.
- [ ] Array indices run from `0` to `n-1`.
- [ ] Partial array initialisation fills remaining elements with zero.
- [ ] `sizeof(array)` is bytes; divide by `sizeof(array[0])` for the element count.
- [ ] C strings need `'\0'`; `strlen` excludes it and `sizeof` includes it for an array.
- [ ] Use `strcmp` to compare strings.
- [ ] Recursion needs a base case and must move towards it.
- [ ] Trace `printf` calls in the order they execute.
- [ ] Ordinary function arguments are passed by value.
- [ ] Arrays passed to functions behave like pointers; pass the length separately.
- [ ] `&` gets an address; `*` dereferences a pointer.
- [ ] Pointer arithmetic moves by element size.
- [ ] Check allocations, `free` memory, and avoid invalid access.
- [ ] Use `.` for structure objects and `->` for structure pointers.
- [ ] Structure members have separate storage; union members share storage.
- [ ] Never assume a particular output for undefined behaviour.

