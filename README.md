# aids.h

[![Tests](https://github.com/alexjercan/aids.h/actions/workflows/test.yml/badge.svg)](https://github.com/alexjercan/aids.h/actions/workflows/test.yml)

Header only library for commonly used helpers and data structures in C
projects. This is a continuation of the
[ds.h](https://github.com/alexjercan/ds.h) project. The name stands for **A**ll
**I**n One **D**ata **S**tructures.

## Features

- **Logging** - File and line information with colored output
- **Temporary Memory Allocator** - Fast allocations for short-lived data
- **Doubly Linked List** - Generic linked list implementation
- **Dynamic Array** - Auto-growing array with type safety
- **Hash Map** - Generic hash table with custom hash and compare functions
- **Priority Queue** - Min-heap based priority queue
- **String Slice** - Efficient string manipulation without copying
- **String Builder** - Dynamic string construction with formatting
- **File I/O Utilities** - Simplified file operations

## Quick Start

To use the library, simply include the header in your C source files:

```c
#define AIDS_IMPLEMENTATION
#include "aids.h"

int main() {
    // Use doubly linked list
    Aids_List list;
    aids_list_init(&list, sizeof(int));

    int value = 42;
    aids_list_push_back(&list, &value);

    int popped_value;
    aids_list_pop_front(&list, &popped_value);
    printf("Popped value: %d\n", popped_value);

    aids_list_free(&list);
    return 0;
}
```

## Building and Testing

### Building Examples

```bash
make        # Build all examples and tests
make clean  # Clean build artifacts
```

### Running Tests

```bash
./checker.sh                    # Run all tests
./checker.sh --memcheck        # Run tests with valgrind memory checking
./checker.sh --verbose         # Show detailed output on failures
./checker.sh --help            # Show all options
```

## Examples

Check the `how_to/` directory for usage examples of different features:

- `001_basic.c` - Basic usage examples
- `002_list.c` - Doubly linked list operations

See `tests/` directory for comprehensive unit tests covering all data structures.

## Documentation

The library is fully documented in the header file. Key features include:

### Macros

- `AIDS_ASSERT(condition, message)` - Assert with formatted message
- `AIDS_TODO(message)` - Mark unimplemented code
- `AIDS_UNREACHABLE(message)` - Mark unreachable code
- `return_defer(code)` - Jump to cleanup label with result code

### Customization

You can customize the library behavior by defining these macros before including the header:

- `AIDSHDEF` - Function linkage (default: `extern`, or `static` with `AIDSH_STATIC`)
- `AIDS_REALLOC` - Memory allocation function (default: `realloc`)
- `AIDS_FREE` - Memory deallocation function (default: `free`)
- `AIDS_NO_TERMINAL_COLORS` - Disable colored logging output
- `AIDS_TEMP_CAPACITY` - Temporary allocator capacity (default: 8MB)
- `AIDS_ARRAY_INIT_CAPACITY` - Initial array capacity (default: 16)

## License

MIT License - see header file for full license text.

## Contributing

Contributions are welcome! Please ensure all tests pass:

```bash
./checker.sh --memcheck
```
