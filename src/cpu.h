#include <stdio.h>

typedef struct {
    uint8_t z;
    uint8_t s;
    uint8_t p;
    uint8_t cy;
    uint8_t ac;
    uint8_t pad;
} condition_codes_t;

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    condition_codes_t cc;
    uint8_t int_enable;
} state_t;

void not_implemented(state_t *state);
void emulate_instruction();
