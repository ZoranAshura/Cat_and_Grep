# Simple Bash Utils

Development of Bash text utilities: cat, grep.

## Information

- The programs must be developed in C language of C11 standard using gcc compiler.
- The program code of the cat and grep must be located on the develop branch in the src/cat/ and src/grep/ folders, respectively  
- Do not use outdated and legacy language constructions and library functions. Pay attention to the legacy and obsolete marks in the official documentation on the language and the libraries used. Use the POSIX.1-2017 standard.
- When writing code it is necessary to follow the Google style
- The programs must be executable files with command line arguments
- The programs must be built with Makefile with appropriate targets: s21_cat, s21_grep
- If third-party libraries are used, there must be build scripts in makefile to connect/load them
- Integration tests must cover all flag variants and input values, based on a comparison with the behavior of real Bash utilities 
- The programs must be developed according to the principles of structured programming
- Code duplication must be avoided, common modules must be reused between the utilities. Common modules can be moved to a separate folder src/common
- You can use standard and non-standard C libraries, or you can use your own developed libraries from other projects
- The statement of the message in the case of an error does not matter
- Input via stdin is not required to be supported

## Part 1. Working with the cat utility

You need to develop a cat utility:
- Support of all flags (including GNU versions) specified [above](#cat-options)
- The source, header, and build files must be placed in the src/cat/ directory
- The resulting executable file must be placed in the directory src/cat/ and named s21_cat

## Part 2. Working with grep utility

You need to develop the grep utility:
- Support of the following flags: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep

## Part 3. Implementation of some grep utility flags

Bonus assignment for extra points. You need to develop the grep utility:
- Support of all flags, including: `-h`, `-s`, `-f`, `-o`
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep

## Part 4. Implementation of grep utility flag combinations

Bonus assignment for extra points. You need to develop the grep utility:
- Support of all flags, including their _pair_ combinations (e.g. `-iv`, `-in`)
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep
