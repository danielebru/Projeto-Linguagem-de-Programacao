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
