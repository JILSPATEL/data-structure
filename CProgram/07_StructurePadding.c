#include <stddef.h>
#include <stdio.h>

/*
 * Structure padding is extra memory inserted by the compiler between members
 * so that each member starts at an address suitable for its alignment.
 *
 * A typical layout of PaddedData is:
 *
 * Offset  0: char first   (1 byte)
 * Offset  1: padding      (3 bytes)
 * Offset  4: int number   (4 bytes)
 * Offset  8: char last    (1 byte)
 * Offset  9: tail padding (3 bytes)
 *
 * Therefore, the typical total size is 12 bytes, not 6 bytes.
 * The exact result can vary between compilers and systems.
 */
typedef struct {
    char first;
    int number;
    char last;
} PaddedData;

/*
 * Reordering members can reduce padding. The int is placed first, followed
 * by the two chars, so this layout typically uses 8 bytes instead of 12.
 */
typedef struct {
    int number;
    char first;
    char last;
} CompactData;

int main(void) {
    PaddedData padded = {'A', 100, 'Z'};
    CompactData compact = {100, 'A', 'Z'};

    printf("PaddedData\n");
    printf("  Size of structure: %zu bytes\n", sizeof(PaddedData));
    printf("  Offset of first:   %zu bytes\n", offsetof(PaddedData, first));
    printf("  Offset of number:  %zu bytes\n", offsetof(PaddedData, number));
    printf("  Offset of last:    %zu bytes\n", offsetof(PaddedData, last));
    printf("  Address of object: %p\n", (void *)&padded);
    printf("  Address of first:  %p\n", (void *)&padded.first);
    printf("  Address of number: %p\n", (void *)&padded.number);
    printf("  Address of last:   %p\n\n", (void *)&padded.last);

    printf("CompactData\n");
    printf("  Size of structure: %zu bytes\n", sizeof(CompactData));
    printf("  Offset of number:  %zu bytes\n", offsetof(CompactData, number));
    printf("  Offset of first:   %zu bytes\n", offsetof(CompactData, first));
    printf("  Offset of last:    %zu bytes\n", offsetof(CompactData, last));
    printf("  Address of object: %p\n", (void *)&compact);
    printf("  Address of number: %p\n", (void *)&compact.number);
    printf("  Address of first:  %p\n", (void *)&compact.first);
    printf("  Address of last:   %p\n", (void *)&compact.last);

    return 0;
}
