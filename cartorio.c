#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartorio.h"

void apagarRegistro(int tipo)
{
    FILE *arquivo, *temp;
    char nomeArquivo[20];
    Documento *lista = NULL;
    int capacidade = 5, quantidade = 0;
    int remover;

    char nomes[5][20] = {
        "nascimento.txt", "obito.txt", "casamento.txt", "divorcio.txt", "outros.txt"
    };

    switch(tipo)
    {
        case 1: strcpy(nomeArquivo, nomes[0]); break;
        case 2: strcpy(nomeArquivo, nomes[1]); break;
        case 3: strcpy(nomeArquivo, nomes[2]); break;
        case 4: strcpy(nomeArquivo, nomes[3]); break;
        default: strcpy(nomeArquivo, nomes[4]);
    }

    arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        printf("Nenhum documento encontrado nesta categoria.\n");
        return;
    }

    lista = malloc(capacidade * sizeof(Documento));
    if (!lista)
    {
        fclose(arquivo);
        return;
    }

    while (fscanf(arquivo, "%d-%49[^-]-%49[^-]-%11[^-]-%99[^\n]\n",
                  &lista[quantidade].tipo,
                  lista[quantidade].nome,
                  lista[quantidade].nome2,
                  lista[quantidade].data,
                  lista[quantidade].detalhes) == 5)
    {
        quantidade++;
        if (quantidade >= capacidade)
        {
            capacidade *= 2;
            Documento *tmp = realloc(lista, capacidade * sizeof(Documento));
            if (!tmp)
            {
                free(lista);
                fclose(arquivo);
                return;
            }
            lista = tmp;
        }
    }
    fclose(arquivo);

    if (quantidade == 0)
    {
        printf("Nenhum registro para remover.\n");
        free(lista);
        return;
    }

    printf("\nRegistros encontrados em %s:\n", nomeArquivo);
    for (int i = 0; i < quantidade; i++)
    {
        if (lista[i].tipo == 3 || lista[i].tipo == 4)
        {
            printf("%d) %s & %s | %s | %s\n",
                   i + 1, lista[i].nome, lista[i].nome2, lista[i].data, lista[i].detalhes);
        }
        else
        {
            printf("%d) %s | %s | %s\n",
                   i + 1, lista[i].nome, lista[i].data, lista[i].detalhes);
        }
    }

    printf("\nDigite o número do registro a remover: ");
    scanf("%d", &remover);

    if (remover < 1 || remover > quantidade)
    {
        free(lista);
        return;
    }

    remover--;

    temp = fopen(nomeArquivo, "w");
    if (!temp)
    {
        free(lista);
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (i != remover)
        {
            fprintf(temp, "%d-%s-%s-%s-%s\n",
                    lista[i].tipo,
                    lista[i].nome,
                    lista[i].nome2,
                    lista[i].data,
                    lista[i].detalhes);
        }
    }

    fclose(temp);
    free(lista);

    printf("Registro removido com sucesso!\n");
}


void listarDocumentos(int tipo)
{
    FILE *arquivo;
    char nomeArquivo[20];
    Documento *lista = NULL;
    int capacidade = 5;
    int quantidade = 0;

    char nomes[5][20] = {
        "nascimento.txt", "obito.txt","casamento.txt" ,"divorcio.txt","outros.txt"
    };

    switch (tipo)
    {
    case 1: strcpy(nomeArquivo, nomes[0]); break;
    case 2: strcpy(nomeArquivo, nomes[1]); break;
    case 3: strcpy(nomeArquivo, nomes[2]); break;
    case 4: strcpy(nomeArquivo, nomes[3]); break;
    default: strcpy(nomeArquivo, nomes[4]);
    }

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Nenhum documento encontrado nesta categoria.\n");
        printf("(O arquivo %s ainda não existe)\n", nomeArquivo);
        return;
    }

    lista = malloc(capacidade * sizeof(Documento));
    if (!lista)
    {
        fclose(arquivo);
        return;
    }

    while (fscanf(arquivo, "%d-%49[^-]-%49[^-]-%11[^-]-%99[^\n]\n",
                  &lista[quantidade].tipo,
                  lista[quantidade].nome,
                  lista[quantidade].nome2,
                  lista[quantidade].data,
                  lista[quantidade].detalhes) == 5)
    {
        quantidade++;
        if (quantidade >= capacidade)
        {
            capacidade *= 2;
            Documento *a = realloc(lista, capacidade * sizeof(Documento));
            if (!a)
            {
                free(lista);
                fclose(arquivo);
                return;
            }
            lista = a;
        }
    }

    fclose(arquivo);

    if (quantidade == 0) printf("Nenhum documento registrado.\n");
    else
    {
        printf("Quantidade de documentos registrados: %d\n", quantidade);
        for (int i = 0; i < quantidade; i++)
        {
            printf("Documento %d:\n", i + 1);
            if (lista[i].tipo == 3 || lista[i].tipo == 4)
            {
                printf("  Cônjuge 1: %s\n", lista[i].nome);
                printf("  Cônjuge 2: %s\n", lista[i].nome2);
            }
            else
            {
                printf("  Nome: %s\n", lista[i].nome);
            }
            printf("  Data: %s\n", lista[i].data);
            printf("  Detalhes: %s\n", lista[i].detalhes);
        }
    }

    free(lista);
}


Documento lerDocumento()
{
    Documento d;

    printf("REGISTRO\n");
    printf("1 - Nascimento\n");
    printf("2 - Óbito\n");
    printf("3 - Casamento\n");
    printf("4 - Divórcio\n");
    printf("5 - Outros\n");
    printf("Digite o tipo do documento (1-5): ");
    scanf("%d", &d.tipo);
    getchar();

    if (d.tipo == 3 || d.tipo == 4)
    {
        printf("Nome do cônjuge 1: ");
        fgets(d.nome, 50, stdin);
        d.nome[strcspn(d.nome, "\n")] = '\0';

        printf("Nome do cônjuge 2: ");
        fgets(d.nome2, 50, stdin);
        d.nome2[strcspn(d.nome2, "\n")] = '\0';
    }
    else
    {
        printf("Nome: ");
        fgets(d.nome, 50, stdin);
        d.nome[strcspn(d.nome, "\n")] = '\0';
        strcpy(d.nome2, "");
    }

    printf("Digite a data (dd/mm/aaaa): ");
    fgets(d.data, 12, stdin);
    d.data[strcspn(d.data, "\n")] = '\0';

    printf("Digite os detalhes: ");
    fgets(d.detalhes, 100, stdin);
    d.detalhes[strcspn(d.detalhes, "\n")] = '\0';

    return d;
}

int validarDocumento (Documento d)
{
    if (d.tipo < 1 || d.tipo > 5) return 0;

    if (d.tipo == 3 || d.tipo == 4)
    {
        if (strlen(d.nome) < 2) return 0;
        if (strlen(d.nome2) < 2) return 0;
    }
    else
    {
        if (strlen(d.nome) < 2) return 0;
    }

    if (strlen(d.data) != 10) return 0;
    if (d.data[2] != '/' || d.data[5] != '/') return 0;

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5) continue;
        if (d.data[i] < '0' || d.data[i] > '9') return 0;
    }

    return 1;
}

void registrarDocumento()
{
    Documento d;

    printf("registro de documento\n");
    printf("Tipos de documento:\n");
    printf("1 - Nascimento\n2 - Óbito\n3 - Casamento\n4 - Divórcio\n5 - Outros\n");
    printf("Digite o tipo (1-5): ");
    scanf("%d", &d.tipo);
    getchar();

    if (d.tipo == 3 || d.tipo == 4)
    {
        printf("Nome do cônjuge 1: ");
        fgets(d.nome, 50, stdin);
        d.nome[strcspn(d.nome, "\n")] = '\0';

        printf("Nome do cônjuge 2: ");
        fgets(d.nome2, 50, stdin);
        d.nome2[strcspn(d.nome2, "\n")] = '\0';
    }
    else
    {
        printf("Nome: ");
        fgets(d.nome, 50, stdin);
        d.nome[strcspn(d.nome, "\n")] = '\0';
        strcpy(d.nome2, "");
    }

    printf("Data (dd/mm/aaaa): ");
    fgets(d.data, 12, stdin);
    d.data[strcspn(d.data, "\n")] = '\0';

    printf("Informações:\n");
    fgets(d.detalhes, 100, stdin);
    d.detalhes[strcspn(d.detalhes, "\n")] = '\0';

    if (!validarDocumento(d))
    {
        printf("Documento Inválido");
        return;
    }

    char Arquivo[20];

    switch (d.tipo)
    {
    case 1: strcpy(Arquivo, "nascimento.txt"); break;
    case 2: strcpy(Arquivo, "obito.txt"); break;
    case 3: strcpy(Arquivo, "casamento.txt"); break;
    case 4: strcpy(Arquivo, "divorcio.txt"); break;
    case 5: strcpy(Arquivo, "outros.txt"); break;
    }

    FILE *arq = fopen(Arquivo, "a");
    if (!arq) return;

    fprintf(arq, "%d-%s-%s-%s-%s\n",
            d.tipo, d.nome, d.nome2, d.data, d.detalhes);

    fclose(arq);

    printf("Documento salvo em %s\n", Arquivo);
}

void menu()
{
    int opcao;

    do
    {
        printf("\nCARTÓRIO DIGITAL\n");
        printf("1-Registrar documento\n");
        printf("2-Listar nascimentos.\n");
        printf("3-Listar óbitos.\n");
        printf("4-Listar Casamentos.\n");
        printf("5-Listar divórcios.\n");
        printf("6-Listar outros documentos\n");
        printf("7 - Apagar registro\n");
        printf("0 - Sair do cartório.\n");

        printf("Digite a opção desejada:\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: registrarDocumento(); break;
        case 2: listarDocumentos(1); break;
        case 3: listarDocumentos(2); break;
        case 4: listarDocumentos(3); break;
        case 5: listarDocumentos(4); break;
        case 6: listarDocumentos(5); break;
        case 7:
            printf("Qual categoria deseja apagar?\n");
            printf("1-Nascimentos\n2-Óbitos\n3-Casamentos\n4-Divórcios\n5-Outros\n");
            scanf("%d", &opcao);
            apagarRegistro(opcao);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}
