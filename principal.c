#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "vendas.h"

int menu()
{
    int op;
    do
    {

        printf("Incluir produto................................[1]\n");
        printf("Alterar dados do produto.......................[2]\n");
        printf("Pesquisar produto .............................[3]\n");
        printf("Listar todos os produtos.......................[4]\n");
        printf("Comprar produto................................[5]\n");
        printf("Balanco de estoque.............................[6]\n");
        printf("Incluir venda..................................[7]\n");
        printf("Pesquisar venda................................[8]\n");
        printf("Vendas por data................................[9]\n");
        printf("Vendas por mes.................................[10]\n\n");

        printf("SAIR...........................................[0]\n\n\n");


        printf("Digite a opcao......:");
        scanf("%d", &op);

        if (op < 0 || op > 10)
        {
            printf("Opcao invalida!!!\n");
        }


    }
    while (op < 0 || op > 10);

    return op;
}

void main()
{
    int op;

    do
    {
        system("cls");
        op = menu();

        switch(op)
        {
        case 1:
            cadastrar();
            break;

        case 2:
            alterar();
            break;

        case 3:
            pesquisar();
            break;

        case 4:
            listar();
            break;

        case 5:
            comprar();
            break;

        case 6:
            balancete();
            break;

        case 7:
            cadastrar_venda();
            break;

        case 8:
            localizar_venda();
            break;

        case 9:
            localizar_venda_data();
            break;

        case 10:
            localizar_venda_mes();
            break;
        }

        system("pause");

    }
    while (op != 0);

}


