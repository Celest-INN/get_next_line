*This project has been created as part of the 42 curriculum by erzhuo.*

# get_next_line

## Description

The **get_next_line** project aims to implement a function in C that reads a file descriptor line by line.  
Each call to the function returns the next line from the file, including the newline character (`\n`) if it exists, and keeps track of the reading progress between calls.

The main challenge of this project is to correctly manage memory, handle partial reads, deal with end-of-file (EOF) situations, and preserve unread data between function calls using static variables.

This project introduces important concepts such as:
- File descriptors
- Static variables
- Buffer-based reading with `read()`
- Memory allocation and cleanup
- Robust handling of edge cases

---

## Instructions

### Compilation

This project does not include a Makefile and must be compiled manually.

To compile the project with the default buffer size, run:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```
To compile with a custom buffer size, use:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```
Replace 42 with any positive value to test different buffer sizes.

---

## Algorithm Explanation and Justification

The goal of this project is to implement `get_next_line(int fd)`, a function that returns one line at a time from a file descriptor while preserving unread data between successive calls.

### Core Concept: Persistent Stash

Because a line can be longer than `BUFFER_SIZE`, data read from the file may not contain a full line.  
To handle this, the algorithm uses a **static buffer called `stash`**, which stores all characters that have been read but not yet returned.

The use of a static variable is essential: it allows the function to remember leftover data across multiple calls to `get_next_line`, ensuring continuity in reading.

---

### Algorithm Overview

The algorithm is divided into four clear steps, each handled by a dedicated function:

1. **Reading data (`read_and_stash`)**  
   Data is read from the file descriptor into a temporary buffer using `read()`.  
   The buffer is appended to `stash` until either:
   - a newline character (`'\n'`) is found, or
   - end-of-file (EOF) is reached.  

   This guarantees that `stash` contains enough data to extract a complete line without performing unnecessary reads.

2. **Extracting a line (`get_line_before_seperator`)**  
   Once a newline is present in `stash` (or EOF is reached), the function extracts the first line from `stash`.  
   The returned line includes the newline character if it exists, as required by the subject.

3. **Updating the stash (`free_stash_and_return_new_stash`)**  
   After extracting the line, the already returned portion is removed from `stash`.  
   Only the remaining unread data is kept for the next call.  
   The old `stash` is freed to avoid memory leaks.

4. **Function coordination (`get_next_line`)**  
   The main function coordinates the entire process:
   - validates inputs,
   - fills `stash` if needed,
   - extracts and returns one line,
   - updates `stash` for the next invocation.

---

### Edge Case Handling

This algorithm correctly handles:
- arbitrary `BUFFER_SIZE` values (including very small sizes),
- lines split across multiple `read()` calls,
- files ending without a trailing newline,
- empty files,
- and read errors.

EOF is detected when `read()` returns `0`. In that case, the remaining content of `stash` (if any) is returned once, and subsequent calls return `NULL`.

---

### Justification of the Approach

This design was chosen because it:
- ensures correctness regardless of buffer size,
- minimizes unnecessary reads by stopping as soon as a newline is found,
- cleanly separates responsibilities between reading, extracting, and state management,
- and provides explicit and safe memory handling.

The algorithm follows the expected approach of the 42 curriculum and is easy to reason about, test, and defend during evaluation.

---

## Resources

### Technical References

- Linux manual pages:
  - `man 2 read`
  - `man 3 malloc`
  - `man 3 free`
- 42 documentation on file descriptors and static variables

### AI Usage Disclosure

AI tools were used during this project to:
- clarify concepts such as file descriptors, static variables, and EOF handling,
- review algorithm logic and edge cases,
- and help improve documentation clarity.

All implementation decisions were understood and validated by the author.  
No AI-generated code was used without careful analysis and adaptation.



