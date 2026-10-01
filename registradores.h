#ifndef REGISTRADORES_H
#define REGISTRADORES_H

/*
 * registradores.h - banco de registradores do SIC/XE (Parte 1).
 *
 * Autonomo: nao depende de memoria.h nem de sicxe.h. Os IDs seguem a
 * numeracao do formato 2 do SIC/XE (A=0, X=1, L=2, B=3, S=4, T=5, F=6,
 * PC=8, SW=9), entao o decodificador pode usar o numero que le da
 * instrucao direto como ID.
 */

#include <stdint.h>

#define REGS_MASK24 0xFFFFFFu            /* A, X, L, B, S, T, PC, SW: 24 bits */
#define REGS_MASK48 0xFFFFFFFFFFFFull    /* F: 48 bits                        */

/* IDs dos registradores (nomes com prefixo REGS_ para nao colidir com os
 * REG_* de memoria.h nem com os SICXE_REG_* da parte 4). */
enum {
    REGS_A  = 0,
    REGS_X  = 1,
    REGS_L  = 2,
    REGS_B  = 3,
    REGS_S  = 4,
    REGS_T  = 5,
    REGS_F  = 6,
    REGS_PC = 8,
    REGS_SW = 9
};

/* Codigo condicional (CC), guardado nos 2 bits de baixo do SW. */
enum {
    REGS_CC_MENOR = 0,   /* '<' */
    REGS_CC_IGUAL = 1,   /* '=' */
    REGS_CC_MAIOR = 2    /* '>' */
};

typedef struct {
    uint32_t A, X, L, B, S, T, PC, SW;   /* 24 bits uteis cada */
    uint64_t F;                          /* 48 bits uteis      */
} Registradores;

/* Zera todos os registradores. */
void reg_inicializar(Registradores *r);

/* 1 se o ID corresponde a um registrador existente, 0 caso contrario. */
int reg_valido(int id);

/* Nome do registrador ("A", "X", ..., "SW") ou "?" se o ID for invalido. */
const char *reg_nome(int id);

/* Le o registrador para *valor. Retorna 0 em sucesso, -1 se ID invalido. */
int reg_ler(const Registradores *r, int id, uint64_t *valor);

/* Escreve no registrador, truncando para 24 bits (48 bits no F).
 * Retorna 0 em sucesso, -1 se ID invalido. */
int reg_escrever(Registradores *r, int id, uint64_t valor);

/* Soma 'bytes' ao PC (volta a 24 bits). Usado apos buscar cada instrucao. */
void reg_avancar_pc(Registradores *r, uint32_t bytes);

/* Codigo condicional no SW. */
void reg_set_cc(Registradores *r, int cc);
int  reg_get_cc(const Registradores *r);

/* Imprime todos os registradores em hexa, uma linha cada. */
void reg_imprimir(const Registradores *r);

#endif
