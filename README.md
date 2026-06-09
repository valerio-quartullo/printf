*This project has been created as part of the 42 curriculum by vquartul.*

# ft_printf

---

## Description

`ft_printf` is a re-implementation of the standard C library function `printf`. The goal is to understand how variadic functions work in C, and how formatted output is produced from a format string and a variable number of arguments.

The library handles the following conversions:

| Specifier | Description |
|-----------|-------------|
| `%c` | Single character |
| `%s` | String |
| `%p` | Pointer address |
| `%d` | Signed decimal integer |
| `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned hexadecimal (lowercase) |
| `%X` | Unsigned hexadecimal (uppercase) |
| `%%` | Literal percent sign |

### Bonus — flags and formatting

The bonus part extends the mandatory with full support for:

| Flag | Effect |
|------|--------|
| `-` | Left-align within the field width |
| `0` | Pad with zeros instead of spaces |
| `+` | Always print sign for numeric types |
| ` ` | Space before positive numbers |
| `#` | Alternate form (`0x` prefix for `%x`/`%X`) |
| `width` | Minimum field width |
| `.precision` | Minimum digits for integers, max chars for strings |

---

## Instructions

### Compilation

Clone the repository and compile the library:

```bash
git clone <your_repo_url>
cd ft_printf
make
```

This produces `libftprintf.a`.

To compile with your own program:

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o program
./program
```

### Makefile rules

| Rule | Effect |
|------|--------|
| `make` | Compile the library |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and library |
| `make re` | Full recompilation |

---

## Algorithm and Data Structures

### Parsing approach

The format string is scanned character by character inside `ft_printf`. When a `%` is encountered, control is passed to `parse_flags`, which reads the format specifier in strict left-to-right order:

```
% → [flags] → [width] → [.precision] → type
```

Each component is parsed by a dedicated static function:

- `read_flags` — reads `-`, `0`, `+`, ` `, `#` in any order
- `read_width` — reads a decimal number or `*` (width from `va_arg`)
- `read_precision` — reads `.` followed by a decimal number or `*`

All parsed values are stored in a `t_flags` struct:

```c
typedef struct s_flags
{
    int minus;
    int zero;
    int plus;
    int space;
    int hash;
    int width;
    int precision;
} t_flags;
```

`precision` is initialized to `-1` to distinguish "not specified" from `0` (which has special meaning for some types).

### Why a struct?

A struct was chosen over individual parameters because the number of formatting options makes passing them separately impractical and unreadable. The struct is passed by value to each print function, keeping the interface clean and consistent.

### Dispatch

After parsing, `handle_format` dispatches to the appropriate print function based on the type character. Each function (`print_int`, `print_str`, etc.) receives the value and the `t_flags` struct, and is fully responsible for applying padding, alignment, and formatting.

### Recursive digit printing

Integer and hexadecimal values are printed using recursion: the function calls itself with `n / base` until `n < base`, then writes digits on the way back up. This naturally produces the correct left-to-right order without requiring a buffer or string reversal.

### Padding logic

For each numeric type, the padding logic follows this order:

```
[spaces]  → [sign or 0x]  → [zero padding]  → [precision zeros]  → [digits]  → [trailing spaces]
```

The flag `-` and `0` are mutually exclusive (`-` wins). The flag `0` is ignored when a precision is specified, since precision already controls zero-padding for digits.

---

## Resources

### Documentation

- [printf man page — cppreference.com](https://en.cppreference.com/w/c/io/fprintf)
- [Variadic functions in C — cppreference.com](https://en.cppreference.com/w/c/variadic)
- [stdarg.h — GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)

### Articles and tutorials

- [How printf works internally](https://www.maizure.org/projects/printf/index.html) — detailed walkthrough of the original printf implementation
- [Formatted output — The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)

### Testing

- [printfTester by Tripouille](https://github.com/Tripouille/printfTester) — used to validate mandatory and bonus parts
- [ft_printf_tester by paulo-santana](https://github.com/paulo-santana/ft_printf_tester)

### AI usage

Claude (Anthropic) was used during this project for the following tasks:

- **Explaining concepts**: `va_list`, variadic functions, and how arguments are passed on the stack
- **Debugging**: identifying issues with flag interactions (e.g. `0` flag not being applied, precision overriding zero-padding)
- **Code review**: checking edge cases such as `INT_MIN`, `NULL` strings, zero with `%.0d`, and pointer formatting
- **Structure guidance**: suggesting the separation of parsing, dispatch, and printing into distinct files and functions

All code was written, understood, and validated by the author. AI was used as a learning and debugging tool, not as a code generator.
