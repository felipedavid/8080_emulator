#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

uint8_t *open_file(char *file_name, int *buffer_size);
void disassemble_file(char *code_buffer);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./disassembler rom.h\n");
        return EXIT_FAILURE;
    }
    disassemble_file(argv[1]);
    return EXIT_SUCCESS;
}

// Open the file, and copies into a allocated buffer
uint8_t *open_file(char *file_name, int *buffer_size) {
    int fd = open(file_name, O_RDONLY); 
    if (fd == -1) {
        printf("Could not open the file.\n");
        exit(-1);
    }

    *buffer_size = lseek(fd, 0L, SEEK_END); 
    if (*buffer_size == -1) {
        exit(-1);
    }
    lseek(fd, 0L, SEEK_SET); // set the file offset to original position

    uint8_t *code_buffer = (uint8_t *) malloc(*buffer_size);
    if (!code_buffer) {
        printf("Could not allocate space for the file in memory.\n");
        exit(-1);
    }

    read(fd, code_buffer, *buffer_size);
    return code_buffer;
}

// Iterate over opcodes buffer a print the assembly representation
void disassemble_file(char *file_name) {
    int buffer_size;
    uint8_t *code_buffer = open_file(file_name, &buffer_size);

    int pc = 0;
    int op_size;
    while (pc < buffer_size) {
        uint8_t *code = &code_buffer[pc];
        op_size = 1;

        printf("%04x ", pc);
        switch(*code) {
            case 0x00: printf("NOP"); break;
            case 0x01: printf("LXI  B,#$%02x%02x", code[2], code[1]); op_size=3; break;
            case 0x02: printf("STAX B"); break;
            case 0x03: printf("INX B"); break;
            case 0x04: printf("INR B"); break;
            case 0x05: printf("DCR B"); break;
            case 0x06: printf("MVI B,#$%02x", code[1]); op_size=2; break;
        }
        printf("\n");

        pc += op_size;
    }

    free(code_buffer);
}
