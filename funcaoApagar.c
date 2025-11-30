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

    // seleciona o arquivo pra apagar
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
        printf("Erro de alocação!\n");
        fclose(arquivo);
        return;
    }

    // Lê os registros
    while (fscanf(arquivo, "%d-%49[^-]-%11[^-]-%99[^\n]\n",
                  &lista[quantidade].tipo,
                  lista[quantidade].nome,
                  lista[quantidade].data,
                  lista[quantidade].detalhes) == 4)
    {
        quantidade++;

        if (quantidade >= capacidade)
        {
            capacidade *= 2;
            Documento *tmp = realloc(lista, capacidade * sizeof(Documento));
            if (!tmp)
            {
                printf("Erro ao realocar!\n");
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

    // lista os registros
    printf("\nRegistros encontrados em %s:\n", nomeArquivo);
    for (int i = 0; i < quantidade; i++)
    {
        printf("%d) %s | %s | %s\n",
               i + 1,
               lista[i].nome,
               lista[i].data,
               lista[i].detalhes);
    }

    // Usuário escolhe qual quer remover
    printf("\nDigite o número do registro a remover: ");
    scanf("%d", &remover);

    if (remover < 1 || remover > quantidade)
    {
        printf("Opção inválida!\n");
        free(lista);
        return;
    }

    remover--; // ajusta índice

    // Reescreve o arquivo sem o item removido
    temp = fopen(nomeArquivo, "w");
    if (!temp)
    {
        printf("Erro ao abrir arquivo temporário!\n");
        free(lista);
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (i != remover)
        {
            fprintf(temp, "%d-%s-%s-%s\n",
                    lista[i].tipo,
                    lista[i].nome,
                    lista[i].data,
                    lista[i].detalhes);
        }
    }

    fclose(temp);
    free(lista);

    printf("Registro removido com sucesso!\n");
}
