#ifndef CARTORIO_H
#define CARTORIO_H

typedef struct
{
    int tipo;
    char nome[50];
    char data[12];
    char informacoes[100];
} Documento;

int validarDocumento(Documento d);
void registrarDocumento();
void listarTudo();

#endif
