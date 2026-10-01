#include <stdio.h>
#include "registradores.h"

static int falhas = 0;

static void confere(const char *nome, int condicao) {
    printf("[%s] %s\n", condicao ? "OK  " : "FALHA", nome);
    if (!condicao) falhas++;
}

int main(void) {
    Registradores r;
    uint64_t v = 0;

    reg_inicializar(&r);
    confere("inicializar zera A", r.A == 0);
    confere("inicializar zera F", r.F == 0);

    reg_escrever(&r, REGS_A, 0x123456);
    reg_ler(&r, REGS_A, &v);
    confere("escrever/ler A", v == 0x123456);

    reg_escrever(&r, REGS_X, 0x1FFFFFF);          /* passa de 24 bits */
    reg_ler(&r, REGS_X, &v);
    confere("X trunca em 24 bits", v == 0xFFFFFF);

    reg_escrever(&r, REGS_F, 0xFFFFFFFFFFFFFFull); /* passa de 48 bits */
    reg_ler(&r, REGS_F, &v);
    confere("F trunca em 48 bits", v == 0xFFFFFFFFFFFFull);

    confere("ID invalido na leitura",   reg_ler(&r, 7, &v) == -1);
    confere("ID invalido na escrita",   reg_escrever(&r, 99, 1) == -1);
    confere("reg_valido(PC)",           reg_valido(REGS_PC) == 1);
    confere("reg_valido(7) e falso",    reg_valido(7) == 0);

    reg_escrever(&r, REGS_PC, 0xFFFFFE);
    reg_avancar_pc(&r, 3);
    confere("PC da a volta em 24 bits", r.PC == 0x000001);

    reg_set_cc(&r, REGS_CC_MAIOR);
    confere("CC maior", reg_get_cc(&r) == REGS_CC_MAIOR);
    reg_set_cc(&r, REGS_CC_IGUAL);
    confere("CC igual", reg_get_cc(&r) == REGS_CC_IGUAL);

    printf("\n");
    reg_imprimir(&r);

    printf("\n%s\n", falhas == 0 ? "TODOS OS TESTES PASSARAM" : "HOUVE FALHAS");
    return falhas != 0;
}
