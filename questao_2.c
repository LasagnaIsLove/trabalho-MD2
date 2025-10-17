#include <stdio.h>
#include <math.h>

void fator(int *v, int n, int index);

int main()
{
    printf("Questao 2 - Chaves Periodicas\n");
    printf("feito por:\n Gabriel Mota Oliveira - 241011081\n Matheus Pinheiro - 241025336\n\n");

    int num;
    printf("Insira o numero de chaves: ");
    scanf("%d", &num);

    printf("Insira os %d ciclos: \n", num);
    int ciclos[10];
    for (int i = 0; i < 10; i++)
        if (i < num)
        {
            printf("C%d: ", i + 1);
            scanf("%d", &ciclos[i]);
        }
        else
            ciclos[i] = 0;

    putchar('\n');
    int produto_de_primos[10], expoentes[21], max_expoentes[21];
    for (int i = 0; i < 21; i++)
        max_expoentes[i] = 0;

    for (int j = 0; j < num; j++)
    {
        for (int i = 0; i < 21; i++)
        {
            if (i < 10)
                produto_de_primos[i] = -1;
            expoentes[i] = 0;
        }

        printf("Fazendo fatoracao prima de %d...\n", ciclos[j]);
        fator(produto_de_primos, ciclos[j], 0);

        int temp = produto_de_primos[0];

        for (int i = 0; i < 10; i++)
            if (produto_de_primos[i] != -1)
            {
                if (expoentes[produto_de_primos[i]] == 0)
                    expoentes[produto_de_primos[i]]++;

                else if (produto_de_primos[i] == temp)
                    expoentes[produto_de_primos[i]]++;

                else
                    temp = produto_de_primos[i];
            }

        for (int i = 2; i < 21; i++)
            if (expoentes[i] > max_expoentes[i])
                max_expoentes[i] = expoentes[i];

        printf("Resultado da fatoracao prima de %d: [ ", ciclos[j]);
        if (ciclos[j] == 1)
            printf("conjunto vazio ");

        else
            for (int i = 2; i < 21; i++)
                if (expoentes[i] != 0)
                    printf("%d^%d ", i, expoentes[i]);
        printf("]\n");
    }
    printf("\nIMPORTANTE: para encontrar o primeiro ano (x>0) em que todas as chaves possam ser utilizadas vamos calcular o MMC de todos os ciclos.\n");
    printf("Para isso vamos utilizar das fatoracoes primas de cada ciclo e pegar o expoente maximo (maior expoente encontrado) de cada numero da fatoracao de cada ciclo.\n");
    printf("Com isso teremos o MMC dos ciclos escrito na forma fatorada.\n\n");
    printf("Resultado da fatoracao maxima dos ciclos: [ ");
    int mmc = 1;
    for (int i = 2; i < 21; i++)
        if (max_expoentes[i] != 0)
        {
            printf("%d^%d ", i, max_expoentes[i]);
            mmc *= pow(i, max_expoentes[i]);
        }
    printf("]\n");
    printf("com isso obtemos o seguinte MMC: %d\n", mmc);
    if (mmc > 50)
        printf("\nComo o resultado do MMC e maior que 50, nao existe um ano valido em que as chaves se ativarao simultaneamente.\n");
    else
        printf("\nComo o resultado do MMC nao e maior que 50, o ano em que as chaves se ativarao simultaneamente e: %d\n", mmc);

    return 0;
}

void fator(int *v, int n, int index)
{
    for (int d = 2; d < sqrt(n) + 1; d++)
        if (n % d == 0)
        {
            v[index] = d;
            return fator(v, n / d, index + 1);
        }

    if (n > 1)
        v[index] = n;
}