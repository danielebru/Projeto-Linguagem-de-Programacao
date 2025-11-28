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

    } while (opcao != 0);

}
