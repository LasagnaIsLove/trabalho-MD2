#include <stdio.h>

int mdcComPassos(int a, int b)
{
    int resto = -1;
    while (resto != 0)
    {
        resto = a % b;
        printf("Algoritmo de euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;
    }

    return a;
}

int inversoModular(int a, int m)
{
    int m0 = m, temp, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    if (mdcComPassos(a, m) != 1)
    {
        printf("'a' e 'm' não são coprimos.\n");
        return 1;
    }

    while (m != 0)
    {
        q = a / m;
        temp = m;
        m = a % m;
        a = temp;

        temp = x0;
        x0 = x1 - q * x0;
        x1 = temp;
    }

    if (x1 < 0)
        x1 += m0;

    printf("\nSubstituindo, temos que o inverso de %d em %d e %d.\n\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod)
{
    long long res = 1;
    long long b = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }

    return (int)res;
}

int main()
{
    int H, G, Zn, x , n1;

    printf("insira H: ");
    scanf("%d", &H);

    printf("insira G: ");
    scanf("%d", &G);

    printf("insira Zn: ");
    scanf("%d", &Zn);

    printf("insira x: ");
    scanf("%d", &x);

    printf("insira n1: ");
    scanf("%d", &n1);
    putchar('\n');

    int inverso = inversoModular(G, Zn);
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf("Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = powMod(a, x, n1);
    printf("Valor final da congruencia: %d\n", resultado);

    return 0;
}