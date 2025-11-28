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
