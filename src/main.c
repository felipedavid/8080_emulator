#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"

uint8_t *open_rom(char *rom_name);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./emulator rom\n");
        exit(1);
    }
    uint8_t rom_buffer = open_rom(argv[1]);

    return EXIT_SUCCESS;
}

uint8_t *open_rom(char *rom_name) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Could not open the ROM.\n");
        exit(1);
    }

    int rom_size = lseek(fd, 0L, SEEK_END);
    lseek(fd, 0L, SEEK_SET);

    uint8_t *rom_buffer = (uint8_t *) malloc(rom_size);
    if (!code_buffer) {
        printf("Could not allocate space for the ROM.\n");
        exit(0);
    }

    read(fd, rom_buffer, rom_size);

    return rom_buffer;
}
