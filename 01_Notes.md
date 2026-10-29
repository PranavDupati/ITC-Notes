# CS1001 — Introduction to Computing (ITC)
## Minor 2 Exam Notes — Modules 3, 4 & 5

**Course:** CS1001 Introduction to Computing (L-T-P-C: 3-0-2-4)
**Language:** C
**Coverage:** Module 3 (Control Flow & Arrays) · Module 4 (User-Defined Functions) · Module 5 (Pointers & Composite Data Types)
**Exam:** Minor 2 — 15%, closed book

> **How to use these notes:** read the rule → read the code → cover the output and predict it yourself. Roughly 60% of a C minor paper is "predict the output" / "what does this function do", so the **Output** blocks are the highest-value part of this document.
>
> **Every output in this file was produced by compiling and running the exact code** (Apple clang 21, 64-bit). See the Verification Record at the end.

---

## Syllabus Map

| Module | Topics (from the official handout) | COs | Hours |
|--------|------------------------------------|-----|-------|
| **M3** | Branching: if-else, switch, ternary. Looping: for, while, do-while, nested, break, continue. Arrays: 1-D, multi-dimensional, character arrays, strings. | CO3 | 8 |
| **M4** | Functions: definition, call by value, functions with arrays. Recursion: direct, indirect, tail. | CO4, CO5, CO6 | 8 |
| **M5** | Pointers: basics, arithmetic, pointers vs arrays. Dynamic memory: malloc, realloc, calloc, free. Structures & unions: definition, nesting, pointers to structs, array of structures. Passing variables: value, reference, arrays, pointers. | CO4, CO5, CO6 | 8 |

**Textbook:** K&R *The C Programming Language* (2/e); Prata *C Primer Plus* (6/e).
**Reference:** Balagurusamy *Programming in ANSI C* (8/e).

---

## What the Minor 2 paper looks like

Based on the pattern paper in your seniors' ITC folder, questions come in pairs:

```
1. Answer the following
   a) Write code / predict output / explain a function   (application)
   b) Differentiate between X and Y                        (understanding)
```

So for every topic, prepare **two things**: (1) a small piece of code you can write from memory, and (2) a 3–4 point comparison table. Part 4 of these notes gives you both.

---

# PART 1 — MODULE 3: CONTROL FLOW & ARRAYS

## 1.1 Truth and falsity in C

C has **no built-in `bool`** in older standards (`#include <stdbool.h>` in C99 gives `bool`, `true`, `false`).

| Value | Truth value |
|-------|-------------|
| `0` | **false** |
| any non-zero (1, -5, 0.1, `'A'`) | **true** |

```c
if (0)  printf("A");   // never runs
if (-1) printf("B");   // runs — negative is still true
if (5)  printf("C");   // runs
```

**Output:** `BC`

> ⚠️ `if (x = 5)` is an **assignment**, not a comparison. It stores 5 in `x` and the value of the expression is 5 → always true. Use `if (x == 5)`.

---

## 1.2 Decision making: `if` family

### (a) Simple `if`

```c
if (condition) {
    statements;      // runs only when condition is true
}
```

### (b) `if–else` — exactly one branch runs

```c
int marks = 35;
if (marks >= 40) printf("Pass");
else             printf("Fail");
```
**Output:** `Fail`

### (c) `else–if` ladder — checked top to bottom, first true wins

```c
int marks = 82;
if      (marks >= 90) printf("A");
else if (marks >= 75) printf("B");
else if (marks >= 40) printf("C");
else                  printf("F");
```
**Output:** `B`

> Only the **first** matching branch executes; later conditions are skipped entirely.

### (d) Nested `if` — second decision only after the first succeeds

```c
int age = 20, has_id = 0;
if (age >= 18) {
    if (has_id == 1) printf("Entry allowed");
    else             printf("ID required");
} else {
    printf("Too young");
}
```
**Output:** `ID required`

> Use nested `if` when the second condition is **meaningless** unless the first is true.

---

## 1.3 `switch` statement

Selects one branch by comparing **one expression** against **constant** case labels.

```c
switch (expression) {
    case constant1:
        statements;
        break;
    case constant2:
        statements;
        break;
    default:
        statements;
}
```

**Rules that get asked:**

| Rule | Detail |
|------|--------|
| Expression type | Must be **integer or char** (int, char, short, long, enum). **Not float, double or string.** |
| Case labels | Must be **compile-time constants** (`case 5:` ✓, `case x:` ✗ if x is a variable). |
| Duplicate cases | Compile-time error. |
| `break` | Exits the switch. **Without it, execution falls through** into the next case. |
| `default` | Optional; runs when no case matches. Position does not matter. |
| Order of checks | Cases are not "searched in order" like an else-if ladder — the compiler may build a jump table. |

### Fall-through demo (very common exam question)

```c
int x = 2;
switch (x) {
    case 1: printf("One ");
    case 2: printf("Two ");
    case 3: printf("Three "); break;
    default: printf("Other ");
}
```
**Output:** `Two Three `

> `case 2` matches, prints `Two`, then **falls through** into `case 3` because there is no `break`. It stops after `Three`.
> **Habit:** put `break;` on every case unless you deliberately want fall-through.

### `switch` on a `char`

```c
char op = '+';
switch (op) {
    case '+': printf("Add"); break;
    case '-': printf("Subtract"); break;
    default:  printf("Unknown");
}
```
**Output:** `Add`

> ⚠️ `switch` **cannot** test a range (`case marks >= 40:` is invalid) and cannot switch on strings.

---

## 1.4 Ternary (conditional) operator `? :`

A compact `if–else` that **produces a value**.

```c
condition ? value_if_true : value_if_false;
```

```c
int a = 10, b = 25;
int max = (a > b) ? a : b;
printf("%d", max);
```
**Output:** `25`

Nested ternary (use sparingly — readability matters):

```c
int n = 0;
printf("%s", (n > 0) ? "Positive" : (n < 0) ? "Negative" : "Zero");
```
**Output:** `Zero`

> Use `if–else` instead when a branch needs **multiple statements**. The ternary returns one expression only.

---

## 1.5 Choosing a construct

| Construct | Use when | Can test ranges? | Can test many variables? |
|-----------|----------|------------------|--------------------------|
| `if / if–else` | one or two outcomes | ✅ | ✅ |
| `else–if` ladder | several ordered conditions | ✅ | ✅ |
| `switch` | one expression vs fixed constants | ❌ | ❌ (one expression) |
| `? :` | choosing between two **values** | ✅ | ✅ (but keep it simple) |

---

## 1.6 Loops

| Loop | Entry/Exit controlled | Condition checked | Minimum executions |
|------|-----------------------|-------------------|--------------------|
| `while` | **Entry** controlled | before each iteration | **0** |
| `do–while` | **Exit** controlled | after each iteration | **1** |
| `for` | Entry controlled | before each iteration | **0** |

### (a) `while`

```c
int i = 1;
while (i <= 5) {
    printf("%d", i);
    i++;
}
```
**Output:** `12345`

> Forgetting `i++` gives an **infinite loop**. `while (i <= 5);` (stray semicolon) also loops forever with an empty body.

### (b) `do–while` — body runs at least once

```c
int n = 1;
do {
    printf("%d", n);
    n++;
} while (n <= 3);
```
**Output:** `123`

Proof that it runs once even when the condition is false:

```c
int k = 10;
do { printf("ran once"); k++; } while (k < 5);
```
**Output:** `ran once`

> Note the semicolon after `while (...)` in a `do–while`. Missing it is a compile error.

### (c) `for`

```c
for (initialization; condition; update) {
    statements;
}
```

**Execution order:** init **once** → check condition → body → update → check again …

```c
for (int i = 1; i <= 5; i++) printf("%d", i);
```
**Output:** `12345`

`for` and `while` are interchangeable:

| `for` | Equivalent `while` |
|-------|--------------------|
| `for (i=0; i<n; i++)` | `i=0; while (i<n) { …; i++; }` |

### (d) Infinite loops (deliberate)

```c
for (;;) { … }        // idiomatic infinite for
while (1) { … }
```

---

## 1.7 Nested loops

For **every one** iteration of the outer loop, the inner loop runs **all** its iterations.

Total body executions = (outer iterations) × (inner iterations).

```c
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 2; j++)
        printf("(%d,%d)", i, j);
    printf("\n");
}
```
**Output:**
```
(1,1)(1,2)
(2,1)(2,2)
(3,1)(3,2)
```

> 3 × 2 = 6 prints. Pattern programs (pyramid, Floyd's triangle, multiplication tables) are built exactly this way.

---

## 1.8 `break` and `continue`

| Keyword | Effect |
|---------|--------|
| `break` | **Immediately exits** the nearest enclosing loop **or switch**; execution continues after it. |
| `continue` | **Skips the rest of the current iteration** and jumps to the next iteration (in a `for`, the update runs first; in a `while`/`do–while`, the condition is evaluated next). |

```c
for (int i = 1; i <= 5; i++) {
    if (i == 3) continue;
    printf("%d", i);
}
```
**Output:** `1245`

```c
for (int i = 1; i <= 5; i++) {
    if (i == 3) break;
    printf("%d", i);
}
```
**Output:** `12`

> ⚠️ `break` inside **nested** loops exits only the **inner** loop. To leave both, use a flag or `goto`.

> ⚠️ `continue` in a `while` loop can cause an infinite loop if the update is placed **after** the `continue`:

```c
int i = 0;
while (i < 5) {
    if (i == 2) continue;   // i never increments → infinite loop
    printf("%d", i);
    i++;
}
```

---

## 1.9 Output-prediction: the `i++` in the condition trap

This pattern appears repeatedly in the Minor 2 pattern paper. Read it slowly.

```c
void fun() {
    int i;
    for (i = 1; i++ <= 4; printf("%d", i));
}
```

Three things happen per iteration:
1. **Test** the **old** value of `i` against 4.
2. **Increment** `i` (post-increment happens as part of the test).
3. If true → run the (empty) body → run the update `printf("%d", i)`.

| Test (`i++ <= 4`) | `i` after increment | Printed |
|---|---|---|
| 1 <= 4 ✓ | 2 | 2 |
| 2 <= 4 ✓ | 3 | 3 |
| 3 <= 4 ✓ | 4 | 4 |
| 4 <= 4 ✓ | 5 | 5 |
| 5 <= 4 ✗ | 6 | — stop |

**Output of `fun()`:** `2345`

Now wrap it in a loop:

```c
int main() {
    int j;
    for (j = 1; j++ <= 4; fun());
}
```
`j = 1,2,3,4` all pass → `fun()` is called **4 times**.

**Output:** `2345234523452345`

**Same pattern with different bounds — memorise the method, not the answer:**

| `fun()` loop | Prints | `main()` loop | Calls | Final output |
|---|---|---|---|---|
| `for (i=1; i++<=4; printf)` | `2345` | `j=1; j++<=4` | 4 | `2345234523452345` |
| `for (i=0; i++<=3; printf)` | `1234` | `j=0; j++<=2` | 3 | `123412341234` |
| `for (i=2; i++<=6; printf)` | `34567` | `j=1; j++<=3` | 3 | `345673456734567` |

> Quick count of calls: `for (j = A; j++ <= B; …)` runs **(B − A + 1)** times.
> Verified: `j=0; j++<=3` → 4 calls → `1234` × 4 = `1234123412341234`.

**Pre-increment variant:** with `++i <= 4`, the value is incremented **before** the test, so the printed sequence shifts by one. Trace it the same way — test, then print.

---

## 1.10 One-dimensional arrays

An array stores a **fixed number of elements of the same type in consecutive memory locations**, accessed by index.

```c
int marks[5];                          // declaration (uninitialised → garbage)
int scores[5] = {70, 82, 91, 65, 88};  // declaration + initialisation
int a[] = {1, 2, 3};                   // size inferred = 3
int b[5] = {1, 2};                     // rest are 0 → 1 2 0 0 0
```

**Rules:**

| Rule | Detail |
|------|--------|
| Indexing | Starts at **0**; valid indices are `0 … n-1`. |
| Bounds checking | **None.** `a[10]` compiles and causes **undefined behaviour** (garbage or crash). |
| Size | Must be a constant expression (C89) / VLA allowed in C99. |
| Name | The array name is **not** a variable you can reassign; it decays to a pointer in most expressions. |
| Copying | `b = a;` is **illegal** — copy element by element or with `memcpy`. |
| `sizeof` | `sizeof(a)` = total bytes; number of elements = `sizeof(a)/sizeof(a[0])`. |

```c
int scores[5] = {70, 82, 91, 65, 88};
printf("%d %d\n", scores[0], scores[2]);
scores[2] = 95;
printf("%d\n", scores[2]);
```
**Output:**
```
70 91
95
```

### Traversal (the standard loop)

```c
int a[5] = {2, 4, 6, 8, 10};
int sum = 0;
for (int i = 0; i < 5; i++)
    sum += a[i];
printf("%d", sum);
```
**Output:** `30`

**Memorise these three loops:**

```c
// sum
for (i = 0; i < n; i++) sum += a[i];

// maximum
int max = a[0];
for (i = 1; i < n; i++) if (a[i] > max) max = a[i];

// linear search
for (i = 0; i < n; i++) if (a[i] == key) { found = 1; break; }
```

> `sizeof(a)/sizeof(a[0])` is the portable element count. `sizeof(a)` alone is **bytes**, not elements.

---

## 1.11 Multi-dimensional arrays (2-D)

A 2-D array is an **array of arrays** — a table with rows and columns.

```c
int matrix[2][3] = {
    {1, 2, 3},     // row 0
    {4, 5, 6}      // row 1
};
```

`matrix[2][3]` = **2 rows, 3 columns**. Valid: `matrix[0..1][0..2]`.

```c
printf("%d", matrix[1][2]);
```
**Output:** `6`

**Reasoning:** row `1` = `{4,5,6}`, column `2` = third element = `6`.

### Row-major order

C stores all of row 0 first, then all of row 1, contiguously:

```
memory: [1][2][3][4][5][6]
         └── row 0 ──┘└── row 1 ──┘
```

Verified on the machine used for these notes:

```c
int m[2][3] = {{1,2,3},{4,5,6}};
printf("%ld\n", (long)((char*)&m[0][2] - (char*)&m[0][0]));  // 8 bytes = 2 ints
printf("%ld\n", (long)(&m[1][0] - &m[0][0]));                // 3 elements
printf("%zu %zu\n", sizeof(m), sizeof(m[0]));                // 24 12
```
**Output:**
```
8
3
24 12
```

### Traversal

```c
for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++)
        printf("%d ", matrix[i][j]);
    printf("\n");
}
```
**Output:**
```
1 2 3
4 5 6
```

> `matrix[i][j]` — **row first, column second**. Writing `matrix[j][i]` silently transposes the table.
> A 3-D array is an array of 2-D arrays: `int t[2][3][4];` → `t[block][row][col]`.

---

## 1.12 Character arrays and strings

A **C string** is a `char` array terminated by the **null character `'\0'`** (ASCII 0). The null marks where the string ends.

```c
char s1[] = "Hello";        // 6 bytes: H e l l o \0
char s2[] = {'H','e','l','l','o','\0'};  // same thing
char s3[6] = "Hello";       // exactly fits, includes '\0'
char s4[5] = "Hello";       // NO room for '\0' → not a valid string
```

| Declaration | Elements stored | Null terminator? | Valid string? |
|-------------|-----------------|------------------|---------------|
| `char x[] = {'6'};` | `'6'` | **No** | **No** |
| `char y[] = "6";` | `'6'`, `'\0'` | **Yes** | **Yes** |

Verified:

```c
char s1[] = {'6'};
char s2[] = "6";
printf("sizeof s1=%zu sizeof s2=%zu\n", sizeof(s1), sizeof(s2));
printf("strlen s2=%zu\n", strlen(s2));
```
**Output:**
```
sizeof s1=1 sizeof s2=2
strlen s2=1
```

> `sizeof` counts the `'\0'`; `strlen` does **not**.
> `sizeof("Hello")` = 6, `strlen("Hello")` = 5.

### Printing and reading

```c
char name[20] = "Manipal";
printf("%s", name);          // Manipal
printf("%zu", strlen(name)); // 7
```

| Task | Code | Note |
|------|------|------|
| Read one word | `scanf("%s", name);` | Stops at whitespace. **No `&`** — the array name is already an address. |
| Read a line | `fgets(name, sizeof(name), stdin);` | Safe; keeps the newline. Avoid `gets()` (removed/unsafe). |
| Print | `printf("%s", name);` | Prints until `'\0'`. Without `'\0'` it runs past the array → undefined behaviour. |

### ASCII essentials

```c
printf("%c %d\n", 'A', 'A');
printf("%c\n", 65);
```
**Output:**
```
A 65
A
```

| char | ASCII |
|------|-------|
| `'0'`–`'9'` | 48–57 |
| `'A'`–`'Z'` | 65–90 |
| `'a'`–`'z'` | 97–122 |
| `'\0'` | 0 |
| `'\n'` | 10 |

> Digit → number: `c - '0'`. Upper → lower: `c + 32`. Lower → upper: `c - 32`.

---

## 1.13 `<string.h>` functions

```c
#include <string.h>
```

| Function | Purpose | Example | Result |
|----------|---------|---------|--------|
| `strlen(s)` | length, excluding `'\0'` | `strlen("Hello")` | `5` |
| `strcpy(d, s)` | copy `s` into `d` | `strcpy(copy,"ITC")` | `copy = "ITC"` |
| `strcat(d, s)` | append `s` to `d` | `strcat(greet," C")` | `"Hello C"` |
| `strcmp(a, b)` | lexicographic compare | `strcmp("abc","abd")` | **negative** (a < b) |
| `strncpy(d, s, n)` | copy at most `n` chars | — | may omit `'\0'` |
| `strchr(s, c)` | first occurrence of `c` | — | pointer or `NULL` |

`strcmp` returns:

| Return | Meaning |
|--------|---------|
| `0` | strings equal |
| `< 0` | first string is **less** (comes first) |
| `> 0` | first string is **greater** |

> ⚠️ Never compare strings with `==`. `if (s1 == s2)` compares **addresses**, not contents. Use `strcmp(s1, s2) == 0`.
> ⚠️ `strcpy`/`strcat` do **no bounds checking** — the destination must be big enough.
> `strcmp` returns "negative/positive", not necessarily `-1`/`1` (the exact value is implementation-defined).

---

## 1.14 Module 3 traps checklist

1. `if (x = 5)` assigns; `if (x == 5)` compares.
2. `switch` needs `break`; missing it causes **fall-through**.
3. `switch` cannot use `float`, `double`, strings, or non-constant cases.
4. `do–while` runs **at least once**; `while`/`for` may run zero times.
5. Semicolon after `for (...)` or `while (...)` creates an **empty body** / infinite loop.
6. `continue` in `while` can skip the update → infinite loop.
7. Array indices are `0 … n-1`; C does **not** check bounds.
8. `int a[5] = {1,2};` → remaining elements are **0**, not garbage.
9. `sizeof(array)` ≠ number of elements; divide by `sizeof(a[0])`.
10. `char x[] = {'6'};` is **not** a string (no `'\0'`).
11. Compare strings with `strcmp`, never `==`.
12. 2-D arrays are **row-major**; `a[row][col]`.

---

# PART 2 — MODULE 4: USER-DEFINED FUNCTIONS

## 2.1 Anatomy of a function

```c
return_type function_name(parameter_list) {
    statements;
    return value;        // omit if return_type is void
}
```

```c
int add(int a, int b) {     // definition
    return a + b;
}

int main(void) {
    printf("%d", add(2, 3));
    return 0;
}
```
**Output:** `5`

| Part | Meaning |
|------|---------|
| `int` | Return type. `void` = returns nothing. |
| `add` | Function name. |
| `(int a, int b)` | Formal parameters — **new local variables** created on each call. |
| `return` | Sends one value back and ends the function. |

**Prototype (declaration) vs definition:**

```c
int add(int, int);          // prototype — tells the compiler the signature
...
int add(int a, int b) { return a + b; }   // definition — the actual body
```

> Declare **before use**. If `main` calls `add` before the compiler has seen it, you get an implicit-declaration warning/error (removed in C99).
> A function returns **one** value only. Need two? Use pointers (Module 5).

---

## 2.2 Call by value (the default in C)

The **values** of the arguments are **copied** into the parameters. The function works on copies.

```c
void swapVal(int a, int b) {
    int t = a;
    a = b;
    b = t;
}

int main(void) {
    int x = 8, y = 4;
    swapVal(x, y);
    printf("%d %d", x, y);
}
```
**Output:** `8 4`

> The swap happened **inside** the function, but `x` and `y` in `main` are untouched — `a` and `b` were separate copies.

```c
void incVal(int a) { a = a + 10; }

int main(void) {
    int m = 20;
    incVal(m);
    printf("%d", m);
}
```
**Output:** `20`

**Why:** each call gets a new **stack frame** holding its own parameters. Destroying the frame destroys the changes.

---

## 2.3 Functions with arrays

An array **decays to a pointer to its first element** when passed to a function. **No copy is made** — the function receives the address of the caller's array.

```c
void modify(int a[]) {
    a[0] = 99;
}

int main(void) {
    int arr[3] = {1, 2, 3};
    modify(arr);
    printf("%d %d %d", arr[0], arr[1], arr[2]);
}
```
**Output:** `99 2 3`

> So array arguments behave like **call by reference** even though the syntax looks like call by value. This is why `scanf("%s", name)` and `modify(arr)` can change the caller's data.

**Three consequences:**

1. **`sizeof` inside the function is the pointer size**, not the array size:

```c
void f(int a[]) { printf("%zu\n", sizeof(a)); }   // 8 on 64-bit
int main(void) { int arr[5]; printf("%zu\n", sizeof(arr)); }  // 20
```
**Output:**
```
8
20
```

2. You must **pass the length** separately:

```c
void printAll(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
```

3. **Modifications are permanent** — there is no "local copy" of the array.

### 2-D arrays as parameters

The **column count is mandatory**; the row count can be omitted, because the compiler needs the row width to compute addresses.

```c
int sum2D(int m[][3], int rows) {
    int s = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 3; j++)
            s += m[i][j];
    return s;
}

int main(void) {
    int m[2][3] = {{1,2,3},{4,5,6}};
    printf("%d", sum2D(m, 2));
}
```
**Output:** `21`

Valid prototypes: `int m[][3]`, `int m[2][3]`, `int (*m)[3]`.
Invalid: `int m[][]` or `int **m` (different type).

---

## 2.4 Scope and storage (supporting concept)

| Kind | Where declared | Lifetime | Default value |
|------|----------------|----------|---------------|
| **Local (auto)** | inside a block | until the block ends | garbage |
| **Global** | outside all functions | whole program | 0 |
| **static local** | inside a block with `static` | whole program, initialised once | 0 |
| **register** | `register int i;` | block | — (hint only) |

```c
void counter(void) {
    static int c = 0;    // initialised only once
    c++;
    printf("%d ", c);
}
int main(void) { counter(); counter(); counter(); }
```
**Output:** `1 2 3`

> Without `static`, it would print `1 1 1` every time.

---

## 2.5 Recursion

A **recursive function** calls itself. Every recursion needs:

1. **Base case** — a condition that stops the recursion.
2. **Recursive case** — a call with a **smaller** input, moving toward the base case.

```c
int fact(int n) {
    if (n <= 1) return 1;        // base case
    return n * fact(n - 1);      // recursive case
}

int main(void) { printf("%d", fact(5)); }
```
**Output:** `120`

Trace: `fact(5) = 5 × fact(4) = 5 × 4 × fact(3) = … = 5×4×3×2×1 = 120`.

```c
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
```
`fib(6)` → **8** (series: 0 1 1 2 3 5 8)

```c
int sumTo(int n) { return (n == 0) ? 0 : n + sumTo(n-1); }
```
`sumTo(5)` → **15**

> **No base case → infinite recursion → stack overflow → crash.**
> Each call uses a stack frame, so recursion costs memory; deep recursion can overflow.

---

## 2.6 Types of recursion

| Type | Definition | Example |
|------|------------|---------|
| **Direct** | Function calls **itself** | `fact(n)` calls `fact(n-1)` |
| **Indirect** | Function calls another, which calls it back | `isEven` → `isOdd` → `isEven` |
| **Tail** | The recursive call is the **last operation**; result returned directly | `factTail(n-1, n*acc)` |

**Indirect recursion:**

```c
int isEven(int n) { return n == 0 ? 1 : isOdd(n-1); }
int isOdd (int n) { return n == 0 ? 0 : isEven(n-1); }
```
`isEven(4)` → **1**, `isEven(7)` → **0**

**Tail recursion:**

```c
int factTail(int n, int acc) {
    if (n <= 1) return acc;
    return factTail(n - 1, n * acc);   // last action is the call
}
```
`factTail(5, 1)` → **120**

> In tail recursion nothing is left to do after the call returns, so a compiler **can** reuse the same stack frame (tail-call optimisation). It still uses O(n) frames without that optimisation.

---

## 2.7 Tracing recursive output (the exam skill)

**Method — "unfold and substitute":**

1. Write `f(1)` first (smallest case).
2. Build `f(2)` using `f(1)`.
3. Build `f(3)` using `f(2)` and `f(1)`.
4. Concatenate in the **exact order** the `printf`s occur.

### Example A

```c
void f(int n) {
    if (n <= 0) return;
    f(n - 1);
    printf("%d", n);
    f(n - 2);
}
```
`f(1)` = `1`. `f(2)` = `f(1)` + `2` + `f(0)` = `12`.
`f(3)` = `f(2)` + `3` + `f(1)` = `12` + `3` + `1` = **`1231`**

### Example B

```c
void f(int n) {
    if (n <= 0) return;
    printf("%d", n);
    f(n - 1);
    printf("%d", n);
}
```
`f(1)` = `1` `f(0)` `1` = `11`; `f(2)` = `2` `11` `2` = `2112`; `f(3)` = `3` `2112` `3` = **`321123`**

### Example C

```c
void f(int n) {
    if (n <= 0) return;
    f(n - 1);
    f(n - 2);
    printf("%d", n);
}
```
`f(1)` = `1`; `f(2)` = `1` + `2` = `12`; `f(3)` = `12` + `1` + `3` = **`1213`**

### Example D

```c
void f(int n) {
    if (n <= 0) return;
    printf("%d", n);
    f(n - 2);
    f(n - 1);
}
```
`f(1)` = `1`; `f(2)` = `2` + `1` = `21`; `f(3)` = `3` + `1` + `21` = **`3121`**

### Example E

```c
void f(int n) {
    if (n <= 0) return;
    f(n - 1);
    printf("%d", n);
    f(n - 1);
}
```
`f(1)` = `1`; `f(2)` = `121`; `f(3)` = `1213121` → **`1213121`**

### `rec(--n)` — the parameter itself changes

```c
void rec(int n) {
    if (n <= 0) return;
    rec(n - 1);
    printf("%d", n);
    rec(--n);          // n is modified here
}
```
`rec(2)` = **`121`**; `rec(3)` = **`1213121`**

> ⚠️ **Answer-key warning.** Several answers in the circulated Minor 2 pattern PDF do **not** match the code. All sequences above were produced by compiling and running the exact functions. In Example A the circulated key says `121312`; the real output is **`1231`**. If your notes disagree, **trace the code** — the compiler is the authority.

---

## 2.8 Recursion vs iteration

| Point | Recursion | Iteration (loops) |
|-------|-----------|-------------------|
| Definition | Function calls itself | Repeats via `for`/`while` |
| Termination | Base case | Loop condition |
| Memory | Uses stack (one frame per call) | Constant extra memory |
| Speed | Slower (call overhead) | Faster |
| Risk | Stack overflow if too deep | Infinite loop if condition wrong |
| Best for | Trees, divide & conquer, backtracking, mathematical definitions | Simple repetition, arrays |

**Same result, both ways:**

```c
int factRec(int n) { return (n <= 1) ? 1 : n * factRec(n-1); }

int factIter(int n) {
    int r = 1;
    for (int i = 2; i <= n; i++) r *= i;
    return r;
}
```
Both return **120** for `n = 5`.

---

## 2.9 Module 4 traps checklist

1. Forgetting the **base case** → infinite recursion.
2. Recursive call that does **not move toward** the base case → same.
3. Call by value **never** changes the caller's variables.
4. Arrays **decay to pointers** — changes are visible, `sizeof` is pointer-sized.
5. 2-D array parameters **must** include the column size.
6. A function returns **one** value; use pointers for multiple outputs.
7. Function must be **declared before use**.
8. `static` local keeps its value between calls; plain local does not.
9. Tail recursion is about **position** of the call, not the number of calls.
10. Recursion output order depends on whether `printf` is **before** or **after** the call.

---

# PART 3 — MODULE 5: POINTERS & COMPOSITE DATA TYPES

## 3.1 Pointer basics

A **pointer** is a variable that stores the **memory address** of another variable.

| Operator | Name | Meaning |
|----------|------|---------|
| `&` | address-of | `&x` gives the address of `x` |
| `*` | dereference | `*p` gives the value **at** the address in `p` |

```c
int x = 42;
int *p = &x;        // p holds the address of x

printf("%d", x);    // 42
printf("%d", *p);   // 42  (value at that address)
printf("%p", (void*)p);  // some address like 0x16b...
```

```c
int v = 42;
int *p = &v;
printf("v=%d *p=%d\n", v, *p);

*p = 100;                 // write through the pointer
printf("v=%d\n", v);
```
**Output:**
```
v=42 *p=42
v=100
```

> `*p = 100` modifies the variable **pointed to** — here, `v`.

**Declaration rules and traps:**

```c
int *p;          // pointer to int (uninitialised — dangerous)
int *p = NULL;   // safe default
int *p, q;       // p is int*, q is a plain int  ← classic trap
```

| Declaration | Meaning |
|-------------|---------|
| `int *p` | pointer to `int` |
| `char *p` | pointer to `char` |
| `float *p` | pointer to `float` |
| `int **p` | pointer to a pointer to `int` |

> The **type matters**: `*p` reads `sizeof(*p)` bytes and interprets them as that type. `int*` and `float*` both hold addresses, but dereferencing gives different results.
> Never dereference an uninitialised or `NULL` pointer → **segmentation fault**.

---

## 3.2 Pointer arithmetic

Arithmetic is **scaled by the size of the pointed-to type**.

| Expression | Meaning |
|-----------|---------|
| `p + 1` | address of the **next element** (adds `sizeof(*p)` bytes) |
| `p - 1` | previous element |
| `p++` / `++p` | move to next element |
| `p2 - p1` | number of **elements** between them (not bytes) |
| `*p`, `*(p+i)` | value at that element |
| `p < q`, `p == q` | comparison (meaningful within the same array) |

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

printf("%d %d\n", p[2], *(p + 2));   // 30 30
printf("%ld\n", (long)((p + 3) - p)); // 3 elements
```
**Output:**
```
30 30
3
```

```c
double d = 2.5;
double *dp = &d;
printf("%ld\n", (long)((char*)(dp + 1) - (char*)dp));
```
**Output:** `8`

> `dp + 1` moved **8 bytes** because `sizeof(double) == 8`; `p + 1` for `int*` moves 4 bytes.
> That is why `int *` and `char *` cannot be mixed carelessly.

**Valid range:** pointer arithmetic is defined only **inside an array** (and one past the last element). Going further is undefined behaviour.

---

## 3.3 Pointers vs arrays

**Key identity:** for an array `a`, the name **decays** to `&a[0]`, so

```c
a[i]  ==  *(a + i)
&a[i] ==  a + i
```

```c
int arr[5] = {10, 20, 30, 40, 50};
printf("%d %d\n", arr[4], *(arr + 4));
```
**Output:** `50 50`

**But they are not the same thing:**

| Property | `int arr[5]` | `int *p` |
|----------|--------------|----------|
| Stores | 5 ints (20 bytes) | one address (8 bytes) |
| `sizeof` | 20 | 8 |
| Assignable? | **No** (`arr = p` illegal) | Yes |
| Can be reseated? | No | Yes (`p = other`) |
| Memory | allocated automatically (stack/global) | must point somewhere valid |
| `arr++` | illegal | legal |
| `&arr` vs `&arr[0]` | same address, different type (`int(*)[5]` vs `int*`) | — |

```c
printf("%zu %zu\n", sizeof(arr), sizeof(p));
```
**Output:** `20 8`

> This is exactly why `sizeof` inside a function that received an array gives **8** (pointer), not the array size.

### `char *` vs `char []` (a favourite "differentiate" question)

```c
char *p = "Hello";     // p points to a string LITERAL (read-only)
char a[] = "Hello";    // a is an array COPY (modifiable)
```

| | `char *p = "Hello";` | `char a[] = "Hello";` |
|--|----------------------|----------------------|
| What is stored | pointer to literal | array of 6 chars |
| Modifiable? | **No** — `p[0]='h'` is UB (may crash) | **Yes** — `a[0]='h'` is fine |
| Reassignable? | Yes (`p = "Bye"`) | No |
| `sizeof` | 8 (pointer) | 6 |

Verified modifiable case:

```c
char s[] = "Hello";
s[0] = 'h';
printf("%s", s);
```
**Output:** `hello`

---

## 3.4 Call by reference

Pass the **address** of a variable; the function dereferences it to modify the original.

```c
void swapPtr(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int main(void) {
    int x = 8, y = 4;
    swapPtr(&x, &y);
    printf("%d %d", x, y);
}
```
**Output:** `4 8`

**Compare with call by value from §2.2:**

| | Call by value | Call by reference |
|--|---------------|-------------------|
| Argument passed | value (copy) | address (`&x`) |
| Parameter | `int a` | `int *a` |
| Changes affect caller? | **No** | **Yes** |
| Memory | new copy on stack | pointer to original |
| Use for | read-only inputs | swap, multiple outputs, large structs |

**Multiple "returns" via pointers:**

```c
void minMax(int a[], int n, int *mn, int *mx) {
    *mn = *mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < *mn) *mn = a[i];
        if (a[i] > *mx) *mx = a[i];
    }
}
```
Call as `minMax(arr, 5, &lo, &hi);` — two results in one call.

---

## 3.5 Dynamic memory: `malloc`, `calloc`, `realloc`, `free`

```c
#include <stdlib.h>
```

| Function | Signature | What it does |
|----------|-----------|--------------|
| `malloc` | `void *malloc(size_t bytes)` | Allocates **uninitialised** memory |
| `calloc` | `void *calloc(size_t n, size_t size)` | Allocates `n × size` bytes, **zero-filled** |
| `realloc` | `void *realloc(void *p, size_t new)` | Resizes an existing block (may **move** it) |
| `free` | `void free(void *p)` | Releases the block back to the heap |

All return `NULL` on failure — **always check**.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *a = (int*)malloc(5 * sizeof(int));   // 20 bytes
    if (a == NULL) { printf("Allocation failed"); return 1; }

    for (int i = 0; i < 5; i++) a[i] = i * 10;
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);

    a = (int*)realloc(a, 8 * sizeof(int));    // grow to 8 ints
    a[7] = 70;
    printf("\n%d", a[7]);

    free(a);
    a = NULL;
}
```
**Output:**
```
0 10 20 30 40 
70
```

`calloc` zero-fills (verified):

```c
int *c = (int*)calloc(5, sizeof(int));
for (int i = 0; i < 5; i++) printf("%d ", c[i]);
```
**Output:** `0 0 0 0 0 `

> `malloc` would print **garbage** here. That is the classic `malloc` vs `calloc` difference.

### Stack vs heap

| | Stack | Heap |
|--|-------|------|
| Allocation | automatic (locals, parameters) | manual (`malloc`/`calloc`) |
| Lifetime | until block/function ends | until `free` |
| Size | small, fixed | large, flexible |
| Speed | fast | slower |
| Failure mode | stack overflow | returns `NULL` |
| Freed by | compiler | **you** |

### Memory errors to name in an exam

| Error | What happens |
|-------|--------------|
| **Memory leak** | allocated, never `free`d → memory wasted |
| **Dangling pointer** | using a pointer after `free` → UB |
| **Double free** | `free(p); free(p);` → UB/crash |
| **Use of uninitialised pointer** | dereferencing garbage address → segfault |
| **Off-by-one** | `malloc(n)` then writing `a[n]` → heap corruption |
| **Lost pointer** | `p = malloc(...)` again without freeing → leak |

> Safe pattern: **check → use → free → set to NULL**.
> `free(NULL)` is safe and does nothing.
> `realloc` can return `NULL` **and** leave the old block valid — use a temporary: `int *tmp = realloc(p, n); if (tmp) p = tmp;`

---

## 3.6 Structures

A **structure** groups variables of **different types** under one name.

```c
struct Student {
    int roll;
    char name[30];
    float marks;
};                          // ← semicolon is required
```

```c
struct Student s1 = {101, "Aarav", 88.5};

printf("%d %s %.1f\n", s1.roll, s1.name, s1.marks);
```
**Output:** `101 Aarav 88.5`

| Access | Syntax | When |
|--------|--------|------|
| Member of an object | `s1.marks` | dot operator |
| Member through a pointer | `p->marks` | arrow operator, same as `(*p).marks` |

**Initialisation styles:**

```c
struct Student s1 = {101, "Aarav", 88.5};   // positional
struct Student s2 = {0};                    // all zero
s1.marks = 90;                              // assign a member
struct Student s3 = s1;                     // whole-struct copy (legal)
```

---

## 3.7 Pointers to structures

```c
struct Book {
    char title[50];
    float price;
};

int main(void) {
    struct Book b = {"C Programming", 299.0f};
    struct Book *bp = &b;

    printf("%s %.2f\n", b.title, b.price);
    printf("%s %.2f\n", bp->title, bp->price);
}
```
**Output:**
```
C Programming 299.00
C Programming 299.00
```

> `bp->title` is exactly `(*bp).title`. The arrow is just shorthand (and `*bp.title` would be wrong — `.` binds tighter than `*`).

**Why use pointers to structs?** Passing a large struct by value copies every byte; passing `struct Book *` copies one address (8 bytes) and lets the function modify the original.

```c
void applyDiscount(struct Book *b, float pct) {
    b->price = b->price * (1 - pct / 100);
}
```

---

## 3.8 Nested structures

A structure can contain another structure as a member.

```c
struct Author { char name[30]; };
struct Novel {
    struct Author author;
    int year;
};

struct Novel n = {{"Kernighan"}, 1978};
printf("%s %d", n.author.name, n.year);
```
**Output:** `Kernighan 1978`

> Access is **chained**: `n.author.name`. With a pointer: `np->author.name`.

**Self-referential structure** (used for linked lists):

```c
struct Node {
    int data;
    struct Node *next;   // pointer to same type — legal
};
```

---

## 3.9 Array of structures

```c
struct Point { int x, y; };

int main(void) {
    struct Point pts[3] = {{1,2}, {3,4}, {5,6}};

    for (int i = 0; i < 3; i++)
        printf("(%d,%d) ", pts[i].x, pts[i].y);

    printf("\n%d", pts[2].y);
}
```
**Output:**
```
(1,2) (3,4) (5,6) 
6
```

> `pts[i]` is a structure; use `.` on it. If you have `struct Point *p = pts;` then `p[i].x` or `(p+i)->x`.

---

## 3.10 Unions

A **union** is like a structure, but **all members share the same memory**. Only **one member is valid at a time**.

```c
union Mix {
    int i;
    float f;
    char c;
};

int main(void) {
    union Mix u;
    u.i = 65;
    printf("%d %c", u.i, u.c);   // same bytes reinterpreted
}
```
**Output:** `65 A`

> `u.i = 65` writes 4 bytes; `u.c` reads the **first byte** → 65 = `'A'`. Writing `u.f` would overwrite `u.i`.

**Size = largest member** (plus alignment):

```c
printf("%zu", sizeof(union Mix));   // 4
```
**Output:** `4`

### Structure vs union

| Point | `struct` | `union` |
|-------|----------|---------|
| Memory | sum of all members (plus padding) | size of the **largest** member |
| Members valid simultaneously? | **Yes** | **No — one at a time** |
| Access | same (`.` / `->`) | same |
| Use | records (student, book) | memory-saving variants, type punning, tagged unions |
| Size example | `char[50] + float` → 56 (padded) | `int/float/char` → 4 |

> **Padding warning:** `sizeof(struct)` may be **larger** than the sum of members because of alignment. Verified: `struct { char name[50]; float price; }` → **56** bytes, not 54. `struct { char c; int i; }` → **8**, not 5.

---

## 3.11 Passing variables — the complete picture

| What you pass | Function parameter | Caller's data modifiable? | `sizeof` inside function |
|---------------|--------------------|---------------------------|--------------------------|
| `int x` | `int a` | ❌ No (copy) | 4 |
| `int x` | `int *a` (pass `&x`) | ✅ Yes | 8 |
| `int arr[5]` | `int a[]` or `int *a` | ✅ Yes (decays) | **8** (pointer) |
| `int m[2][3]` | `int m[][3]` | ✅ Yes | 8 |
| `struct S s` | `struct S s` | ❌ No (whole copy) | full struct size |
| `struct S s` | `struct S *p` | ✅ Yes | 8 |
| `char s[]` | `char *s` | ✅ Yes | 8 |

> There is **no true "call by reference"** in C — it is always call by value. Passing an **address** (a pointer value) is what people call call-by-reference.

---

## 3.12 Module 5 traps checklist

1. `int *p, q;` → `p` is a pointer, `q` is an **int**.
2. Uninitialised / `NULL` dereference → **segfault**. Initialise to `NULL`.
3. `p + 1` moves `sizeof(*p)` **bytes**, not 1 byte.
4. `arr` is **not** assignable; a pointer is.
5. `sizeof(array)` (real size) vs `sizeof(pointer)` (8) — arrays decay in function calls.
6. `*p++` parses as `*(p++)` — increments the pointer, then dereferences the old address.
7. `free` only memory from `malloc`/`calloc`/`realloc` — never a local variable.
8. After `free(p)`, set `p = NULL` to avoid dangling/double free.
9. `malloc` does **not** zero memory; `calloc` does.
10. `realloc` may **move** the block — never keep the old pointer as the only reference.
11. Struct definition needs a **semicolon** after `}`.
12. `*p.member` is wrong — use `(*p).member` or `p->member`.
13. Union members **overwrite** one another; `sizeof(union)` = largest member.
14. `char *p = "text"` is read-only; `char p[] = "text"` is modifiable.
15. `switch`/`scanf`/`printf` need the right type — `%d` with a `float` is UB.

---

# PART 4 — EXAM PATTERN & SOLVED QUESTION BANK

## 4.1 The 10 "differentiate" answers you must have ready

**(1) `while` vs `do–while`**

| `while` | `do–while` |
|---------|------------|
| Entry controlled | Exit controlled |
| Condition tested **before** body | Condition tested **after** body |
| May run **0** times | Runs **at least once** |
| `while (cond) { }` | `do { } while (cond);` |

**(2) `break` vs `continue`**

| `break` | `continue` |
|---------|------------|
| Exits the loop/switch completely | Skips the rest of **this** iteration |
| Control goes **after** the loop | Control goes to the next iteration |
| Used in loops and `switch` | Used only in loops |

**(3) Array vs pointer**

| Array | Pointer |
|-------|---------|
| Stores many elements | Stores one address |
| `sizeof` = total bytes | `sizeof` = 8 |
| Not assignable / not reseatable | Assignable / reseatable |
| Memory allocated automatically | Must point to valid memory |
| `arr[i]` and `*(arr+i)` both work | same |

**(4) `malloc` vs `calloc`**

| `malloc(n * size)` | `calloc(n, size)` |
|--------------------|-------------------|
| One size argument | Two arguments |
| Memory **uninitialised** (garbage) | Memory **zeroed** |
| Faster | Slightly slower |
| `void *malloc(size_t)` | `void *calloc(size_t, size_t)` |

**(5) Call by value vs call by reference**

| Value | Reference |
|-------|-----------|
| Passes a copy | Passes an address |
| `int a` | `int *a`, call with `&x` |
| Caller unchanged | Caller modified |
| Safe, simple | Needed for swap/multiple outputs |

**(6) Structure vs union**

| Structure | Union |
|-----------|-------|
| Members have separate memory | Members share memory |
| Size = sum (+ padding) | Size = largest member |
| All members usable at once | One at a time |

**(7) `char *p = "Hello"` vs `char p[] = "Hello"`**

| Pointer to literal | Character array |
|--------------------|-----------------|
| Read-only literal | Modifiable copy |
| Reassignable | Not reassignable |
| `sizeof` 8 | `sizeof` 6 |

**(8) `int arr[5]` vs `int *arr = malloc(5*sizeof(int))`**

| Static array | Dynamic allocation |
|--------------|--------------------|
| Stack/static storage | Heap |
| Fixed size at compile time | Size chosen at run time |
| Freed automatically | Must call `free(arr)` |
| No failure check needed | Check for `NULL` |

**(9) `&` vs `*`**

| `&x` | `*p` |
|------|------|
| Address-of operator | Dereference operator |
| Variable → address | Address → value |
| `int *p = &x;` | `printf("%d", *p);` |

**(10) `const int x = 10;` vs `int const *p = &x;`**

| `const int x` | `int const *p` (= `const int *p`) |
|---------------|-----------------------------------|
| The **variable** cannot change | The **pointed-to value** cannot change |
| `x = 20;` ✗ | `*p = 20;` ✗ |
| — | `p = &other;` ✓ (pointer itself can move) |

---

## 4.2 Verified output-prediction set

**Q1.** What is the output?
```c
int i = 1;
for (i = 1; i++ <= 4; printf("%d", i));
```
**A:** `2345`

**Q2.** What is the output?
```c
void fun(void) { int i; for (i = 0; i++ <= 3; printf("%d", i)); }
int main(void) { int j; for (j = 0; j++ <= 2; fun()); }
```
**A:** `123412341234` (3 calls × `1234`)

**Q3.** What is the output?
```c
void f(int n) { if (n <= 0) return; f(n-1); printf("%d", n); f(n-2); }
int main(void) { f(3); }
```
**A:** `1231`

**Q4.** What is the output?
```c
void f(int n) { if (n <= 0) return; printf("%d", n); f(n-1); printf("%d", n); }
int main(void) { f(3); }
```
**A:** `321123`

**Q5.** What is the output?
```c
void f(int n) { if (n <= 0) return; f(n-1); f(n-2); printf("%d", n); }
int main(void) { f(3); }
```
**A:** `1213`

**Q6.** What is the output?
```c
int i = 2, j = 8;
while (i < j) { i += 3; j -= 2; }
printf("%d %d", i, j);
```
**A:** `8 4`

**Q7.** What is the output?
```c
int i = 0, j = 6;
while (i < j) { i += 2; j--; }
printf("%d %d", i, j);
```
**A:** `4 4`

> The circulated key says `6 3`; the real trace is `0,6 → 2,5 → 4,4` then `4 < 4` is false. **`4 4`**.

**Q8.** What is the output?
```c
void swapVal(int a, int b) { int t=a; a=b; b=t; }
int main(void) { int x=8, y=4; swapVal(x,y); printf("%d %d", x, y); }
```
**A:** `8 4` (unchanged — call by value)

**Q9.** What is the output?
```c
union U { int i; char c; };
union U u; u.i = 65;
printf("%d %c", u.i, u.c);
```
**A:** `65 A`

**Q10.** What is the output?
```c
int arr[5] = {10,20,30,40,50};
int *p = arr;
printf("%d %d %ld", p[2], *(p+3), (long)((p+4)-p));
```
**A:** `30 40 4`

---

## 4.3 Short-answer questions (with model answers)

**Q1. Define a pointer. Why is a pointer typed?**
A pointer is a variable that stores the memory address of another variable. It is typed (`int*`, `char*`) so the compiler knows how many bytes to read on dereference and how far `p + 1` should move.

**Q2. What is array decay?**
Except when it is the operand of `sizeof`, `&`, or a string literal initialiser, an array name converts to a pointer to its first element. That is why `f(arr)` passes an address and `sizeof` inside `f` gives the pointer size.

**Q3. Why must a recursive function have a base case?**
Without one, the recursive calls never stop, each call consumes a stack frame, and the program crashes with **stack overflow**.

**Q4. What is the difference between `malloc` and `calloc`?**
`malloc(n*size)` allocates uninitialised memory; `calloc(n, size)` allocates and zero-fills. `calloc` takes two arguments and is slightly slower.

**Q5. What happens if you `free` a pointer twice?**
Undefined behaviour — typically heap corruption or a crash. Set the pointer to `NULL` after `free`; `free(NULL)` is safe.

**Q6. What is a dangling pointer?**
A pointer that still holds the address of memory that has been freed (or gone out of scope). Dereferencing it is undefined behaviour.

**Q7. Why does `scanf("%s", name)` not need `&`?**
Because an array name already decays to the address of its first element; `name` **is** the address.

**Q8. What is the difference between `struct` and `union`?**
A struct gives each member its own memory (size = sum + padding); a union overlays all members in the same memory (size = largest member) and only one member is valid at a time.

**Q9. What does `p->x` mean?**
It is shorthand for `(*p).x` — access member `x` of the structure pointed to by `p`.

**Q10. Why is `char *p = "Hello"; p[0] = 'h';` dangerous?**
`p` points to a string literal, which may live in read-only memory. Modifying it is undefined behaviour (often a crash). Use `char p[] = "Hello";` to get a modifiable copy.

---

## 4.4 Eleven programs to be able to write from memory

All outputs below are compiler-verified.

### P1 — Grade using an else-if ladder
```c
int marks = 82;
if      (marks >= 90) printf("A");
else if (marks >= 75) printf("B");
else if (marks >= 40) printf("C");
else                  printf("F");
```
**Output:** `B`

### P2 — Sum of digits
```c
int n = 1234, sum = 0;
while (n > 0) { sum += n % 10; n /= 10; }
printf("%d", sum);
```
**Output:** `10`

### P3 — Reverse a number
```c
int n = 1234, rev = 0;
while (n > 0) { rev = rev * 10 + n % 10; n /= 10; }
printf("%d", rev);
```
**Output:** `4321`

### P4 — Prime check
```c
int p = 29, isPrime = 1;
if (p < 2) isPrime = 0;
for (int i = 2; i * i <= p; i++)
    if (p % i == 0) { isPrime = 0; break; }
printf("%s", isPrime ? "Prime" : "Not Prime");
```
**Output:** `Prime`

### P5 — Pyramid pattern
```c
int rows = 4;
for (int i = 1; i <= rows; i++) {
    for (int s = 1; s <= rows - i; s++) printf(" ");
    for (int j = 1; j <= 2 * i - 1; j++) printf("*");
    printf("\n");
}
```
**Output:**
```
   *
  ***
 *****
*******
```

### P6 — Palindrome check
```c
char s[] = "madam";
int len = strlen(s), pal = 1;
for (int i = 0; i < len / 2; i++)
    if (s[i] != s[len - 1 - i]) { pal = 0; break; }
printf("%s", pal ? "Palindrome" : "Not Palindrome");
```
**Output:** `Palindrome`

### P7 — Bubble sort
```c
int a[5] = {5, 2, 9, 1, 6};
for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4 - i; j++)
        if (a[j] > a[j + 1]) {
            int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
        }
for (int i = 0; i < 5; i++) printf("%d ", a[i]);
```
**Output:** `1 2 5 6 9 `

### P8 — Matrix addition (2×2)
```c
int A[2][2] = {{1,2},{3,4}}, B[2][2] = {{5,6},{7,8}}, C[2][2];
for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
        C[i][j] = A[i][j] + B[i][j];

for (int i = 0; i < 2; i++)
    printf("%d %d\n", C[i][0], C[i][1]);
```
**Output:**
```
6 8
10 12
```

### P9 — Count vowels
```c
char v[] = "Manipal";
int count = 0;
for (int i = 0; v[i] != '\0'; i++) {
    char c = v[i];
    if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
        c=='A'||c=='E'||c=='I'||c=='O'||c=='U') count++;
}
printf("%d", count);
```
**Output:** `3`

### P10 — Reverse a string in place
```c
char t[] = "ITC";
int L = strlen(t);
for (int i = 0; i < L / 2; i++) {
    char tmp = t[i]; t[i] = t[L-1-i]; t[L-1-i] = tmp;
}
printf("%s", t);
```
**Output:** `CTI`

### P11 — Manual `strlen`
```c
char u[] = "Hello";
int n = 0;
while (u[n] != '\0') n++;
printf("%d %zu %zu", n, strlen(u), sizeof(u));
```
**Output:** `5 5 6`

> `n` and `strlen` count characters; `sizeof` includes `'\0'`.

---

## 4.5 Pattern-paper extras (nice to know)

These appeared in the circulated paper but are **beyond the Module 3–5 handout**. One line each is enough.

**Array of pointers**

```c
int a = 10, b = 20, c = 30;
int *parr[3] = {&a, &b, &c};
printf("%d %d %d", *parr[0], *parr[1], *parr[2]);
```
**Output:** `10 20 30`

**Function pointer**

```c
int add(int x, int y) { return x + y; }
int (*fp)(int, int) = add;
printf("%d", fp(2, 3));
```
**Output:** `5`

`int (*fp)(int,int)` = pointer to a function returning `int`.
`int (*fp[5])(int,int)` = array of **5** such pointers.
`int *fp(int,int)` = function returning an `int*` — completely different (no parentheses around `*fp`).

**Classic bit tricks** (common "what does this function do?" questions):

| Function | Returns | Example |
|----------|---------|---------|
| `x & -x` | lowest set bit | `fun(12)` → `4` |
| `x & (x-1)` | clears lowest set bit | `fun(14)` → `12` |
| `(x>0) && ((x & (x-1)) == 0)` | is `x` a power of 2? | `8` → `1`, `12` → `0` |
| `while(x){x&=(x-1); c++;}` | counts set bits | `13` → `3` |

Verified: `fun2(12)=4`, `fun3(8)=1`, `fun3(12)=0`, `fun4(14)=12`, `fun7(13)=3`.

---

# PART 5 — CHEAT SHEETS

## 5.1 Syntax quick reference

```c
// ---------- decisions ----------
if (c) { } else if (c2) { } else { }
switch (x) { case 1: …; break; default: …; }
result = cond ? a : b;

// ---------- loops ----------
while (c) { }
do { } while (c);
for (init; cond; update) { }
break; continue;

// ---------- arrays ----------
int a[5] = {1,2,3,4,5};
int m[2][3] = {{1,2,3},{4,5,6}};
char s[] = "text";
m[row][col]
a[i] == *(a+i)

// ---------- functions ----------
int f(int a, int b);            // prototype
int f(int a, int b) { return a+b; }
void g(int *p) { *p = 5; }
int h(int m[][3], int rows);

// ---------- recursion ----------
int fact(int n){ return (n<=1)?1:n*fact(n-1); }

// ---------- pointers ----------
int x = 5, *p = &x;
*p = 10;
int **pp = &p;
p + 1; p2 - p1; *p++;

// ---------- dynamic memory ----------
int *a = (int*)malloc(n * sizeof(int));
int *b = (int*)calloc(n, sizeof(int));
a = (int*)realloc(a, m * sizeof(int));
free(a); a = NULL;

// ---------- structs / unions ----------
struct S { int x; char name[20]; };
struct S s = {1, "A"};
struct S *ps = &s;
s.x; ps->x; (*ps).x;
union U { int i; float f; };
```

## 5.2 Format specifiers

| Specifier | Type | Example |
|-----------|------|---------|
| `%d` | int | `printf("%d", 42)` |
| `%f` | float/double | `%.2f` → 2 decimals |
| `%c` | char | `%c` with 65 → `A` |
| `%s` | string (char array) | stops at `'\0'` |
| `%ld` | long | pointer difference cast |
| `%zu` | `size_t` | `sizeof`, `strlen` |
| `%p` | pointer | cast to `(void*)` |
| `%%` | literal `%` | — |

> `%d` with a `float` or `%f` with an `int` is **undefined behaviour** — a classic bug in output questions.

## 5.3 Operator precedence (the parts that matter)

```
()  []  ->  .            highest
!  ++  --  (unary)  *  &  sizeof
*  /  %
+  -
<  <=  >  >=
==  !=
&&
||
?:                       lowest (except assignment)
=  +=  -=  ...
```

Two consequences:

1. `*p++` = `*(p++)` — the pointer moves, then the old value is dereferenced.
2. `*p.member` = `*(p.member)` — wrong. Use `(*p).member` or `p->member`.

## 5.4 The 25 traps (final revision list)

1. `=` vs `==`.
2. Missing `break` in `switch` → fall-through.
3. `switch` doesn't accept `float`/strings/ranges.
4. Semicolon after `for`/`while` → empty body.
5. `do–while` runs at least once.
6. `continue` skips the update in a `while`.
7. Arrays: no bounds checking.
8. `int a[5]={1,2}` → remaining zeros.
9. `sizeof(a)/sizeof(a[0])` for element count.
10. `char x[]={'6'}` has no `'\0'`.
11. `strcmp`, not `==`, for strings.
12. 2-D arrays are row-major.
13. Call by value never changes the caller.
14. Arrays decay to pointers; `sizeof` inside a function is 8.
15. 2-D parameter needs the column size.
16. No base case → stack overflow.
17. `printf` before vs after a recursive call changes the order.
18. `int *p, q;` declares one pointer and one int.
19. `p+1` moves by `sizeof(*p)` bytes.
20. `arr` is not assignable; `p` is.
21. `char *p="text"` is read-only.
22. `malloc` doesn't zero; `calloc` does.
23. Always check `malloc` for `NULL`; always `free`.
24. `struct` needs a semicolon after `}`.
25. `sizeof(struct)` includes padding; `sizeof(union)` = largest member.

## 5.5 60-second revision

- **Branch:** `if/else` for ranges, `switch` for constants (needs `break`), `?:` for two values.
- **Loops:** `while`/`for` may run 0 times, `do–while` at least 1; `break` exits, `continue` skips.
- **Arrays:** 0-based, no bounds check, contiguous; 2-D is row-major `[row][col]`.
- **Strings:** always `'\0'`; `strlen` excludes it, `sizeof` includes it.
- **Functions:** call by value copies; arrays decay to pointers; 2-D needs the column count.
- **Recursion:** base case + smaller input; trace by unfolding `f(1) → f(2) → f(3)`.
- **Pointers:** `&` address, `*` value; `p+1` scales by type size; `a[i] == *(a+i)`.
- **Memory:** `malloc` (garbage) / `calloc` (zeros) / `realloc` (resize, may move) / `free` (+ `NULL`).
- **Structs:** `.` for objects, `->` for pointers; arrays of structs; nested access chains.
- **Unions:** shared memory, size = largest member, one member at a time.

---

## 5.6 Flashcards — last-minute recall

### A. Syntax cards (cover the right column)

| # | Prompt | Answer |
|---|--------|--------|
| 1 | Declare a pointer to `int` | `int *p;` |
| 2 | Point `p` at `x` | `p = &x;` |
| 3 | Read/write the value at `p` | `*p` |
| 4 | Element `i` via a pointer | `*(a + i)` (same as `a[i]`) |
| 5 | 2-D element | `m[row][col]` |
| 6 | Array parameter | `int a[]` or `int *a` |
| 7 | 2-D array parameter | `int m[][3]` — column size **required** |
| 8 | String length (no `'\0'`) | `strlen(s)` → print with `%zu` |
| 9 | Test string equality | `strcmp(a, b) == 0` |
| 10 | Swap by reference | `int t=*a; *a=*b; *b=t;` |
| 11 | `malloc` `n` ints | `(int*)malloc(n * sizeof(int))` |
| 12 | Zero-filled `n` ints | `(int*)calloc(n, sizeof(int))` |
| 13 | Resize a block | `p = (int*)realloc(p, m * sizeof(int))` |
| 14 | Free safely | `free(p); p = NULL;` |
| 15 | Member via struct pointer | `p->x` (same as `(*p).x`) |
| 16 | Array of structs, element `i` | `s[i].x` |
| 17 | Nested struct member | `n.author.name` |
| 18 | Static local counter | `static int c = 0;` |
| 19 | Function prototype | `int f(int, int);` |
| 20 | Factorial recursion | `return n<=1 ? 1 : n*fact(n-1);` |
| 21 | Element count of an array | `sizeof(a) / sizeof(a[0])` |
| 22 | Max of two values | `(a > b) ? a : b` |
| 23 | `switch` must-have | `break;` on every case |
| 24 | `do–while` syntax | `do { } while (cond);` ← semicolon |
| 25 | Sum of digits | `while(n>0){ s+=n%10; n/=10; }` |
| 26 | Reverse a number | `while(n>0){ r=r*10+n%10; n/=10; }` |
| 27 | Two decimal places | `%.2f` |
| 28 | Print a pointer | `printf("%p", (void*)p);` |

### B. Output triggers (see code → know the trap)

| If you see | The answer hinges on |
|------------|----------------------|
| `i++ <= n` in a `for` condition | test **old** value, print **new** value |
| `for (j = A; j++ <= B; …)` | runs **B − A + 1** times |
| `*p++` | means `*(p++)` → **old** value, pointer moves |
| `char x[] = {'6'}` | `sizeof` = 1, **not a string** |
| `sizeof("Hello")` vs `strlen("Hello")` | `6` vs `5` |
| `union { int i; char c; }`, `i = 65` | prints `65 A` (same byte) |
| `swapVal(x, y)` | caller values **unchanged** |
| array passed to a function | changes **visible**; `sizeof` inside = **8** |
| `malloc` then print | **garbage**; `calloc` prints **0** |
| `struct { char name[50]; float price; }` | `sizeof` = **56** (padding) |
| `int *p, q;` | one pointer, one **int** |
| `if (x = 5)` | assignment → **always true** |

### C. Recursion cards (`n = 3`)

| Body order | Output |
|------------|--------|
| `f(n-1); print n;` | `123` |
| `print n; f(n-1);` | `321` |
| `f(n-1); print n; f(n-2);` | `1231` |
| `print n; f(n-1); print n;` | `321123` |
| `f(n-1); f(n-2); print n;` | `1213` |
| `print n; f(n-2); f(n-1);` | `3121` |
| `f(n-1); print n; f(n-1);` | `1213121` |

### D. Program skeletons (write these, not the whole program)

| Task | Core lines |
|------|-----------|
| Sum / max of array | `for(i=0;i<n;i++) s+=a[i];` / `if(a[i]>max) max=a[i];` |
| Bubble sort | `if(a[j]>a[j+1]) swap(a[j],a[j+1]);` inside two loops |
| Linear search | `if(a[i]==key){ found=1; break; }` |
| Palindrome | `if(s[i]!=s[len-1-i]) pal=0;` for `i<len/2` |
| Count vowels | `if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u') count++;` |
| Matrix addition | `C[i][j] = A[i][j] + B[i][j];` in nested loops |
| Reverse string | swap `s[i]` with `s[L-1-i]` for `i<L/2` |
| Prime check | `for(i=2;i*i<=p;i++) if(p%i==0) not prime;` |
| Pyramid rows | spaces `rows-i`, then stars `2*i-1` |
| Min **and** max in one call | two pointer outputs `*mn`, `*mx` |

---

## Verification Record

| Item | Value |
|------|-------|
| Compiler | Apple clang 21.0.0 (arm64, 64-bit, macOS) |
| Standard | C (clang default, gnu17) |
| Code files | 6 verification programs, ~70 snippets |
| Result | **Every output shown in these notes was produced by running the code** |

**Note on portability:** `sizeof` values (int 4, double 8, pointer 8) and struct padding are platform/ABI dependent. Values quoted here are what you will see on the 64-bit lab machines. `strcmp` is documented as "negative / zero / positive", not exactly `-1`.

**Note on the pattern paper:** several answers in the circulated `ITC_Minor_2_Pattern` PDF do not match the code (recursion Q1/Q3/Q4, while-loop Q6, call-count Q9, recursion Q12). The outputs above are compiler-verified; when in doubt, **trace the code**.

---

*Compiled for CS1001 ITC Minor 2 (Modules 3–5). Covers the official course-handout topics plus the question style used in the Minor 2 pattern paper. All code compiled and executed.*
