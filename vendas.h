#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{

    int dia;
    int mes;
    int ano;
    int cod_produto;
    int qtd;

} venda;

int validar(int cod)
{
    int posicao = -1, pos_atual;
    FILE *arquivo;
    prod produto;

    arquivo = fopen("produtos.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
    }
    else
    {
        fread(&produto, sizeof(prod),1, arquivo);
        pos_atual = 0;
        while (!feof(arquivo))
        {
            if(produto.codigo == cod)
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

venda leitura_venda()
{
    FILE *arquivo;
    venda x;
    prod produto;
    int codigo;
    int posicao;
    int disponibilidade=0;
    float totalVenda;

    arquivo = fopen("produtos.dat", "rb+");

    if(arquivo == NULL)
    {
        printf("Registro de produtos nao existe");
    }
    else
    {

        do
        {
            printf("\nDia: ");
            scanf(" %d", &x.dia);

            if(x.dia < 1 || x.dia > 31)
                printf("Dia inválido\n");
        }
        while (x.dia < 1 || x.dia > 31);

        do
        {
            printf("\nMes: ");
            scanf(" %d", &x.mes);

            if(x.mes < 1 || x.mes > 12)
                printf("Mes invalido\n");
        }
        while (x.mes < 1 || x.mes > 12);

        do
        {
            printf("\nAno: ");
            scanf(" %d", &x.ano);

            if(x.ano < 1)
                printf("Ano invalido\n");
        }
        while (x.ano < 1);
        do
        {
            printf("Digite o codigo do produto que deseja vender:\n");
            scanf("%d", &codigo);
            posicao = validar(codigo);

            if(posicao == -1)
                printf("Produto nao encontrado\n");

        }
        while(posicao == -1);

        x.cod_produto = codigo;

        do
        {

            printf("Digite a quantidade do produto que deseja vender\n");
            scanf("%d", &x.qtd);

            fseek(arquivo, posicao*sizeof(prod), SEEK_SET);
            fread(&produto, sizeof(prod), 1, arquivo);

            if(produto.estoque >= x.qtd)
            {
                printf("Quantidade disponível!!!\n\n");

                produto.estoque = produto.estoque - x.qtd;
                totalVenda = produto.preco * x.qtd;

                fseek(arquivo, posicao*sizeof(prod), SEEK_SET);
                fwrite(&produto, sizeof(prod), 1, arquivo);

                printf("Venda relizada!!!!!!!\n");
                printf("Total da venda: R$%.2f\n", totalVenda);
                disponibilidade = 1;
                fclose(arquivo);

            }
            else
            {
                printf("Quantidade insuficiente\n");
                disponibilidade = 0;
            }


        }
        while (disponibilidade == 0);



        return x;

    }
}

void cadastrar_venda()
{
    FILE *arquivo;
    venda x;

    arquivo = fopen("vendas.dat", "ab");

    if(arquivo == NULL)
    {
        printf("Nao foi possivel criar o arquivo");
    }
    else
    {
        x = leitura_venda();
        fwrite(&x, sizeof(venda), 1,arquivo);

        fclose(arquivo);
    }
}

float total_venda(int codigo, int qtd)
{
    FILE *arquivo;
    float total;
    int posicao;
    prod produto;

    arquivo = fopen("produtos.dat", "rb");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
    }
    else
    {
        posicao = localizar(codigo);
        fseek(arquivo, posicao*sizeof(prod), SEEK_SET);
        fread(&produto, sizeof(prod), 1, arquivo);

        total = produto.preco * qtd;

        fclose(arquivo);

    }
    return total;
}

void localizar_venda()
{
    FILE *arquivo;
    int posicao=-1, pos_atual = 0;
    int codigo;
    venda x;
    float total, qtd_vendas;

    arquivo = fopen("vendas.dat", "rb+");

    if(arquivo == NULL)
    {
        printf("Não foi possível abrir o registro de vendas");
    }
    else
    {
        fread(&x, sizeof(venda),1, arquivo);

        printf("Digite o codigo do produto:");
        scanf("%d", &codigo);

        while (!feof(arquivo))
        {
            if(codigo == x.cod_produto)
            {
                printf("Data................:%d/%d/%d\n", x.dia, x.mes, x.ano);
                printf("Codigo do produto...: %d\n", x.cod_produto);
                printf("Quantidade vendida..: %d\n", x.qtd);
                total = total_venda(codigo, x.qtd);

                printf("Valor total da venda: %.2f\n", total);
                printf("==============================\n ");
                qtd_vendas = qtd_vendas + total;
            }
            fread(&x, sizeof(venda),1, arquivo);

        }
        printf("Valor total das vendas : %.2f\n\n", qtd_vendas);

        fclose(arquivo);

    }

}

void localizar_venda_data()
{
    FILE *arquivo;
    venda x;
    int dia, mes, ano, posicao = -1, pos_atual;
    float total, valor_por_data;

    arquivo = fopen("vendas.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Nao foi possível abrir o arquivo\n");
    }
    else
    {
        do
        {
            printf("\nDia: ");
            scanf(" %d", &dia);

            if(dia < 1 || dia > 31)
                printf("Dia invalido\n");
        }
        while (dia < 1 || dia > 31);

        do
        {
            printf("\nMes: ");
            scanf(" %d", &mes);

            if(mes < 1 || mes > 12)
                printf("Mes invalido\n");
        }
        while (mes < 1 || mes > 12);

        do
        {
            printf("\nAno: ");
            scanf(" %d", &ano);

            if(ano < 1)
                printf("Ano invalido\n");
        }
        while (ano < 1);

        fread(&x, sizeof(venda),1, arquivo);
        while(!feof(arquivo))
        {
            if(dia == x.dia && mes == x.mes && ano == x.ano)
            {

                printf("Codigo do produto...: %d\n", x.cod_produto);
                printf("Quantidade vendida..: %d\n", x.qtd);
                total = total_venda(x.cod_produto, x.qtd);
                printf("Valor total da venda: %.2f\n", total);
                valor_por_data = valor_por_data + total;
                printf("\n");
            }

            fread(&x, sizeof(venda),1, arquivo);

        }
        fclose(arquivo);
        printf("Total vendido: %.2f\n\n", valor_por_data);
    }
}

void localizar_venda_mes()
{
    FILE *arquivo;
    venda x;
    float total_no_mes, total;
    int mes;

    arquivo = fopen("vendas.dat", "rb");

    printf("Digite o mes:");
    scanf("%d", &mes);

    if(arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
    }
    else
    {
        fread(&x, sizeof(venda), 1, arquivo);

        while(!feof(arquivo))
        {
            if(x.mes == mes)
            {
                total = total_venda(x.cod_produto, x.qtd);
                total_no_mes = total_no_mes + total;

            }
            fread(&x, sizeof(venda), 1, arquivo);
        }
        printf("Total vendido no mes %d: %.2f\n\n", mes, total_no_mes);
        fclose(arquivo);
    }
}

