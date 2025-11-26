#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int tipo;
    char nome[50];
    char data[12];
    char informacoes[100];
} Documento;

void registrarDocumento()
{
    Documento d;

    printf("registro de documento\n");
    printf("Tipos de documento:\n");
    printf("1 - Nascimento\n2 - Óbito\n3 - Casamento\n4 - Divórcio\n5 - Outros\n");
    printf("Digite o tipo (1-5): ");
    scanf("%d", &d.tipo);
    getchar();
    printf("Nome: ");
    fgets(d.nome, 50, stdin);
    d.nome[strcspn(d.nome, "\n")] = '\0';

    printf("Data (dd/mm/aaaa): ");
    fgets(d.data, 12, stdin);
    d.data[strcspn(d.data, "\n")] = '\0';

    printf("Informações:\n");
    fgets(d.informacoes, 100, stdin);
    d.informacoes[strcspn(d.informacoes, "\n")] = '\0';

    if (d.tipo < 1 || d.tipo > 5)
    {
        printf("\nTipo de documento não existente\n");
        return;
    }

    char Arquivo[20];

    switch (d.tipo)
    {
    case 1:
        strcpy(Arquivo, "nascimento.txt");
        break;
    case 2:
        strcpy(Arquivo, "obito.txt");
        break;
    case 3:
        strcpy(Arquivo, "casamento.txt");
        break;
    case 4:
        strcpy(Arquivo, "divorcio.txt");
        break;
    case 5:
        strcpy(Arquivo, "outros.txt");
        break;
    }

    FILE *arq = fopen(Arquivo, "a");

    if (!arq)
    {
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    fprintf(arq, "%d-%s-%s-%s\n", d.tipo, d.nome, d.data, d.informacoes);
    fclose(arq);

    printf("Documento salvo em %s\n", Arquivo);
}
void menu()
{
    int opcao;
    do
    {
        printf("\nCARTÓRIO DIGITAL\n");
        printf("1 - Registrar documento\n");
        // FAZER O DE SAIR, E DE LISTAR DOCUMENTOS DE CADA TIPO
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            registrarDocumento();
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}

int main()
{


    menu();
    return 0;
}
