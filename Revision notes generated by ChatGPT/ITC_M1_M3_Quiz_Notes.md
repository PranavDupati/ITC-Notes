# ITC Lab Quiz: M1-M3 Quick Revision

## M1 - computers, C, and number systems

### C program skeleton

```c
#include <stdio.h>

int main(void) {
    /* statements */
    return 0;
}
```

- A **high-level language** such as C is readable by people; machine code and assembly are low-level.
- C is compiled: write `.c` source -> compile -> executable -> run.
- `main` is where execution starts. `#include <stdio.h>` provides `printf` and `scanf`.
- `//` begins a single-line comment; `/* ... */` is a block comment.

### Number systems

- Base/radix `b`: `(d_n ... d_0)_b = sum(d_i * b^i)`.
- Decimal -> binary: repeatedly divide the integer part by 2 and read remainders **bottom to top**.
- Binary -> decimal: add powers of 2 at positions containing 1. Example: `(101101)_2 = 32 + 8 + 4 + 1 = 45`.
- Binary -> octal: group bits in 3 from the right. Binary -> hexadecimal: group bits in 4 from the right; `A-F = 10-15`.
- Fractional binary positions are `2^-1, 2^-2, ...`. Example: `(101.11)_2 = 5.75`.
- For an `n`-bit unsigned number, range = `0` to `2^n - 1`.
- To make `-x` in two's complement: write `x` in the chosen width, flip every bit, add 1. In `n` bits the range is `-2^(n-1)` to `2^(n-1)-1`.
- IEEE 754 floating point stores a sign, exponent, and fraction; many decimals cannot be represented exactly. Do not compare computed floats with `==` unless the question explicitly expects it.

## M2 - C fundamentals, operators, and I/O

### Types, constants, and format specifiers

| Use | Type | `printf` | `scanf` |
|---|---|---|---|
| integer | `int` | `%d` | `%d` |
| real number | `float` | `%f` | `%f` |
| more precision | `double` | `%f` | `%lf` |
| character | `char` | `%c` | `%c` |
| word/string | `char name[20]` | `%s` | `%19s` |

```c
const float PI = 3.14159f;  /* cannot be changed */
int count = 0;
float average;
```

### Operators to know

- Arithmetic: `+  -  *  /  %`. With two `int` values, `/` discards the fraction: `5 / 2` is `2`. Use `5.0f / 2` for `2.5`.
- Relational: `< <= > >= == !=` produce `1` (true) or `0` (false).
- Logical: `&&` AND, `||` OR, `!` NOT. Use `==` to compare, not `=` (assignment).
- Update: `++x` increments then uses; `x++` uses then increments.
- Bitwise: `& | ^ ~ << >>` operate on individual bits; do not confuse `&` with `&&` or `|` with `||`.
- Parenthesise mixed expressions. It makes intent clear and avoids precedence mistakes.

### Input/output traps

```c
int n;
float x;
scanf("%d %f", &n, &x);       /* & is required for ordinary variables */
printf("n=%d, x=%.2f\n", n, x);
```

- The `&` in `scanf` gives the variable's address. Do **not** use `&` with a character array: `scanf("%19s", name);`.
- For `sqrt`, `fabs`, or `pow`, include `<math.h>` and compile with `gcc file.c -o file -lm`.

## M3 - selection, loops, arrays, and strings

### Selection

```c
if (mark >= 50) {
    printf("Pass\n");
} else {
    printf("Fail\n");
}

char result = (mark >= 50) ? 'P' : 'F';
```

- Use `if ... else if ... else` for ranges or general conditions.
- `switch` is useful for exact integer/character choices. Each case normally ends with `break`; without it, execution falls through to the next case.

### Loops

```c
for (int i = 0; i < n; i++) { /* known count */ }
while (condition) { /* test before each iteration */ }
do { /* runs at least once */ } while (condition);
```

- `break` exits the nearest loop or switch immediately.
- `continue` skips the rest of this iteration and goes to the next one.
- For an array of size `n`, valid indices are `0` through `n - 1`; `a[n]` is out of bounds.

### Arrays and strings

```c
int a[5] = {2, 4, 6, 8, 10};
int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
char word[20] = "hello";      /* ends with the null character '\\0' */
```

- Traverse a 1D array with one loop; traverse a 2D array with nested loops.
- A string is a `char` array ending in `\0`. `%s` reads one word only (stops at whitespace).

## High-value lab-question patterns

1. Area/perimeter or dot product - direct formula + `scanf`/`printf`.
2. Extract digits or convert a decimal integer to binary - `%` and `/`.
3. Manhattan/Euclidean distance - `fabs` / `sqrt`; link `-lm`.
4. Triangle validity - calculate three sides; invalid if **any** pair sum is `<=` the third.
5. Largest/even-odd/grade - `if-else` or ternary.
6. Menu/day/month - `switch` and `break`.
7. Array sum, maximum, reverse, count positives/even values - `for` loop.
8. Matrix sum/transpose - nested loops.

## 60-second submission check

- Is every variable declared with the right type?
- Are your `scanf` format specifiers correct, and did you use `&` where needed?
- Did you use `==` in a condition?
- Are all loop bounds `< n`, not `<= n`?
- Does every intended `switch` case have `break`?
- For math functions: did you include `<math.h>` and compile with `-lm`?

## Practice files in this folder

- `01_decimal_to_binary.c` - division/remainder and a loop
- `02_geometry.c` - the class-assignment family: Manhattan and Euclidean distance
- `03_grade_and_menu.c` - `if-else`, ternary, and `switch`
- `04_array_stats.c` - sum, max, even count, and average
- `05_matrix_addition.c` - a 2D array/nested-loop pattern
- `06_string_count.c` - character arrays and a simple string loop

Compile ordinary files with `gcc filename.c -Wall -Wextra -std=c11 -o filename`; compile `02_geometry.c` with `-lm` at the end.
