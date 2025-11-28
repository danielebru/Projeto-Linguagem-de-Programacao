

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartorio.h"
//comeca-2812
void listarDocumentos(int tipo)
{
    FILE *arquivo;// esse ponteiro para arquivo serve para utilizar as funcionalidades de arquivo em c
    char nomeArquivo[20]; // nome do arquivo que será aberto ao listar o determinado tipo doc
    Documento *lista = NULL; // ponteiro para o vetor dinâmico, ele guardará os docs lidos
    int capacidade = 5;      // o vetor dinâmico lista, vai te ruma capacidade inicial de 10, que dita quantos elementos ele pode armazenar
    int quantidade = 0;      // conta quantos elementos foram colocados no vetor

  char nomes[5] [20]={"nascimento.txt", "obito.txt","casamentos.txt" ,"divorcio.txt","outros.txt"};
  // essse s.c define o nome do arquivo ao usar a funcao strcpy, e qual título.
    switch (tipo)
    {
    case 1:
        strcpy(nomeArquivo, nomes[0]);
        printf("NASCIMENTOS: \n");
        break;
    case 2:
        strcpy(nomeArquivo, nomes[1]);
        printf("ÓBITOS: \n");
        break;
    case 3:
        strcpy(nomeArquivo, nomes[2]);
        printf("CASAMENTOS: \n");
        break;
    case 4:
        strcpy(nomeArquivo, nomes[3]);
        printf("DIVÓRCIOS: \n");
        break;
    default:
        strcpy(nomeArquivo, nomes[4]);
        printf("OUTROS DOCUMENTOS: \n");
    }

    // abre o arquivo para leitura ( usando o modo read- r), para visualizarmos os arquivos criados
    arquivo = fopen(nomeArquivo, "r");
  
    if (arquivo == NULL) // caso o arquivo nao exista ou nao possa ser acessado, ele vai retornar null, por isso essa logica parecida com alocacao
    {
        printf("Nenhum documento encontrado nesta categoria.\n");
        printf("(O arquivo %s ainda não existe)\n", nomeArquivo);
        return;
    }

    lista = (Documento *)malloc(capacidade * sizeof(Documento));  // aloca memória inicial para o vetor de documentos (utiliznado a capacidade inicialmente indicada)
    if (lista == NULL) //verifica se a alocação foi feita
    {
        printf("Erro ao fazer alocação!\n");
        fclose(arquivo);
        return;
    }
    // lê os documentos do arquivo
    while (fscanf(arquivo, "%d-%49[^-]-%11[^-]-%99[^\n]\n",
                  &lista[quantidade].tipo,
                  lista[quantidade].nome,
                  lista[quantidade].data,
                  lista[quantidade].detalhes) == 4)
    {
        quantidade++;

    
        if (quantidade >= capacidade)     //usando realloc, pois quando a qtd de arquivos ja registrados, atingir o msm numero da capacidade, no caso 5, 
                                          //o vetor dinamico que guarda os documentos aumenta
        {
            capacidade *= 2; // assim, multiplicando sequencialmente a capacidade por dois, ha um crescimento maior na capacidade de armazenamento do vetor dinâmico
            Documento *a = (Documento *)realloc(lista, capacidade * sizeof(Documento)); // usar um ponteiro temporário, pois se fizesse lista = realloc(lista, nova alocacao). perde o ponteiro antigo

            if (a == NULL)
            {
                printf("Erro ao fazer a realocação\n");
                free(lista);
                fclose(arquivo);
                return;
            }
            lista = a; // Atualiza o ponteiro
        }
    }

    fclose(arquivo);

    // lista os documentos encontrados
    if (quantidade == 0) printf("Nenhum documento registrado.\n");
    else
    {
        printf("Quantidade de documentos registrados: %d\n", quantidade);

       
        Documento *ptr = lista;  // Usa ponteiro para percorrer o vetor

        for (int i = 0; i < quantidade; i++)
        {
            printf("Documento %d:\n", i + 1);
            printf("  Nome: %s\n", lista[i].nome);// sabe-se que lista [i]. nome == (lista +i) -> nome 
            printf("  Data: %s\n",  lista[i].data);
            printf("  Detalhes: %s\n",  lista[i].detalhes);
    

            ptr++; // Avança o ponteiro para o próximo documento
        }
    }


    free(lista);     // libera a memoria alocada primeiramente
}



//termina
Documento lerDocumento()
{
    Documento d;

    printf("REGISTRO\n");
    printf("Tipos disponíveis:\n");
    printf("  1 - Nascimento\n");
    printf("  2 - Óbito\n");
    printf("  3 - Casamento\n");
    printf("  4 - Divórcio\n");
    printf("  5 - Outros Documentos\n");
    printf("Digite o tipo do documento (1-5): ");
    scanf("%d", &d.tipo);
    getchar(); // Limpa o buffer do enter

    printf("Digite o nome: ");
    fgets(d.nome, 50, stdin);
    d.nome[strcspn(d.nome, "\n")] = '\0'; // Remove o \n do final

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
    if (d.tipo < 1 || d.tipo > 5)
    {
        printf("Tipo inválido.\n");
        return 0;
    }

    int tamanhoNome = strlen(d.nome);
    if (tamanhoNome < 2)
    {
        printf("Nome deve possuir no mínimo 2 caracteres.\n");
        return 0;
    }

    if (strlen(d.data) != 10)
    {
        printf("Data tem que estar no formato dd/mm/aaaa.\n");
        return 0;
    }

    if (d.data[2] != '/' || d.data[5] != '/')
    {
        printf("Posição incorreta das barras.\n");
        return 0;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;
if (d.data[i] < '0' || d.data[i] > '9')
        {
            printf("Caracteres inválidos.\n");
            return 0;
        }
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
    printf("Nome: ");
    fgets(d.nome, 50, stdin);
    d.nome[strcspn(d.nome, "\n")] = '\0';

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

    fprintf(arq, "%d-%s-%s-%s\n", d.tipo, d.nome, d.data, d.detalhes);
    fclose(arq);

    printf("Documento salvo em %s\n", Arquivo);
}
/* fucnao de  menu antiga
void menu()
{
    int opcao;
    do
    {
        printf("\nCARTÓRIO DIGITAL\n");
        printf("1 - Registrar documento\n");
        // FAZER O DE SAIR, E DE LISTAR DOCUMENTOS DE CADA TIPO
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            registrarDocumento();
            break;
        case 0:printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
*/
void menu()
{
    int opcao;
    //Documento[struct] tipo inicializado no cartorio.h
    Documento doc;//ve se vamos usar
    do
    {
        printf("\nCARTÓRIO DIGITAL\n");
        printf("1-Registrar documento\n");
        printf("2-Listar nascimentos.\n");
        printf("3-Listar óbitos.\n");
        printf("4-Listar Casamentos.\n");
        printf("5-Listar divórcios.\n");
        printf("6-Listar outros documentos\n");
        printf("0 - Sair do cartório.\n");
    
        printf("Digite a opção desejada:\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            registrarDocumento();
            break;
        case 2:
            listarDocumentos(1);
            break;
        case 3:
             listarDocumentos(2);
            break;
        case 4:
            listarDocumentos(3);
            break;
        case 5:
            listarDocumentos(5);
            break;
        case 6:
             listarDocumentos(6);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

}
    } while (opcao != 0);

}


