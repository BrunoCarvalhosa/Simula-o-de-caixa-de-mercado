#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{

    int codigo;
    char nome[50];
    float preco;
    int estoque;

} prod;

int localizar(int codigo)
{
    int posicao = -1, pos_atual;
    FILE *arquivo;
    prod produto;

    arquivo = fopen("produtos.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Nao foi possível abrir o arquivo\n");
    }
    else
    {
        fread(&produto, sizeof(prod),1, arquivo);
        pos_atual = 0;

        while (!feof(arquivo) )
        {
            if(produto.codigo == codigo)
            {
                posicao = pos_atual;
            }
            fread(&produto, sizeof(prod),1, arquivo);
            pos_atual ++;
        }

        fclose(arquivo);

    }
    return posicao;
}

prod leitura()
{
    prod produto;
    int validade;


    do
    {
        printf("Codigo do produto - 0 para sair: ");
        scanf("%d", &produto.codigo);

        validade = localizar(produto.codigo);
        if(validade == -1)
        {

        }

        else
        {
            printf("Codigo ja registrado!!\n");
        }
    }
    while (validade != -1);
    do
    {
        if(produto.codigo != 0 && produto.codigo > 0)
        {
            printf("Nome.......: ");
            fflush(stdin);
            gets(produto.nome);
            printf("Preco......: ");
            scanf("%f", &produto.preco);
            printf("Estoque....: ");
            scanf("%d", &produto.estoque);
        }
        else if(produto.codigo < 0)
        {
            printf("Codigo invalido\n");
        }
    }
    while (produto.codigo < 0);

    if(produto.codigo == 0)
        printf("SAIU\n");

    return produto;
}

void cadastrar()
{
    FILE *arquivo;
    prod produto;
    int codigo, validade;


    arquivo = fopen("produtos.dat", "ab");

    if(arquivo == NULL)
    {
        printf("Nao foi possível abrir o arquivo\n");
    }
    else
    {
        produto = leitura();

        while(produto.codigo != 0)
        {
            fwrite(&produto, sizeof(prod), 1, arquivo);
            produto = leitura();
        }

        fclose(arquivo);
    }
}

void alterar()
{
    int posicao;
    int codigo;
    FILE *arquivo;
    prod produto;

    arquivo = fopen("produtos.dat", "rb+");

    if(arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo\n");
    }
    else
    {
        printf("Digite o codigo do produto para alteracao: ");
        scanf("%d", &codigo);

        posicao = localizar(codigo);
        if(posicao == -1)
        {
            printf("Produto nao encontrado\n");
        }
        else
        {

            printf("\nNovo nome:");
            fflush(stdin);
            gets(produto.nome);

            printf("\nNovo preco:");
            scanf("%f", &produto.preco);

            printf("\nNovo estoque:");
            scanf("%d", &produto.estoque);

            fseek(arquivo, posicao*sizeof(prod), SEEK_SET);
            fwrite(&produto, sizeof(prod), 1, arquivo);

            printf("Alteracao concluida!!\n");
        }
        fclose(arquivo);

    }

}

void listar_um_produto(int codigo)
{
    FILE *arquivo;
    prod produto;
    int posicao;

    arquivo = fopen("produtos.dat", "rb+");

    if(arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!!\n");
    }
    else
    {
        posicao = localizar(codigo);
        if(posicao == -1)
            printf("Produto nao encontrado!!\n");
        else
        {
            fseek(arquivo, posicao*sizeof(prod), SEEK_SET);
            fread(&produto, sizeof(prod), 1, arquivo);
            printf(" Cod  Nome                              Preco     Qtd\n");
            printf("=====================================================\n");
            printf("%05d %-30s %10.2f %5d\n", produto.codigo, produto.nome, produto.preco, produto.estoque);
        }
        fclose(arquivo);

    }
}

void listar()
{
    FILE *arquivo;
    prod produto;

    arquivo = fopen ("produtos.dat", "rb");

    if (arquivo != NULL)
    {

        fread(&produto, sizeof(prod), 1, arquivo);

        printf(" Cod  Nome                              Preco     Qtd\n");
        printf("=====================================================\n");


        while(!feof(arquivo))
        {
            printf("%05d %-30s %10.2f %5d\n", produto.codigo, produto.nome, produto.preco, produto.estoque);
            fread(&produto, sizeof(prod), 1, arquivo);
        }
        fclose(arquivo);
    }
}

void pesquisar()
{
    int codigo;

    printf("Digite o codigo do produto que deseja vizualizar: ");
    scanf("%d", &codigo);
    listar_um_produto(codigo);
}

void comprar()
{
    FILE *arquivo;
    int posicao;
    int qtd;
    int codigo;
    prod produto;

    arquivo = fopen("produtos.dat", "rb+");

    if(arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!!\n");
    }
    else
    {


        printf("Digite o codigo para compra: ");
        scanf("%d", &codigo);

        posicao = localizar(codigo);

        if(posicao == -1)
        {
            printf("Produto nao existe!!\n");
        }
        else
        {
            printf("Informe a quantidade comprada:");
            scanf("%d", &qtd);

            fseek(arquivo, posicao*sizeof(prod), SEEK_SET);
            fread(&produto, sizeof(prod),1,  arquivo);

            produto.estoque = produto.estoque + qtd;

            fseek(arquivo, posicao*sizeof(prod), SEEK_SET);
            fwrite(&produto, sizeof(prod), 1, arquivo);

            fclose(arquivo);

        }
    }
}

void balancete()
{
    FILE *arquivo;
    prod produto;
    int totalEstoque=0;
    float valor_produto, totalDinheiro;

    arquivo = fopen ("produtos.dat", "rb");

    if (arquivo != NULL)
    {

        fread(&produto, sizeof(prod), 1, arquivo);

        printf(" Cod  Nome                          Preco   Quant   | ValorEstoque\n");
        printf("==================================================================\n");


        while(!feof(arquivo))
        {
            valor_produto = produto.preco * produto.estoque;
            totalDinheiro = totalDinheiro + valor_produto;
            totalEstoque = totalEstoque + produto.estoque;
            printf("%05d %-30s %.2f %5d     |    %.2f\n", produto.codigo, produto.nome, produto.preco, produto.estoque, valor_produto);
            fread(&produto, sizeof(prod), 1, arquivo);
        }

        printf("==================================================================\n");
        printf("Total de produtos em Estoque: %d\n", totalEstoque);
        printf("Patrimonio do Estoque: %.2f\n\n", totalDinheiro);
        fclose(arquivo);
    }
}

