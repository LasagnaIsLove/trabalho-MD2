#include <stdio.h>
#include <math.h>

void fator(int *v, int n, int index);

int main()
{
    int num;
    printf("Questao 3 - A Razao de Eficiencia de um Numero\n");
    printf("feito por:\n Gabriel Mota Oliveira - 241011081\n Matheus Pinheiro - 241025336\n\n");

    printf("Por favor insira o numero que deseja descobrir a razao de eficiencia: ");
    scanf("%d", &num);

    int produto_de_primos[10];
    for (int i = 0; i < 10; i++)
        produto_de_primos[i] = -1;

    printf("Fazendo fatoracao prima de %d...\n", num);
    fator(produto_de_primos, num, 0);

    int temp = produto_de_primos[0], expoentes[106];
    for (int i = 0; i < 106; i++)
        expoentes[i] = 0;

    for (int i = 0; i < 10; i++)
        if (produto_de_primos[i] != -1)
            if (expoentes[produto_de_primos[i]] == 0)
                expoentes[produto_de_primos[i]]++;

            else if (produto_de_primos[i] == temp)
                expoentes[produto_de_primos[i]]++;

            else
                temp = produto_de_primos[i];

    float tau = 0, sigma = 1;
    printf("Resultado da fatoracao prima de %d: [ ", num);
    if (num == 1)
    {
        printf("conjunto vazio ");
        tau = 1;
        sigma = 1;
    }
    else
    {
        for (int i = 0; i < 106; i++)
            if (expoentes[i] != 0)
            {
                tau += (expoentes[i] + 1);
                sigma *= (pow(i, expoentes[i] + 1) - 1) / (i - 1);
                printf("%d^%d ", i, expoentes[i]);
            }
    }

    printf("]\n");
    printf("A partir da fatoracao prima obtemos: \n");
    printf("  1- tau = %.0f\n  2- sigma = %.0f\n", tau, sigma);

    float resultado = sigma / tau;
    printf("\nConsequentemento usando a formula: 'sigma(n)/tau(n)', obtemos a razao de eficiencia de %d...\nResultado: %.2f", num, resultado);
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
