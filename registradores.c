#include <stdio.h>
#include "registradores.h"

void reg_inicializar(Registradores *r) {
    r->A = r->X = r->L = r->B = 0;
    r->S = r->T = r->PC = r->SW = 0;
    r->F = 0;
}

int reg_valido(int id) {
    switch (id) {
        case REGS_A: case REGS_X: case REGS_L: case REGS_B:
        case REGS_S: case REGS_T: case REGS_F:
        case REGS_PC: case REGS_SW:
            return 1;
        default:
            return 0;
    }
}

const char *reg_nome(int id) {
    switch (id) {
        case REGS_A:  return "A";
        case REGS_X:  return "X";
        case REGS_L:  return "L";
        case REGS_B:  return "B";
        case REGS_S:  return "S";
        case REGS_T:  return "T";
        case REGS_F:  return "F";
        case REGS_PC: return "PC";
        case REGS_SW: return "SW";
        default:      return "?";
    }
}

int reg_ler(const Registradores *r, int id, uint64_t *valor) {
    switch (id) {
        case REGS_A:  *valor = r->A;  break;
        case REGS_X:  *valor = r->X;  break;
        case REGS_L:  *valor = r->L;  break;
        case REGS_B:  *valor = r->B;  break;
        case REGS_S:  *valor = r->S;  break;
        case REGS_T:  *valor = r->T;  break;
        case REGS_F:  *valor = r->F;  break;
        case REGS_PC: *valor = r->PC; break;
        case REGS_SW: *valor = r->SW; break;
        default:      return -1;
    }
    return 0;
}

int reg_escrever(Registradores *r, int id, uint64_t valor) {
    uint32_t v24 = (uint32_t)(valor & REGS_MASK24);

    switch (id) {
        case REGS_A:  r->A  = v24; break;
        case REGS_X:  r->X  = v24; break;
        case REGS_L:  r->L  = v24; break;
        case REGS_B:  r->B  = v24; break;
        case REGS_S:  r->S  = v24; break;
        case REGS_T:  r->T  = v24; break;
        case REGS_F:  r->F  = valor & REGS_MASK48; break;
        case REGS_PC: r->PC = v24; break;
        case REGS_SW: r->SW = v24; break;
        default:      return -1;
    }
    return 0;
}

void reg_avancar_pc(Registradores *r, uint32_t bytes) {
    r->PC = (r->PC + bytes) & REGS_MASK24;
}

void reg_set_cc(Registradores *r, int cc) {
    r->SW = (r->SW & ~0x3u) | ((uint32_t)cc & 0x3u);
}

int reg_get_cc(const Registradores *r) {
    return (int)(r->SW & 0x3u);
}

void reg_imprimir(const Registradores *r) {
    printf("A  = %06X\n", (unsigned)r->A);
    printf("X  = %06X\n", (unsigned)r->X);
    printf("L  = %06X\n", (unsigned)r->L);
    printf("B  = %06X\n", (unsigned)r->B);
    printf("S  = %06X\n", (unsigned)r->S);
    printf("T  = %06X\n", (unsigned)r->T);
    printf("F  = %012llX\n", (unsigned long long)r->F);
    printf("PC = %06X\n", (unsigned)r->PC);
    printf("SW = %06X\n", (unsigned)r->SW);
}
