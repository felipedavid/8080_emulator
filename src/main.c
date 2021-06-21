#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./emulator rom\n");
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Could not open the ROM.\n");
        return EXIT_FAILURE;
    }

    int rom_size = lseek(fd, 0L, SEEK_END);
    lseek(fd, 0L, SEEK_SET);

    uint8_t *rom_buffer = (uint8_t *) malloc(rom_size);
    if (!code_buffer) {
        printf("Could not allocate space for the ROM.\n");
        return EXIT_FAILURE;
    }

    read(fd, rom_buffer, rom_size);
    return EXIT_SUCCESS;
}
