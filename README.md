# Higa-OS

This is an small custom operating system based on Unix that also uses GRUB.

It is based in x86 (32 bits) architecture and it was / it is still being developed following the https://wiki.osdev.org/ as base of study, also the ["The little book about OS Development"](https://littleosbook.github.io/).

## Current features

1. Simple VGA mode [x]
2. Simple IDT [x]
3. Simple terminal [x]
4. Simple memory manager [x]
5. Reimplementation of some LibC files like strings.h and stdio.h [ ]
6. Simple GDT [ ]
7. Unit tests [ ]
8. Simple file system [ ]
9. Simple interpreter for loading custom programs [ ]
10. Simple scheduler [ ]

We won't add audio, bluetooth and internet support. Perhaps, in the future, we can discuss to add into it.

## How to contribute

Feel free to open new pull requests to improve the current code or to implement new features.

Some rules you must follow before opening a new pull request:

1. Always specify what you are going to change or to add in the PR's description.
2. If you aren't changing some code inside the LibC based files, you must use snake_case. It includes for new type definitions. Constants are UPPER_CASE.
